#!/bin/sh

#
# user register
#
    
if [ ! -d /homeX/tfs/share/user/$USER ] ; then
    mkdir /homeX/tfs/share/user/$USER
fi

if [ -f /homeX/tfs/share/user/$USER/id_rsa.pub ] ; then
    echo "you have already registered, thanks~"
    exit 0
fi
                  
if [ ! -f /homeX/$USER/.ssh/id_rsa.pub ] ; then
    echo ""
    echo "Please hit Enter 3 times..."
    echo ""
    ssh-keygen -t rsa
fi
cp ~/.ssh/id_rsa.pub /homeX/tfs/share/user/$USER/
startdir=`dirname $0`
expect $startdir/.register.exp $USER 2>>/dev/null 1>>/dev/null
echo "Thank you!"


