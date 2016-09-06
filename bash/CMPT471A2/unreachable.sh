#! /bin/bash -u

clear 
date | tee log.unreachable.txt
echo " This script captures ICMP destination unreachable messages for a target host." | tee -a log.unreachable.txt
echo " The user is prompted to enter the target host, then the eth1 interface of the target host is turned off." | tee -a log.unreachable.txt
echo " Target is pinged and the ICMP message is captured using tcpdump." | tee -a log.unreachable.txt
echo " The captured message is saved in a file \"unreachable.cap\" and displayed using tcpdump command." | tee -a log.unreachable.txt
echo " It is also possible to open and view the .cap file in Wireshark, if so desired." | tee -a log.unreachable.txt
echo " A log file of the execution of this script is saved in \"log.unreachable.txt\" and can be viewed at a later date." | tee -a log.unreachable.txt
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
REMOVE_HOST=($HOSTNAME)
ALL_HOSTS=(april june september summer fall equinox august november autumn spring may july winter october solstice year)
TARGET_LIST=(${ALL_HOSTS[@]/$REMOVE_HOST})


#--------------------------------------------------------------------------------
# FUNCTIONS
#--------------------------------------------------------------------------------


# list of functions:
# reste_interface()
# turn_off_target_eth1()
# reset_target_interface()
# print_target_list()
# get_target_info()
# get_host_info()


# reset_interface():
# Postcondition: routing table is reset to its original state. eth1 is up and configured correctly                
reset_interface()
{
    sudo ifconfig eth1 down &> /dev/null  && sudo ifdown eth1 &> /dev/null       # > /dev/null 2>&1 for only STDERR piping 
    sleep 1
    sudo ifconfig eth1 up &> /dev/null && sudo ifup eth1 &> /dev/null
}

# turn_off_target_eth1():
# Precondition: target host is a valid host, and it is reachable via admin network.
# Postcondition: target host's eth1 NIC is down
turn_off_target_eth1()
{
    ssh -tt $USER@$TARGET_HOST 'sudo ifconfig eth1 down && sudo ifdown eth1 > /dev/null 2>&1'
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
        fi
    done

    for i in ${NET17[*]}; do
        if [[ $i =~ $HOSTNAME ]]; then
            HOST_SUBNET=net17
        fi
    done

    for i in ${NET18[*]}; do
        if [[ $i =~ $HOSTNAME ]]; then
            HOST_SUBNET=net18
        fi
    done

    for i in ${NET19[*]}; do
        if [[ $i =~ $HOSTNAME ]]; then
            HOST_SUBNET=net19
        fi
    done

    HOST_SUBNET_IP=$(nmblookup -A $HOSTNAME.$HOST_SUBNET | awk '{print $5;}')
    HOST_ADMIN_IP=$(nmblookup -A $HOSTNAME | awk '{print $5;}')
}


# print_target_ifconfig()
# Postcondition: ifconfig information of the target are displayed
print_target_ifconfig()
{
    ssh -tt $TARGET_HOST 'ifconfig'
}


### list of functions:
# reste_interface()
# turn_off_target_eth1()
# reset_target_interface()
# print_target_list()
# get_target_info()
# get_host_info()
# print_targe_ifconfig()


#--------------------------------------------------------------------------------
# MAIN BODY
#--------------------------------------------------------------------------------

clear
echo " Please enter a target host from the follwoing list: " | tee -a log.unreachable.txt
print_target_list | tee -a log.unreachable.txt
read TARGET_HOST

clear
echo >> log.unreachable.txt
echo " Initializing variables belonging to $HOSTNAME and $TARGET_HOST."
echo " Please stand by...."
reset_interface
reset_target_interface
get_host_info
get_target_info
echo " Initialization complete."
sleep 2

clear
echo " You are currently running the script \"unreachable.sh\" on \"$HOSTNAME\" with admin IP address: \"$HOST_ADMIN_IP\""  | tee -a log.unreachable.txt 
echo " \"$HOSTNAME\" belongs to subnetwork \"$HOST_SUBNET\" with IP address: \"$HOST_SUBNET_IP\"" | tee -a log.unreachable.txt
echo | tee -a log.unreachable.txt
echo " The target you chose is \"$TARGET_HOST\" with admin IP address: \"$TARGET_ADMIN_IP\"" | tee -a log.unreachable.txt
echo " \"$TARGET_HOST\" belongs to subnetowrk \"$TARGET_SUBNET\" with IP address: \"$TARGET_SUBNET_IP\"" | tee -a log.unreachable.txt
sleep 2.5
echo >> log.unreachable.txt

clear 
echo " Turning off eth1 NIC on \"$TARGET_HOST\" ...." | tee -a log.unreachable.txt
turn_off_target_eth1
echo " Process complete... " | tee -a log.unreachable.txt
sleep 2
echo >> log.unreachable.txt

clear
print_target_ifconfig | tee -a log.unreachable.txt
sleep 2
echo >> log.unreachable.txt

clear
echo " Starting the sequence to capture ICMP UNREACHABLE message.... " | tee -a log.unreachable.txt 
#ping -c 10 -W 2 $TARGET_HOST.$TARGET_SUBNET | sudo tcpdump -i any -c 3 -v -s0 -e -w unreachable.cap 'icmp[icmptype] == 3'
tracepath $TARGET_HOST.$TARGET_SUBNET | sudo tcpdump -i any -c 3 -v -s0 -e -w unreachable.cap 'icmp[icmptype] == 3'
echo | tee -a log.unreachable.txt
echo " Process complete... " | tee -a log.unreachable.txt
sleep 2

clear
echo | tee -a log.unreachable.txt
echo " Restoring eth1 NIC on \"$TARGET_HOST\" .... " | tee -a log.unreachable.txt
reset_target_interface
echo " Process complete... " | tee -a log.unreachable.txt
print_target_ifconfig | tee -a log.unreachable.txt
echo | tee -a log.unreachable.txt
sleep 2

clear
echo " Displaying the captured message(s): " | tee -a log.unreachable.txt
echo | tee -a log.unreachable.txt
sudo tcpdump -vvvXX -r unreachable.cap | tee -a log.unreachable.txt


echo; echo; echo
echo " Have a beautiful time! "
echo " Farzin Fakhraei "
