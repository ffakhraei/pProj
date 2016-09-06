#!/bin/bash -u

# This script tests the reachability of the clients on the network and subnetwork(s)
# It displays and stores (in varous files as described below) information about
# the hostname, IP address, Ethernet address, Internet interface, route to reach, 
# etc. of all the machines on the network and the corresponding subnetwork(s), if applicable.
# By Farzin Fakhraei - ffakhrae - 301125876

# function IsResponding:
# This function tests whether a host is responding or not
# Input argument: the IP address of the destination
# Output: displays the following information and saves them in "log.txt" file. It also creates files containing the name and IP address of all the machines on the network
#   whether the destination IP is responding or not
#   The hostname of the source and destination machines
#   The Ethernet address of the destination machine
#   The internet inteface of the destination machine
#   The path from the source to the destination over the network

function IsResponding()
{
    ping -c1 -W1 $1 1>/dev/null 2>/dev/null
    if [ $? -eq 0 ]; then
        echo "Host with IP address $1 is reachable from $HOSTNAME" | tee -a log.txt
        echo $1 >> reachable.IP.from.$HOSTNAME.txt
        arp -a $1 >> reachable.Name.from.$HOSTNAME.txt
        MYTEMPVAR=$(arp -a $1)
        MYHOSTNAME=$(arp -a $1 | awk '{print $1}')
        if [ "$MYSUBNET" == "admin" ]; then
            echo $(echo $MYHOSTNAME | awk 'BEGIN {FS="."} {print $1}') >> admin.all.hostnames.txt
        elif [ "$MYSUBNET" == "net16" ]; then  
            echo $MYHOSTNAME >> net16.hostnames.txt
        elif [ "$MYSUBNET" == "net17" ]; then
            echo $MYHOSTNAME >> net17.hostnames.txt
        elif [ "$MYSUBNET" == "net18" ]; then
            echo $MYHOSTNAME >> net18.hostnames.txt
        elif [ "$MYSUBNET" == "net19" ]; then
            echo $MYHOSTNAME >> net19.hostnames.txt
        fi
        MYETHERNETADD=$(arp -a $1 | awk '{print $4}')
        MYINTERFACE=$(arp -a $1 | awk '{print $7}')
        printf "IP address $1 belongs to $MYHOSTNAME with Ethernet address $MYETHERNETADD over interface $MYINTERFACE \n" | tee -a log.txt
        printf "Path to reach IP address $1 ($MYHOSTNAME) from $1 ($HOSTNAME) is:\n" | tee -a log.txt
        tracepath $1 | tee -a log.txt
        echo | tee -a log.txt
        #ifconfig $1 | grep eth0
        #ifconfig $1 | grep eth1
        isReachable=0
        sleep 1
    else #[ $? -eq 1 ] && 
        echo "Host with IP address $1 is not reachable from $HOSTNAME or is not part of $MYSUBNET network" | tee -a log.txt
        echo $1 >> unreachable.IP.from.$HOSTNAME.txt 
        echo | tee -a log.txt
        isReachable=1
    fi
}


# function IsRespondingName:
# This function tests whether a host is responding or not
# Input argument: the hostname of the destination
# Output: displays the following information and saves them in "log.txt" file. It also creates files containing the name and IP address of all the machines on the network
#   whether the destination IP is responding or not
#   The hostname of the source and destination machines
#   The Ethernet address of the destination machine
#   The internet inteface of the destination machine
#   The path from the source to the destination over the network

