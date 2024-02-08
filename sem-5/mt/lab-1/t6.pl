#!usr/bin/perl
while (<>) {
	print if /\b(\d+)\b/;
}