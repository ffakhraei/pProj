#! /bin/bash 
clear
# This scrip is used to securely connect to all machines on the network for the first time
GATEWAY=CS-VNL
FILE_SERVER=Seasons
CLIENTS=(Seasons Summer Fall Equinox April June September January December November Spring August Autumn May July Winter February October Solstice Year March)

echo "The Gateway is: "$GATEWAY
echo "The File Server is: " $FILE_SERVER
echo "The Clients are: " ${CLIENTS[*]}

sleep 1
clear

echo "******************************"
echo "Starting the SSH sequence."
echo "******************************"
sleep 1
for CLIENT in {0..20} 
do
	clear
	echo ${CLIENTS[CLIENT]}
	ssh ${CLIENTS[CLIENT]} << EOF
		set HOSTNAME=hostname
		sleep 1
		echo "Successfully connected to " $HOSTNAME
		echo "Closing the connection now..."
		sleep 1
		exit	
EOF
done
