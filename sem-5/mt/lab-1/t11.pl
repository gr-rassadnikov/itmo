#!usr/bin/perl
while (<>) {
	print if /^0*(1(01*0)*1|0)*0*$/;
}