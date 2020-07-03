#!/bin/bash
ifconfig eth0 up
ifconfig eth0 172.16.20.1/24
ifconfig eth0 down ##clears old
ifconfig eth0 up
route add -net 172.16.21.0/24 gw 172.16.20.254  ## can be ignored
route add default gw 172.16.20.254
