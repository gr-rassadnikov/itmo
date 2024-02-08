#!usr/bin/perl
while (<>) {
	print if /\b(\w+)\1\b/;
}