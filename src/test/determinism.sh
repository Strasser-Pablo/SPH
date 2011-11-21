echo $1
mkdir 1
mkdir 2
cd 1
rm -r *

$1
md5sum * >../1.md5
cd ../2
rm -r *
$1
md5sum * >../2.md5
cd ..
cmp 1.md5 2.md5
