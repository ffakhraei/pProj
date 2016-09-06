#!/bin/bash

clear
date > log.restrictive.txt
echo "This script creats a restrictive firewall on the host that will blocks all packets except for ssh to port 22" | tee -a log.restrictive.txt

#-------------------------------------------------------------------------------
#   GLOBAL VARIABLES
#-------------------------------------------------------------------------------
ALLOW_IP_MASTER_RANGE=192.168.0.0/24
ALLOW_IP_RANGE1=172.16.0.0/16
ALLOW_IP_RANGE2=172.17.0.0/16
ALLOW_IP_RANGE3=172.18.0.0/16
ALLOW_IP_RANGE4=172.19.0.0/16

#-------------------------------------------------------------------------------
#   FUNCTIONS
#-------------------------------------------------------------------------------
# FUNCTION: reset_firewall
# POSTCONDITION: all firewall rules are reset to the original state
reset_firewall()
{
    sudo iptables -F INPUT
    sudo iptables -P INPUT ACCEPT
    sudo iptables -F FORWARD
    sudo iptables -P FORWARD ACCEPT
    sudo iptables -F OUTPUT
    sudo iptables -P OUTPUT ACCEPT
    echo "Firewall rules have been reset."  | tee -a log.restrictive.txt
}

# FUNCTION: reset_eth1
# POSTCONDITION: eth1 interface of the host is reset to its original state
reset_eth1()
{
    sudo ifconfig eth1 down && sudo ifdown eth1
    sleep 1
    ifconfig | tee -a log.restrictive.txt
    sudo ifconfig eth1 up && sudo ifup eth1
    ifconfig | tee -a log.restrictive.txt
    sleep 1.5
    clear
}

#-------------------------------------------------------------------------------
#   MAIN BODY
#-------------------------------------------------------------------------------
echo "Current firewall rules: " | tee -a log.restrictive.txt
sudo iptables -L | tee -a log.restrictive.txt
echo | tee -a log.restrictive.txt
reset_firewall
echo | tee -a log.restrictive.txt
echo "The default firewall rules: " | tee -a log.restrictive.txt
sudo iptables -L | tee -a log.restrictive.txt

echo "Allow incoming SSH" | tee -a log.restrictive.txt
sudo iptables -A INPUT -p tcp --dport ssh -j ACCEPT
#sudo iptables -A INPUT -i eth0 -p tcp -s 192.168.0.0/24 ALLOW_IP_MASTER_RANGE --dport 22 -m state --state NEW, ESTABLISHED -j ACCEPT
#sudo iptables -A OUTPUT -o eth0 -p tcp --sport 22 -m state --state ESTABLISHED -j ACCEPT

echo "Allow outgoing SSH only to network $ALLOW_IP_MASTER_RANGE" | tee -a log.restrictive.txt
sudo iptables -A OUTPUT -o eth1 -p tcp -d $192.168.0.0/24 --dport 22 -m state --state NEW,ESTABLISHED -j ACCEPT
sudo iptables -A INPUT -i eth1 -p tcp --sport 22 -m state --state ESTABLISHED -j ACCEPT

echo "Setting new RESTRICTIVE iptables default policy" | tee -a log.restrictive.txt
sudo iptables -P INPUT DROP
sudo iptables -P FORWARD DROP
sudo iptables -P OUTPUT DROP

echo "Current iptables policy" | tee -a log.restrictive.txt
sudo iptables -L | tee -a log.restrictive.txt
sleep 3
reset_eth1
read -p "Please check the rules manually and press enter when done..." | tee -a log.restrictive.txt
clear
echo "Restoring the default iptables policy..." | tee -a log.restrictive.txt
reset_firewall
reset_eth1
