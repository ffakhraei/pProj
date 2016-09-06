#! /bin/bash 
clear
# This scrip is used to securely copy the .ssh folder to all machines on the network for the first time in order to allow for passwordless connections in the future
GATEWAY=CS-VNL
FILE_SERVER=Seasons
CLIENTS=(Seasons Summer Fall Equinox April June September January December November Spring August Autumn May July Winter February October Solstice Year March)

echo "The Gateway is: "$GATEWAY
echo "The File Server is: " $FILE_SERVER
echo "The Clients are: " ${CLIENTS[*]}


echo "******************************"
echo "Starting the SSH sequence."
echo "******************************"
for CLIENT in {0..20} 
do
        clear
        echo ${CLIENTS[CLIENT]}
        scp -r /home/ffakhrae/.ssh ${CLIENTS[CLIENT]}:/home/ffakhrae
done

