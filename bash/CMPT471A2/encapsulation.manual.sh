#! /bin/bash
#  this script runs tcpdump on an intermediate node as indicated in "encapsulation.sh" script. to capture 6to4 IPv4 encapsulated datagrams

clear
sudo tcpdump -i eth1 -v -s0 -c3 -e -w ipV4.encapsulation.cap ip[9] == 41 &
