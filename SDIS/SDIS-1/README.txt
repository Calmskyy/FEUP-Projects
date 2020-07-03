Java SE version "1.8.0_201"

Open terminal and run the commands in the following order:

1 - javac *.java
2 - start rmiregistry (for Windows)/ rmiregistry & (for Linux)
3 - java CreatePeer 1.0 1 peer1 224.0.0.15 8001 224.0.0.16 8002 224.0.0.17 8003 

If you want to create another Peer open another terminal and do:

4 - java CreatePeer 2.0 2 peer2 224.0.0.15 8001 224.0.0.16 8002 224.0.0.17 8003 

In another terminal run the protocols:

-> java TestApp peer1 BACKUP 1.jpg 2
-> java TestApp peer1 RESTORE 1.jpg
-> java TestApp peer1 DELETE 1.jpg
-> java TestApp peer1 RECLAIM 100
-> java TestApp peer1 STATE