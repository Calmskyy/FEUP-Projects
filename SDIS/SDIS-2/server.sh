# To be run in src/build directory

# Check number input arguments
argc=$#

if (( argc != 1 )) 
then
	echo "Usage: $0 <server_port>"
	exit 1
fi

# Assign input arguments to nicely named variables
server_port=$1

# Execute the program

java "-Djavax.net.ssl.keyStore=../keystore.jks" "-Djavax.net.ssl.keyStorePassword=password" "-Djavax.net.ssl.trustStore=../truststore.jks" "-Djavax.net.ssl.trustStorePassword=password" Server ${server_port}
