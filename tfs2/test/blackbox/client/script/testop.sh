# This shell is assumed to be run in build1

cd /home2/tfs/tplatform/tfs/build
cp ../distrib/tfs_client.ini .
rm -rf testop
mkdir testop
cd testop

echo Init...

cexecs :1-9 rm -rf /home/tfs/testop >null
cexecs :1-9 mkdir /home/tfs/testop >null
cexecs :1-9 cp /home2/tfs/tplatform/tfs/build/blackbox/test_operation /home/tfs/testop/ >null
cexecs :1-9 cp /home2/tfs/tplatform/tfs/build/tfs_client.ini /home/tfs/testop >null 

for i in 1 2 3 4 5 6 7 8 9
do
    echo
    echo Testing $i clients ...
    cexec :1-$i 'cd /home/tfs/testop; ./test_operation >$HOSTNAME'
    cexecs :1-$i 'cp /home/tfs/testop/build* /home2/tfs/tplatform/tfs/build/testop; sleep 0.1' >null
    cat build* >$i
done

cexec :1-9 rm -rf /home/tfs/testop 
echo
echo Test over

