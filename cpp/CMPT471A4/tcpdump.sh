echo "Usage: ./tcpdump PORT_NUMBER"
sudo tcpdump -i any -s0 -v -w capture.cap tcp port $1
