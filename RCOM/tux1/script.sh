#!/bin/bash
configure terminal #fisrt check that every ip is right
vlan 20
vlan 21 
interface fastethernet 0/1
switchport mode access
switchport access vlan 20
interface fastethernet 0/4
switchport mode access
switchport access vlan 20
interface fastethernet 0/4
switchport mode access
switchport access vlan 21
interface fastethernet 0/6
switchport mode access
switchport access vlan 20
interface fastethernet 0/8
switchport mode access
switchport access vlan 21




