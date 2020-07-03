# t7g027
java version "1.8.0_151"

**SCRIPTS** 
- compile.sh - compiles all files <br/>
- rmiregistry.sh - starts the rmi <br/>
- server.sh <server_port> - starts the server <br/>
- peer.sh <peer_id> <svc_access_point> <server_addr> <server_port> - starts a peer <br/>
- cleanup.sh <peerID> - delete peer's fileSystem
- test.sh  <peer_ap> BACKUP|RESTORE|DELETE|RECLAIM|STATE [<opnd_1> [<optnd_2]] - executes a subprotocol <br/>
<br/>

**HOW TO RUN WITH SCRIPTS**
 - Open TERMINAL1 and in directory src run script compile.sh ; then change to directory src/build and run script rmiregistry.sh
 - Open TERMINAL2 and start the server by running the script server.sh in the src/build directory
 - Open TERMINAL3 and start peer 1 by running the script peer.sh in the src/build directory
 - Open TERMINAL4 and start peer 2  by running the script peer.sh in the src/build directory
 - Open TERMINAL5 and execute a subprotocol by running the script test.sh in the src/build directory

 Ps: you can start as many peers as you would like 
<br/><br/><br/>


**COMPILING:** in directory src <br/>
&nbsp;&nbsp;rm -rf build <br/>
&nbsp;&nbsp;mkdir -p build <br/>
&nbsp;&nbsp;javac -d build *.java<br/>
<br/>
&nbsp;&nbsp;OR<br/>
<br/>
&nbsp;&nbsp;bash compile.sh<br/>
<br/>
**STARTING RMI:** in directory src/build <br/>
&nbsp;&nbsp;rmiregistry <br/>
<br/>
&nbsp;&nbsp;OR<br/>
<br/>
&nbsp;&nbsp;bash rmiregistry.sh<br/>
<br/>

**STARTING SERVER:** in directory src/build <br/>
&nbsp;&nbsp;java "-Djavax.net.ssl.keyStore=keystore.jks" "-Djavax.net.ssl.keyStorePassword=password" "-Djavax.net.ssl.trustStore=truststore.jks" "-Djavax.net.ssl.trustStorePassword=password" Server <server_port> <br/>
&nbsp;&nbsp;Ex: java "-Djavax.net.ssl.keyStore=keystore.jks" "-Djavax.net.ssl.keyStorePassword=password" "-Djavax.net.ssl.trustStore=truststore.jks" "-Djavax.net.ssl.trustStorePassword=password" Server 9669
<br/>
<br/>
&nbsp;&nbsp;OR<br/>
<br/>
&nbsp;&nbsp;bash server.sh <server_port><br/>
&nbsp;&nbsp;Ex: bash server.sh 9669
<br/>

**STARTING PEERS:** in directory src/build <br/>
&nbsp;&nbsp;java "-Djavax.net.ssl.keyStore=keystore.jks" "-Djavax.net.ssl.keyStorePassword=password" "-Djavax.net.ssl.trustStore=truststore.jks" "-Djavax.net.ssl.trustStorePassword=password" App <peer_id> <svc_access_point> <server_addr> <server_port> <br/>
&nbsp;&nbsp;Ex: java "-Djavax.net.ssl.keyStore=keystore.jks" "-Djavax.net.ssl.keyStorePassword=password" "-Djavax.net.ssl.trustStore=truststore.jks" "-Djavax.net.ssl.trustStorePassword=password" App 1 1 127.0.0.1 9669
<br/>
<br/>
&nbsp;&nbsp;OR<br/>
<br/>
&nbsp;&nbsp;bash peer.sh <peer_id> <svc_access_point> <server_addr> <server_port> <br/>
&nbsp;&nbsp;Ex: bash peer.sh 1 1 127.0.0.1 9669
<br/>
	
**RUNNING WITH TESTAPP:** in directory src/build <br/>

- BACKUP: <br/>
&nbsp;&nbsp; java TestApp <peer_ap> BACKUP <file_path> <replication_degree> <br/>
&nbsp;&nbsp;Ex: java TestApp localhost/1 BACKUP "..\..\files\exemplo.txt" 1

- RESTORE: <br/>
&nbsp;&nbsp;java TestApp <peer_ap> RESTORE <file_path> <br/>
&nbsp;&nbsp;Ex: java TestApp localhost/1 RESTORE "..\..\files\exemplo.txt"

- DELETE: <br/>
&nbsp;&nbsp;java TestApp <peer_ap> DELETE <file_path> <br/>
&nbsp;&nbsp;Ex: java TestApp localhost/1 DELETE "..\..\files\exemplo.txt"

- RECLAIM: <br/>
&nbsp;&nbsp;java TestApp <peer_ap> RECLAIM <maximum_disk_space> <br/>
&nbsp;&nbsp;Ex: java TestApp localhost/1 RECLAIM 0

- STATE: <br/>
&nbsp;&nbsp;java TestApp <peer_ap> STATE <br/>
&nbsp;&nbsp;Ex: java TestApp localhost/1 STATE

