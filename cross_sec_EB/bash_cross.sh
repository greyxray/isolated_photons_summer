cp /afs/desy.de/user/g/glusheno/zeus/dustexchange/cross_sec.cxx /nfs/dust/zeus/group/glushenko/isolated_photons_summer/cross_sec_EB/cross_sec.cxx 
touch output.txt
./p cross_sec >> output.txt
cp  /nfs/dust/zeus/group/glushenko/isolated_photons_summer/cross_sec_EB/output.txt /afs/desy.de/user/g/glusheno/zeus/dustexchange/output.txt 
rm output.txt