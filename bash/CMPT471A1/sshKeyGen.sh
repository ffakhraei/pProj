#!/bin/bash
clear
# This script creates a set of private and public ssh keys and adds the public key to authorized_keys
# so that these keys can be coppied to all machines on the network to allow passwordless ssh connection
# between all machines on the network
# By Fazin Fakhraei - ffakhrae - 301125876


ssh-keygen -t rsa -f /home/$USER/.ssh/id_rsa -q -N ""


# Following code would work if "spawn", "expect", and "send" commands were installed on the system
# but they are not as of this time
#expect "Enter file in which to save the key (/home/$USER/.ssh/id_rsa): "
#send "\r"
#expect "Enter passphrase (empty for no passphrase): "
#send "\r"
#expect "Enter same passphrase again: "
#send "\r"


touch /home/$USER/.ssh/authorized_keys
cat /home/$USER/.ssh/id_rsa.pub >> /home/$USER/.ssh/authorized_keys
chmod 600 /home/$USER/.ssh/authorized_keys
chmod 700 /home/$USER/.ssh
