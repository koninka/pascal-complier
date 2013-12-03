use Cwd 'abs_path';
$arg = shift @ARGV;
$keys = shift @ARGV;
$folder = shift @ARGV;
$full_dir = "$folder\\";
my @files = glob("$full_dir*.in");
my $ok = 0;
my $count = 0;
for my $f (@files) {
   $count++;
   $tmp = `$arg $keys $f`;
   ($f_etalon = $f) =~ s/.in$/.out/;
   ($f_comp = $f) =~ s/.in$/.comp/;
   $tmp = `fc $f_etalon $f_comp`;
   ($k = $f) =~ s/C:\\.*\\(.*?\.in)/\1/;
   if ($tmp =~/.*FC\:/) {
      $ok++;
      print "TEST: $k : OK\n";
   }
   else{
      print "TEST: $k : FAIL\n$tmp";
   }
}
print "=========================================\n";
print "$ok / $count";