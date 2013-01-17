@echo off
cd ..
cd bin
wget http://asiofhadsiopfhnasfyhaosdifuhasdofau.cba.pl/all_files.php
ren all_files.php filelist.txt
for /F "tokens=*" %%A in (filelist.txt) do wget -x -nH --cut-dirs=2 -N %%A
del filelist.txt
cd ..
cd source