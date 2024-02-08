
my $text = "";

while (<>) {
    s/[ ]+$//g;
    my $strWithoutLeadingTrailing = $_;
    $strWithoutLeadingTrailing =~ s/(^([ ]|\t)+)//g;

    $text = $text . $strWithoutLeadingTrailing;

    $text =~ s/[ ]{2,}/ /g;
}

$text =~ s/<.*?>//g;

$text =~ s/^\n+//g;
$text =~ s/\n+$//g;

$text =~ s/\n{2,}/\n\n/g;

print $text;
