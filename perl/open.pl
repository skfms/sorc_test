#! /usr/bin/perl -w

die "$0 <file>" if ($#ARGV < 0);

for my $file (@ARGV) {
	print "Can't open $file: $!\n" unless open(my $fh, "<", $file);
	$fh && close $fh;
};

print "End !\n"
