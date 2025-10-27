#! /usr/bin/perl -w
# 파일내용 중 동일한 데이터 비교

use strict;
use warnings;

use Data::Dumper;

our $modnm = $0;

& about if ($#ARGV != 3);

our ($sorc_file, $dest_file, $skip_rows, $pk_cols) = @ARGV;

& main;

# ***************************
sub main()
{
	my @sorc_arr = & get_file($sorc_file);
	my @dest_arr = & get_file($dest_file);
	
	my $row_sz = @sorc_arr;
	my $col_sz = @{$sorc_arr[0]};
	
	#printf "row count = %d\n", scalar(@sorc_arr);
	my ($pline, $pk_find, $pk_data, $chk_data);
	my ($x, $y, $z);
	
	for($x=0; $x<$row_sz; $x++)
	{
		for($y=0; $y<@dest_arr; $y++)
		{
			$pk_find = 1;
			$pk_data = "";
			
			for($z=0; $z<$pk_cols; $z++)
			{
				if($sorc_arr[$x][$z] eq $dest_arr[$y][$z])
				{
					$pk_data .= ", " if ($pk_data ne "");
					$pk_data .= $sorc_arr[$x][$z];
				}
				else
				{
					$pk_find = 0;
					last;
				};
			};
			
			last if $pk_find;
		};

		if($pk_find == 1)
		{
			$chk_data = 0;
			for($z=$pk_cols; $z<$col_sz; $z++)
			{
				if($sorc_arr[$x][$z] eq $dest_arr[$y][$z])
				{
					$chk_data = 1;
					last;
				}
			};
			
			if($chk_data == 0)
			{
				printf "PK : %s : Check Ok !\n", $pk_data;
			}
			else
			{
				printf "PK : %s : Cehck Fail ! [%s,%s]\n", $pk_data, $sorc_arr[$x][$z], $dest_arr[$y][$z];
			};
		}
		else
		{
			printf "PK : %s : not found !\n", $pk_data;
		};
	};
	
=begin
	my $pline;
	
	for my $t1 (@sorc_arr)
	{
		my @sarr = @$t1;
		
		$pline = "";
		for my $t (@sarr)
		{
			#$pline .= "\t" if ($pline ne "");
			#$pline .= $t;
		};
		
		print $pline;
	};
=cut

};

# ***************************
sub about()
{
    print <<_ENDABOUT;
Usage : $modnm <sorc_file> <dest_file> <skip_rows> <pk_cols>
_ENDABOUT

    exit 0;
};

# ***************************
# ProC 소스에서 생성된 *.c 소스를 제외
sub get_file()
{
	my $file_name = shift;
	
	my @fdata;

	open (FH, $file_name) || die "file[$file_name] open error !";

	for my $line (<FH>)
	{
		my @t = split(/\t/, $line);
		push(@fdata, \@t);
	};
	
	close (FH);

	#print Dumper(\@fdata);

	return @fdata;
};

