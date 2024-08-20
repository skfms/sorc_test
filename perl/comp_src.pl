#! /usr/bin/perl -w
# 디렉토리 소스 비교

use strict;
use warnings;

use Data::Dumper;

our $modnm = $0;

& about if ($#ARGV < 1);

our ($source_dir, $target_dir) = @ARGV;

& main;

# ***************************
sub main()
{
	my @_files;

	$source_dir .= '/';
	$target_dir .= '/';

	my @files = `ls $source_dir`;
	for my $file (@files)
	{
		chomp $file;
		push (@_files, $file) if ($file =~ /.*\.[ch]$/ || $file =~ /.*\.pc$/ );
	};

	my @comp_files = & del_gen_source(\@_files);

	#print Dumper \@comp_files;

	for my $file (@comp_files)
	{
		print "diff $file\n";
		my $result = `diff $source_dir$file $target_dir$file`;
		print "result : $result\n" if ($result);
	};
};

# ***************************
sub about()
{
    print <<_ENDABOUT;
Usage : $modnm <source_dir> <target_dir>
_ENDABOUT

    exit 0;
};

# ***************************
# ProC 소스에서 생성된 *.c 소스를 제외
sub del_gen_source()
{
	my $arg = shift;
	my @files = @$arg;

	#print Dumper \@files;

	my @new_files;
	my @gen_files;
	my $_tt;

	# Oracle ProC source find
	for my $file (@files)
	{
		if ($file =~ /.*\.pc/)
		{
			$_tt = $file;
			$_tt  =~ s/\.pc/\.c/;
			push @gen_files, $_tt;
		};
	};

	for my $file (@files)
	{
		push (@new_files, $file) unless (grep { $_ eq $file } @gen_files);
	};

	return @new_files;
};