function IsRespondingName()
{
    ping -c1 -W1 $1 1>/dev/null 2>/dev/null
    if [ $? -eq 0 ]; then
        echo "Host with hostname \"$1\" is reachable from $HOSTNAME" | tee -a log.txt
        echo $1 >> reachable.IP.from.$HOSTNAME.txt
        arp -a $1 >> reachable.Name.from.$HOSTNAME.txt
        MYTEMPVAR=$(arp -a $1)
        MYHOSTNAME=$(arp -a $1 | awk '{print $1}')
        #echo $(echo $MYHOSTNAME | awk 'BEGIN {FS="."} {print $1}') >> admin.all.hostnames.txt
        MYIPADDRESS=$(ping -c1 $1 | awk 'NR==1 {print $3}'| tr -d "()")
        MYNETWORK=$(echo $MYHOSTNAME | awk 'BEGIN {FS="."} {print $2}') 
        MYETHERNETADD=$(arp -a $1 | awk '{print $4}')
        MYINTERFACE=$(arp -a $1 | awk '{print $7}')
        printf "Host \"$1\" belongs to \"$MYSUBNET\" network with Ethernet address $MYETHERNETADD over interface $MYINTERFACE and IP address $MYIPADDRESS \n" | tee -a log.txt
        printf "Path to reach \"$1\" ($MYHOSTNAME) on subnetwork $MYSUBNET from \"$HOSTNAME\" on subnetwork $MYNETWORK is:\n" | tee -a log.txt
        tracepath $1 | tee -a log.txt
        echo | tee -a log.txt
        #ifconfig $1 | grep eth0
        #ifconfig $1 | grep eth1
        isReachable=0
        sleep 1
    else #[ $? -eq 1 ] && 
        echo "Host $i.$MYSUBNET is not reachable from $HOSTNAME or is not part of $MYSUBNET network" | tee -a log.txt
        echo $i.$MYSUBNET >> unreachable.Name.from.$HOSTNAME.txt 
        echo | tee -a log.txt
        isReachable=1
    fi
}

# creating blank files to keep the information obtained by the above function(s)
echo > reachable.Name.from.$HOSTNAME.txt
echo > reachable.IP.from.$HOSTNAME.txt
echo > unreachable.Name.from.$HOSTNAME.txt
echo > unreachable.IP.from.$HOSTNAME.txt
echo > admin.all.hostnames.txt
echo > net16.hostnames.txt
echo > net17.hostnames.txt
echo > net18.hostnames.txt
echo > net19.hostnames.txt
echo > log.txt

# variables
NET16BASEIP=172.16.1
NET17BASEIP=172.17.1
NET18BASEIP=172.18.1
NET19BASEIP=172.19.1
ADMINBASEIP=192.168.0
SCANRANGE=21   #(seq 1 $SCANRANGE)

# Testing reachability of clients on "admin" network by pinging their IP address
MYSUBNET=admin
clear
echo "======================================================================================" | tee -a  log.txt
echo "Scanning \"admin\" network by IP addresses" | tee -a log.txt
echo "======================================================================================" | tee -a  log.txt
sleep 1
for i in $ADMINBASEIP.{1..21}
    do
    IsResponding $i #&
done

sed -i 's/arp://' admin.all.hostnames.txt   # to get rid of arp: in the file that is caused by pinging the machine that the script is being run on and replacing it with the name of the machine
sed -i '/^\s*$/d' admin.all.hostnames.txt  # to get rid of blank lines in the file
# Test reachability of clients on "admin" network by pinging server names
echo "======================================================================================" | tee -a  log.txt
echo "Scanning \"admin\" network by hostnames" | tee -a log.txt
echo "======================================================================================" | tee -a  log.txt
sleep 1
for i in $(cat admin.all.hostnames.txt)
do
    IsRespondingName $i.$MYSUBNET
done


# Testing reachability of clients on "net16" network by pinging their IP address
MYSUBNET=net16
clear
echo "======================================================================================" | tee -a  log.txt
echo "Scanning \"net16\" network by IP addresses" | tee -a log.txt
echo "======================================================================================" | tee -a  log.txt
sleep 1
for i in $NET16BASEIP.{1..21}
    do
    IsResponding $i #&
done

sed -i 's/arp://' admin.all.hostnames.txt   # to get rid of arp: in the file that is caused by pinging the machine that the script is being run on and replacing it with the name of the machine
sed -i '/^\s*$/d' admin.all.hostnames.txt  # to get rid of blank lines in the file
# Test reachability of clients on "net16" network by pinging server names
echo "======================================================================================" | tee -a  log.txt
echo "Scanning \"net16\" network by hostnames" | tee -a log.txt
echo "======================================================================================" | tee -a  log.txt
sleep 1
for i in $(cat admin.all.hostnames.txt)
do
    IsRespondingName $i.$MYSUBNET
