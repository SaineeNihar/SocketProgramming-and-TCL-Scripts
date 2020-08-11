#NetSys-T
#L3 Access Control rules

#Group1 to Computer B in WAN reject
$IPTABLES -A FORWARD -s 192.168.3.0/24 -d 10.0.0.0/8 -j REJECT

#Group2 to Group1 Reject
$IPTABLES -A FORWARD -s 192.168.5.0/24 -d 192.168.3.0/24 -j REJECT


#Group2 to Computer A in WAN reject
$IPTABLES -A FORWARD -s 192.168.5.0/24 -d 172.16.0.0/16 -j REJECT


#Group2 to DMZ only FTP
$IPTABLES -A FORWARD -s 192.168.5.0/24 -d 192.168.20.100/24 -p tcp --dport 21 -j ACCEPT
$IPTABLES -A FORWARD -s 192.168.5.0/24 -d 192.168.20.100/24 -p tcp --dport 20 -j ACCEPT
$IPTABLES -A FORWARD -s 192.168.5.0/24 -d 192.168.20.100/24 -j REJECT

#DNAT Rules

$IPTABLES -t nat -A PREROUTING -i WAN0 -p tcp --dport 21 -j DNAT --to-destination 192.168.20.100:21

#SNAT Rules

$IPTABLES -t nat -A POSTROUTING -s 192.168.3.0/24 -o WAN0 -p tcp -j SNAT --to-source 172.30.10.1:6000-7000
$IPTABLES -t nat -A POSTROUTING -s 192.168.5.0/24 -o WAN0 -p tcp -j SNAT --to-source 172.30.10.1:6000-7000
$IPTABLES -t nat -A POSTROUTING -s 192.168.20.0/24 -o WAN0 -p tcp -j SNAT --to-source 172.30.10.1:6000-7000

$IPTABLES -t nat -A POSTROUTING -s 192.168.3.0/24 -o WAN0 -p udp -j SNAT --to-source 172.30.10.1:6000-7000
$IPTABLES -t nat -A POSTROUTING -s 192.168.5.0/24 -o WAN0 -p udp -j SNAT --to-source 172.30.10.1:6000-7000
$IPTABLES -t nat -A POSTROUTING -s 192.168.20.0/24 -o WAN0 -p udp -j SNAT --to-source 172.30.10.1:6000-7000

$IPTABLES -t nat -A POSTROUTING -s 192.168.3.0/24 -o WAN0 -p icmp -j SNAT --to-source 172.30.10.1:6000-7000
$IPTABLES -t nat -A POSTROUTING -s 192.168.5.0/24 -o WAN0 -p icmp -j SNAT --to-source 172.30.10.1:6000-7000
$IPTABLES -t nat -A POSTROUTING -s 192.168.20.0/24 -o WAN0 -p icmp -j SNAT --to-source 172.30.10.1:6000-7000
