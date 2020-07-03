#! /usr/bin/bash

# Script for running a peer
# To be run in src/build directory

# Check number input arguments
argc=$#

if (( argc != 4 )) 
then
	echo "Usage: $0 <peer_id> <svc_access_point> <server_addr> <server_port>"
	exit 1
fi

# Assign input arguments to nicely named variables
peer_id=$1
svc_access_point=$2
server_addr=$3
server_port=$4

# Execute the program

java "-Djavax.net.ssl.keyStore=../keystore.jks" "-Djavax.net.ssl.keyStorePassword=password" "-Djavax.net.ssl.trustStore=../truststore.jks" "-Djavax.net.ssl.trustStorePassword=password" App ${peer_id} ${svc_access_point} ${server_addr} ${server_port}
# java "-Djavax.net.ssl.keyStore=keystore.jks" "-Djavax.net.ssl.keyStorePassword=password" "-Djavax.net.ssl.trustStore=truststore.jks" "-Djavax.net.ssl.trustStorePassword=password" App 1 1 127.0.0.1 9669

