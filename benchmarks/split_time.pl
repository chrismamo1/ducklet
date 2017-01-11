#/usr/bin/perl

my $text, $number;
while (<STDIN>) {
        print $_;
        $text = $_;
        $text =~ /([0-9]+\.[0-9]+)\n/;
        $number = $1;
        print "$number\n";
}
