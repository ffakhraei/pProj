#! /bin/bash -u

clear 
date | tee log.redirect.txt
echo " This script captures ICMP REDIRECT messages for a target host/network." | tee -a log.redirect.txt
echo " The user is prompted to enter the target host, then the routing table of the host is modified so that instead of the default route, the seocond router attached to the subnetwork is used to reach the host/network." | tee -a log.redirect.txt
echo " tracepath and route -Cn commands are used to display the current and modified routing table and path to the target host."  | tee -a log.redirect.txt
echo " Due to some technicalities, a list of targets in the immediate (clockwise) subnetwork, adjacent to the current host is displayed."  | tee -a log.redirect.txt
echo " tcpdump is used to capture the message and save it in a file \"redirect.cap\" and is displayed using tcpdump command." | tee -a log.redirect.txt
echo " It is also possible to open and view the .cap file in Wireshark, if so desired." | tee -a log.redirect.txt
echo " A log file of the execution of this script is saved in \"log.redirect.txt\" and can be viewed at a later date." | tee -a log.redirect.txt
sleep 6
clear

#--------------------------------------------------------------------------------
# VARIABLES
#--------------------------------------------------------------------------------

NET16=(summer fall equinox april june september)
NET17=(august autumn spring november)
NET18=(may july winter)
NET19=(october solstice year)
ROUTERS=(december march february january)
ALL_HOSTS=(april june september summer fall equinox august november autumn spring may july winter october solstice year)
JANUARY_NET17=172.17.1.1
JANUARY_NET16=172.16.1.1
DECEMBER_NET16=172.16.1.12
DECEMBER_NET18=172.18.1.12
MARCH_NET18=172.18.1.3
MARCH_NET19=172.19.1.3
FEBRUARY_NET19=172.19.1.2
FEBRUARY_NET17=172.17.1.2
NET16_DEFAULT_ROUTER=$DECEMBER_NET16
NET16_ALTERNATE_ROUTER=$JANUARY_NET16
NET17_DEFAULT_ROUTER=$JANUARY_NET17
NET17_ALTERNATE_ROUTER=$FEBRUARY_NET17
NET18_DEFAULT_ROUTER=$MARCH_NET18
NET18_ALTERNATE_ROUTER=$DECEMBER_NET18
NET19_DEFAULT_ROUTER=$FEBRUARY_NET19
NET19_ALTERNATE_ROUTER=$MARCH_NET19


#--------------------------------------------------------------------------------
# FUNCTIONS
#--------------------------------------------------------------------------------


# reset_interface():
# Postcondition: routing table is reset to its original state. eth1 is up and configured correctly                
reset_interface()
{
    sudo ifconfig eth1 down &> /dev/null  && sudo ifdown eth1 &> /dev/null       # > /dev/null 2>&1 for only STDERR piping 
    sleep 1
    sudo ifconfig eth1 up &> /dev/null && sudo ifup eth1 &> /dev/null
}

# reset_target_interface():
# Precondition: target host is a valid host, and is reachable via admin network
# Postcondition: target host's routing table is reset to its original state and eth1 NIC is up
reset_target_interface()
{
    ssh -tt $USER@$TARGET_HOST 'sudo ifconfig eth1 down && sudo ifdown eth1 > /dev/null 2>&1; sleep 1.5; sudo ifconfig eth1 up && sudo ifup eth1 > /dev/null 2>&1'
}

# print_target_list()
# Postcondition: a list of valid targets is displayed to the user
print_target_list()
{
    for i in ${NET16[*]}; do
        if [[ $i =~ $HOSTNAME ]]; then
            TARGET_LIST=(may july winter)
        fi
    done

    for i in ${NET17[*]}; do
        if [[ $i =~ $HOSTNAME ]]; then
            TARGET_LIST=(april june september summer fall equinox)
        fi
    done

    for i in ${NET18[*]}; do
        if [[ $i =~ $HOSTNAME ]]; then
            TARGET_LIST=(october solstice year)
        fi
    done

    for i in ${NET19[*]}; do
        if [[ $i =~ $HOSTNAME ]]; then
            TARGET_LIST=(august november autumn spring)
        fi
    done

    for i in ${TARGET_LIST[*]}; do
        echo $i
    done
    echo "->"; echo
}

