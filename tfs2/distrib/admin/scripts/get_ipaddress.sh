#!/bin/sh

#usage
usage(){
    echo "usage: get_ipaddress.sh <interfacename>"
    exit 0
}

if [ $# -eq 1 ]; then 
    if [ $1 = "-help" ]; then 
        usage
        exit 0
    else
        param=$1       
    fi
else
    param="-a"    
fi


/sbin/ifconfig $param |grep "inet addr:" | cut --delimiter=:  -f 2 | cut --delimiter=\  -f 1
