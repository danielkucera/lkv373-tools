#! /usr/bin/perl
use strict;
use warnings FATAL=>'all';
use autodie;

#This script is for injecting code into the original block2.bin firmware (block2, not full memory-dump!)
#see README.TXT

#(c) 2020 by kitten_nb_five
#freenode #lkv373a
#licence: AGPL v3 or later
#NO WARRANTY! CHECK THE OUTPUT!

#limitations:
#!!ASSUMING 4 BYTE-INSTRUCTIONS ONLY!!
#unsupported: pseudo-ops that uses addr (like "la")


#for debugging
my $verbose=0;

if(scalar(@ARGV)<3)
{
	print "usage: ./assemble.pl \$block2.bin \$file.asm \$output.bin\n";
	exit(0);
}

my $filename_block2_bin=$ARGV[0];
my $filename=$ARGV[1];
my $filename_block2_out=$ARGV[2];
my @file;

print "parsing file $filename...\n";

open(my $inp, '<', $filename);
while(($_=<$inp>))
{
	chomp;
	push @file, $_;
}
close($inp);

my %labels;
my %addr_to_inj;

my $pos_eof;
my $addr_eof;

my $i;
for $i (0.. $#file)
{
	if($file[$i]=~/^(\w+):/)
	{
		print "found label $1 line $i\n" if($verbose);
		$labels{$1}=$i;
		$file[$i]="";
		$pos_eof=$i if($1 eq "eof");
		
	}
	elsif($file[$i]=~/^!!pos=0x([[:xdigit:]]+)/)
	{
		print "found addr_to_inj $1 line $i\n" if($verbose);
		$addr_to_inj{$1}=$i;
	}
}

my $nb_inj=0;

for $i (0.. $#file)
{
	if($file[$i] eq "j eof")
	{
		my $offset=calc_offset($i, $pos_eof)+2*4*$nb_inj;
		$nb_inj++;
		
		$file[$i]="j $offset";
		
		print "jump to eof replaced with offset $offset\n" if($verbose);
	}
	elsif($file[$i]=~/^j(?:al|)\s+(\w+)/ || $file[$i]=~/^b.+?\s+\$r\d+,\s+(\w+)/)
	{
		my $word=$1;
		next if(!$labels{$word});
		
		print "label $word found in instr line $i\n" if($verbose);
		
		my $offset=calc_offset($i, $labels{$word});
		
		$file[$i]=~s/$word/$offset/;
	}
	elsif($file[$i]=~/(?:hi20|lo12)\((\w+)\)/)
	{
		my $word=$1;
		next if(!$labels{$word});
		
		print "label $word found as arg for load line $i\n" if($verbose);
		
		#absolute offset from start of file
		#at runtime we need to add PC to this to get real offset
		#THIS WILL ONLY WORK FOR THIS SPECIFIC SEQUENCE:
		#sethi reg, hi20(label_str)
		#ori reg, reg, lo12(label_str)
		#mfusr reg2, $PC
		#add reg, reg, reg2
		my $offset=calc_offset(0, $labels{$word})-16;
		
		$file[$i]=~s/$word/$offset/;
	}
}

foreach my $addr (keys %addr_to_inj)
{
	my $offset=calc_offset(0, $addr_to_inj{$addr});
	$addr_to_inj{$addr}=$offset;
	print "for addr_to_inj $addr offset is $offset\n" if($verbose);
}

if(!$pos_eof)
{
	die "label eof not found";
}

$addr_eof=calc_offset(0, $pos_eof);

my $filename_out=($filename=~s/\.asm/_fixed.asm/r);
open(my $out, '>', $filename_out);
print $out "!autogenerated from $filename by assemble.pl - DO NOT MODIFY\n\n";
print $out join("\n", @file);
close($out);

my $filename_bin=($filename_out=~s/\.asm/.bin/r);

print "file $filename fixed, calling assembler and objdump, please check output:\n";

#adjust names of binaries as needed
system("nds32le-unknown-linux-gnu-as $filename_out && nds32le-unknown-linux-gnu-objcopy -O binary a.out $filename_bin && rm a.out && touch _ok && nds32le-unknown-linux-gnu-objdump -b binary -D -m nds32 $filename_bin");

print "\n\n";

if(!-e "_ok")
{
	die "assembler error";
}

system("rm _ok");

open($out, '>', 'make_binary.sh');
print $out "#! /bin/sh\n";
print $out "#autogenerated by assemble.pl - DO NOT MODIFY\n";
print $out "./inject $filename_block2_bin $filename_bin $filename_block2_out $addr_eof ".scalar(keys %addr_to_inj)." ";
foreach my $addr (keys %addr_to_inj)
{
	print $out hex($addr)." ".hex($addr_to_inj{$addr})." ";
}
print $out "\n";
close($out);
system("chmod +x make_binary.sh");

print "COMMAND FOR FINAL: ./make_binary.sh\n";

############################

sub calc_offset
{
	my ($line_start, $line_end)=@_;
	
	my $flag_neg=0;
	if($line_start>$line_end)
	{
		print "inverting\n" if($verbose);
		$_=$line_start;
		$line_start=$line_end;
		$line_end=$_;
		$flag_neg=1;
	}
	
	my $offset=0;
	my $i;
	
	print "calc_offset: from $line_start to <$line_end\n" if($verbose);
	
	for($i=$line_start; $i<$line_end; $i++)
	{
		print "checking line $i: $file[$i]\n" if($verbose);
		if($file[$i] eq "" || $file[$i]=~/^\s+$/ || $file[$i]=~/^[^"]+:/ || $file[$i]=~/^!/)
		{
			next;
		}
		elsif($file[$i]=~/\.asciz\s+"([^"]+)"/)
		{
			my $length=length($1)+1; #+1 for '\0'!
			print "found string len $length\n" if($verbose);
			$offset+=$length;
		}
		elsif($file[$i]=~/^\./)
		{
			next;
		}
		else
		{
			print "offset++ for $file[$i]\n" if($verbose);
			$offset+=4;
		}
	}
	
	print "for alignment +",(4-$offset%4)%4,"\n" if($verbose);
	$offset+=(4-$offset%4)%4; #align on 4 byte boundary
	
	return ($flag_neg?-$offset:$offset);
}