# get_target_info()
# Postcondition: target host's IP (admin network) and the subnetwork that it belongs to are stored in $TARGET_SUBNET_IP, $TARGET_ADMIN_IP and $TARGET_SUBNET
get_target_info()
{ 

    for i in ${NET16[*]}; do
        if [[ $i =~ $TARGET_HOST ]]; then
            TARGET_SUBNET=net16
        fi
    done

    for i in ${NET17[*]}; do
        if [[ $i =~ $TARGET_HOST ]]; then
            TARGET_SUBNET=net17
        fi
    done

    for i in ${NET18[*]}; do
        if [[ $i =~ $TARGET_HOST ]]; then
            TARGET_SUBNET=net18
        fi
    done

    for i in ${NET19[*]}; do
        if [[ $i =~ $TARGET_HOST ]]; then
            TARGET_SUBNET=net19
        fi
    done

    TARGET_SUBNET_IP=$(nmblookup -A $TARGET_HOST.$TARGET_SUBNET | awk '{print $5;}')
    TARGET_ADMIN_IP=$(nmblookup -A $TARGET_HOST | awk '{print $5;}')
}


# get_host_info()
# Postcondition: current host's admin IP, sub network, and subnetwork IP are stored in $HOST_ADMIN_IP, $HOST_SUBNET_IP and $HOST_SUBNET
get_host_info()
{
    for i in ${NET16[*]}; do
        if [[ $i =~ $HOSTNAME ]]; then
            HOST_SUBNET=net16
            DEFAULT_ROUTER=$NET16_DEFAULT_ROUTER
            ALTERNATE_ROUTER=$NET16_ALTERNATE_ROUTER
            NET_ROUTE_CHANGE=172.18.0.0/16
        fi
    done

    for i in ${NET17[*]}; do
        if [[ $i =~ $HOSTNAME ]]; then
            HOST_SUBNET=net17
            DEFAULT_ROUTER=$NET17_DEFAULT_ROUTER
            ALTERNATE_ROUTER=$NET17_ALTERNATE_ROUTER
            NET_ROUTE_CHANGE=172.16.0.0/16
        fi
    done

    for i in ${NET18[*]}; do
        if [[ $i =~ $HOSTNAME ]]; then
            HOST_SUBNET=net18
            DEFAULT_ROUTER=$NET18_DEFAULT_ROUTER
            ALTERNATE_ROUTER=$NET18_ALTERNATE_ROUTER
            NET_ROUTE_CHANGE=172.19.0.0/16
        fi
    done

    for i in ${NET19[*]}; do
        if [[ $i =~ $HOSTNAME ]]; then
            HOST_SUBNET=net19
            DEFAULT_ROUTER=$NET19_DEFAULT_ROUTER
            ALTERNATE_ROUTER=$NET19_ALTERNATE_ROUTER
            NET_ROUTE_CHANGE=172.17.0.0/16
        fi
    done

    HOST_SUBNET_IP=$(nmblookup -A $HOSTNAME.$HOST_SUBNET | awk '{print $5;}')
    HOST_ADMIN_IP=$(nmblookup -A $HOSTNAME | awk '{print $5;}')
}




### list of functions:
# reste_interface()
# reset_target_interface()
# print_target_list()
# get_target_info()
# get_host_info()



#--------------------------------------------------------------------------------
# MAIN BODY
#--------------------------------------------------------------------------------

clear
echo " Please enter a target host from the follwoing list: " | tee -a log.redirect.txt
print_target_list | tee -a log.redirect.txt
read TARGET_HOST

clear
echo >> log.redirect.txt
echo " Initializing variables belonging to $HOSTNAME and $TARGET_HOST."
echo " Please stand by...."
reset_interface
reset_target_interface
get_host_info
get_target_info
echo " Initialization complete."
sleep 2

