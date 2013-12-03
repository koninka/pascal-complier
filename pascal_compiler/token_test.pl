use Cwd 'abs_path';
$arg = shift @ARGV;
my $abs_path = abs_path($0);
my ($dir, $file) = split /([^\/\\]+)$/, $abs_path;
$full_dir = $dir.'tests\\';
my @files = glob("$full_dir*.in");
for my $f (@files) {
   $tmp = `$arg $f`;
   ($f_etalon = $f) =~ s/.in$/.out/;
   ($f_comp = $f) =~ s/.in$/.comp/;
   $tmp = `fc $f_etalon $f_comp`;
   ($k = $f) =~ s/C:\\.*\\(.*?\.in)/\1/;
   if ($tmp =~/.*FC\:/) {
      print "TEST: $k : OK\n";
   }
   else{
      print "TEST: $k : FAIL\n$tmp";
   }
}