done

# Testing reachability of clients on "net17" network by pinging their IP address
MYSUBNET=net17
clear
echo "======================================================================================" | tee -a  log.txt
echo "Scanning \"net17\" network by IP addresses" | tee -a log.txt
echo "======================================================================================" | tee -a  log.txt
sleep 1
for i in $NET17BASEIP.{1..21}
    do
    IsResponding $i
done

sed -i 's/arp://' admin.all.hostnames.txt   # to get rid of arp: in the file that is caused by pinging the machine that the script is being run on and replacing it with the name of the machine
sed -i '/^\s*$/d' admin.all.hostnames.txt  # to get rid of blank lines in the file
# Test reachability of clients on "net17" network by pinging server names
echo "======================================================================================" | tee -a  log.txt
echo "Scanning \"net17\" network by hostnames" | tee -a log.txt
echo "======================================================================================" | tee -a  log.txt
sleep 1
for i in $(cat admin.all.hostnames.txt)
do
    IsRespondingName $i.$MYSUBNET
done

# Testing reachability of clients on "net18" network by pinging their IP address
MYSUBNET=net18
clear
echo "======================================================================================" | tee -a  log.txt
echo "Scanning \"net18\" network by IP addresses" | tee -a log.txt
echo "======================================================================================" | tee -a  log.txt
sleep 1
for i in $NET18BASEIP.{1..21}
    do
    IsResponding $i #&
done

sed -i 's/arp://' admin.all.hostnames.txt   # to get rid of arp: in the file that is caused by pinging the machine that the script is being run on and replacing it with the name of the machine
sed -i '/^\s*$/d' admin.all.hostnames.txt  # to get rid of blank lines in the file
# Test reachability of clients on "net18" network by pinging server names
echo "======================================================================================" | tee -a  log.txt
echo "Scanning \"net18\" network by hostnames" | tee -a log.txt
echo "======================================================================================" | tee -a  log.txt
sleep 1
for i in $(cat admin.all.hostnames.txt)
do
    IsRespondingName $i.$MYSUBNET
done

# Testing reachability of clients on "net19" network by pinging their IP address
MYSUBNET=net19
clear
echo "======================================================================================" | tee -a  log.txt
echo "Scanning \"net19\" network by IP addresses" | tee -a log.txt
echo "======================================================================================" | tee -a  log.txt
sleep 1
for i in $NET19BASEIP.{1..21}
    do
    IsResponding $i #&
done

sed -i 's/arp://' admin.all.hostnames.txt   # to get rid of arp: in the file that is caused by pinging the machine that the script is being run on and replacing it with the name of the machine
sed -i '/^\s*$/d' admin.all.hostnames.txt  # to get rid of blank lines in the file
# Test reachability of clients on "net19" network by pinging server names
echo "======================================================================================" | tee -a  log.txt
echo "Scanning \"net19\" network by hostnames" | tee -a log.txt
echo "======================================================================================" | tee -a  log.txt
sleep 1
for i in $(cat admin.all.hostnames.txt)
do
    IsRespondingName $i.$MYSUBNET
done

echo | tee -a log.txt
clear

echo "======================================================================================" | tee -a  log.txt
echo "Testing IPv6 addresses" | tee -a log.txt
echo "======================================================================================" | tee -a  log.txt
# Pinging the IPv6 addresses indicated in the assignment
IPV6_1=2002:ac10:10c:118:250:56ff:fea4:2fa3
IPV6_2=2002:ac10:101:117:250:56ff:fea4:58ac
for i in $IPV6_1 $IPV6_2; do
    ping6 -c1 -W1 $i  1>/dev/null 2>/dev/null
    if [ $? -eq 0 ]; then
        printf "Host with IP address $i is reachable from $HOSTNAME\n" | tee -a log.txt
        printf "Path to host with IP address $i is: \n" | tee -a log.txt
        tracepath6 $i | tee -a log.txt
        echo
   else
        printf "Host with IP address $i is not reachable from $HOSTNAME\n" | tee -a log.txt
    fi
done

