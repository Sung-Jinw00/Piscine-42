#!/usr/bin/perl

use warnings;
use strict;

die "program x y density c1 c2 c3" unless (scalar(@ARGV) == 6);

my ($x, $y, $density, $c1, $c2, $c3) = @ARGV;

print "$y$c1$c2$c3\n";
for (my $i = 0; $i < $y; $i++) {
	for (my $j = 0; $j < $x; $j++) {
		if (int(rand($y) * 2) < $density) {
			print $c2;
		}
		else {
			print $c1;
		}
	}
	print "\n";
}
