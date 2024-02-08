#!usr/bin/perl
while (<>) {
	print if /(.*cat.*){2}/;
}