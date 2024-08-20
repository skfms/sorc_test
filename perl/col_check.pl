#! /usr/bin/perl -w

die "$0 <file>\n" if ($#ARGV < 0);

print "Can't open $ARGV[0]: $!\n" unless open(my $fh, "<", $ARGV[0]);
for my $line (<$fh>)
{
	chomp $line;

	my @tt = split /\|/, $line;

	print "$tt[10]\n" if (length($tt[10]) >= 50);
};
$fh && close $fh;

