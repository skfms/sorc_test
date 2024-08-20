#! /usr/bin/perl -w

my $dec = $ARGV[0];

my $aa = sprintf "%d", $dec & 0x0000FFFF;

printf "dec : %d / remaind : %04d\n", $dec, $aa;

#my $hex2 = substr($hex, length($hex)-4, 4);

#print "$hex2\n";

#print hex "$hex2";

