# ComnetsPBL_WSN
Instructions and codebase(s) for the Comnets3 PBL WSN project. 2025/2026

# make command line:
- `make BOARD="seeedstudio-xiao-nrf52840" RIOTBASE="$HOME/ComnetsPBL_WSN/RIOT" PORT="/dev/ttyACM0" UF2_SOFTDEV=DROP WERROR=0 flash term`
- This line should build your project and flash the binary to the board at 
- Where: 
- RIOTBASE should point to the RIOT directory we're using (the one in this repo)   
- PORT is the serial port you want to flash the firmware to
- If you add the `term` argument it will open serial comms to the board where you can run commands. If you do not have the `flash` argument and only the `term` argument, it will get you the shell without flashing the device.

# Task 1) Get familiar with this workflow
- Go to the `gnrc_networking` directory in the root of this repo.
- Run the `make` command line noted above. Flash all of your boards.
- If you had added the `term` argument, it should take you to a shell with the device. 
- Open a shell to both of your devices. 
- Run `udp server start 1` on one device. This will be your `Receiver` node and the other device will be your `Transmitter` node.
- Run `ifconfig` on both. Here you should see the MAC and the (automatically assigned) IPv6 addresses. 
- Test for connectivity by pinging. From the shell of one of your devices do `ping <ip address>` where <ip address> is the IPv6 of your other device. The output should look like:
```
> ping fe80::aca5:e855:c919:2044
ping fe80::aca5:e855:c919:2044
12 bytes from fe80::aca5:e855:c919:2044%7: icmp_seq=0 ttl=64 rssi=-38 dBm time=5.609 ms
12 bytes from fe80::aca5:e855:c919:2044%7: icmp_seq=1 ttl=64 rssi=-38 dBm time=9.103 ms
12 bytes from fe80::aca5:e855:c919:2044%7: icmp_seq=2 ttl=64 rssi=-37 dBm time=7.502 ms

--- fe80::aca5:e855:c919:2044 PING statistics ---
3 packets transmitted, 3 packets received, 0% packet loss
round-trip min/avg/max = 5.609/7.404/9.103 ms

```
- Once you verify that the devices can talk to one another, run the following on your `Transmitter` node: `udp send <Receiver IP address> 1 aaaa`
- This will send the payload string `aaaa` to the IP address of the receiver, port number 1, where the UDP server should be listening on. Verify on the other device that our data came through. Should look like this:

Transmitter side:
```
> udp send fe80::aca5:e855:c919:2044 1 asd
Success: sent 3 byte(s) to [fe80::aca5:e855:c919:2044]:1
```
Receiver side:
```
> PKTDUMP: data received:
~~ SNIP  0 - size:   3 byte, type: NETTYPE_UNDEF (0)
00000000  61  73  64
~~ SNIP  1 - size:   8 byte, type: NETTYPE_UDP (4)
   src-port:     1  dst-port:     1
   length: 11  cksum: 0x9d32
~~ SNIP  2 - size:  40 byte, type: NETTYPE_IPV6 (2)
traffic class: 0x00 (ECN: 0x0, DSCP: 0x00)
flow label: 0x00000
length: 11  next header: 17  hop limit: 64
source address: fe80::ec0a:1a43:ebf7:2f8f
destination address: fe80::aca5:e855:c919:2044
~~ SNIP  3 - size:  24 byte, type: NETTYPE_NETIF (-1)
if_pid: 7  rssi: -40  lqi: 212
flags: 0x0
src_l2addr: EE:0A:1A:43:EB:F7:2F:8F
dst_l2addr: AE:A5:E8:55:C9:19:20:44
~~ PKT    -  4 snips, total size:  75 byte

```

# Task 2) One (or more) transmitter, one receiver
- TBA


