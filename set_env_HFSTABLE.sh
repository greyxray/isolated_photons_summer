
# compiler
#source /afs/cern.ch/sw/lcg/contrib/gcc/4.3/x86_64-slc5-gcc43-opt/setup.sh
. /afs/cern.ch/sw/lcg/contrib/gcc/4.6/x86_64-slc6-gcc46-opt/setup.sh
#. /afs/cern.ch/sw/lcg/contrib/gcc/4.3/i686-slc5-gcc43-opt/setup.sh
# cernlib
#export CERN_ROOT=/afs/cern.ch/sw/lcg/external/cernlib/2006a/x86_64-slc5-gcc43-opt
export CERN_ROOT=/afs/cern.ch/sw/lcg/external/cernlib/2006a/x86_64-slc6-gcc46-opt
#export CERN_ROOT=/afs/cern.ch/sw/lcg/external/cernlib/2006a/i686-slc5-gcc43-opt

# root
#cd /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.00/x86_64-slc5-gcc43-opt/root/
#. /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.00/x86_64-slc5-gcc43-opt/root/bin/thisroot.sh
cd  /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.14/x86_64-slc6-gcc46-opt/root/
.  /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.14/x86_64-slc6-gcc46-opt/root/bin/thisroot.sh
#cd /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.00/i686-slc5-gcc43-opt/root/
#. /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.00/i686-slc5-gcc43-opt/root/bin/thisroot.sh
cd -

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/afs/desy.de/group/zeus/pool/kuprash/programs/KtJet-1.08/lib
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/afs/desy.de/user/g/glusheno/programs/KtJet-1.08/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/afs/cern.ch/sw/lcg/external/clhep/2.0.4.0/slc4_amd64_gcc34/lib
