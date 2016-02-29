
cd stats_aplha
prename 's/^.*D_(.*\.txt)$/$1/'  *.txt
prename 's/^.*priority(.*\.txt)$/rank$1/'  *.txt

cd ..
cd stats_ber
prename 's/^.*D_(.*\.txt)$/$1/'  *.txt
prename 's/^.*priority(.*\.txt)$/rank$1/'  *.txt
cd ..
cd stats_cache_size_600s
prename 's/^.*D_(.*\.txt)$/$1/'  *.txt
prename 's/^.*priority(.*\.txt)$/rank$1/'  *.txt
cd ..
cd stats_cache_size_800s
prename 's/^.*D_(.*\.txt)$/$1/'  *.txt
prename 's/^.*priority(.*\.txt)$/rank$1/'  *.txt
cd ..