clear
echo " You are currently running the script \"redirect.sh\" on \"$HOSTNAME\" with admin IP address: \"$HOST_ADMIN_IP\""  | tee -a log.redirect.txt 
echo " \"$HOSTNAME\" belongs to subnetwork \"$HOST_SUBNET\" with IP address: \"$HOST_SUBNET_IP\"" | tee -a log.redirect.txt
echo | tee -a log.redirect.txt
echo " The target you chose is \"$TARGET_HOST\" with admin IP address: \"$TARGET_ADMIN_IP\"" | tee -a log.redirect.txt
echo " \"$TARGET_HOST\" belongs to subnetowrk \"$TARGET_SUBNET\" with IP address: \"$TARGET_SUBNET_IP\"" | tee -a log.redirect.txt
echo " The default router from \"$HOSTNAME\" to \"$TARGET_HOST\" in \"$NET_ROUTE_CHANGE\" is \"$DEFAULT_ROUTER\"." | tee -a log.redirect.txt
sleep 4
echo >> log.redirect.txt

clear
echo " The default routing table of $HOSTNAME is: " | tee -a log.redirect.txt
route -n | tee -a log.redirect.txt
echo | tee -a log.redirect.txt
echo " The default routing cache of $HOSTNAME is: " | tee -a log.redirect.txt
route -Cn | tee -a log.redirect.txt
echo | tee -a log.redirect.txt
echo " The default path to $TARGET_HOST.$TARGET_SUBNET is: " | tee -a log.redirect.txt
tracepath -n $TARGET_HOST.$TARGET_SUBNET | tee -a log.redirect.txt
echo | tee -a log.redirect.txt
sleep 4

sudo tcpdump -i any -c 1 -s0 -e -w redirect.cap icmp[icmptype] == 5 &

sleep 2
clear
echo " Applying changes to the routing table.... " | tee -a log.redirect.txt
sudo ip route add $NET_ROUTE_CHANGE via $ALTERNATE_ROUTER
sudo ip route add $TARGET_SUBNET_IP via $ALTERNATE_ROUTER
echo " Process complete... " | tee -a log.redirect.txt
echo | tee -a log.redirect.txt
sleep 1.5
clear
echo " Starting the sequence to capture ICMP REDIRECT message.... " | tee -a log.redirect.txt 
echo | tee -a log.redirect.txt
sleep 3

clear
echo " The modified path to $TARGET_HOST is: " | tee -a log.redirect.txt
tracepath -n $TARGET_HOST.$TARGET_SUBNET | tee -a log.redirect.txt
echo | tee -a log.redirect.txt
echo " The modified routing table of $HOSTNAME is: " | tee -a log.redirect.txt
route -n | tee -a log.redirect.txt
echo | tee -a log.redirect.txt
echo " The modified routing cache of $HOSTNAME is: " | tee -a log.redirect.txt
route -Cn | tee -a log.redirect.txt
echo | tee -a log.redirect.txt
sleep 1


tracepath -n $TARGET_HOST.$TARGET_SUBNET &> /dev/null
tracepath -n $TARGET_HOST.$TARGET_SUBNET &> /dev/null
tracepath -n $TARGET_HOST.$TARGET_SUBNET &> /dev/null

sleep 3
clear
echo " The updated routing table of $HOSTNAME is: " | tee -a log.redirect.txt
route -n | tee -a log.redirect.txt
echo | tee -a log.redirect.txt
echo " The updated routing cache of $HOSTNAME is: " | tee -a log.redirect.txt
route -Cn | tee -a log.redirect.txt
echo | tee -a log.redirect.txt
echo " The updated path to $TARGET_HOST is: " | tee -a log.redirect.txt
tracepath -n $TARGET_HOST.$TARGET_SUBNET | tee -a log.redirect.txt
echo | tee -a log.redirect.txt
sleep 4

clear
echo " Restoring the routing table on \"$HOSTNAME\" to its original state.... " | tee -a log.redirect.txt
reset_interface
echo " Process complete... " | tee -a log.redirect.txt
echo | tee -a log.redirect.txt
sleep 2

clear
echo " Displaying the captured message(s): " | tee -a log.redirect.txt
echo | tee -a log.redirect.txt
sudo tcpdump -vvvXX -r redirect.cap | tee -a log.redirect.txt


echo; echo; echo
echo " Have a beautiful time! "
echo " Farzin Fakhraei "
