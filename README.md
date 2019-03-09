#Introduction

Simple program for sending a probe request to broadcast address.

#Get Started

1. Install libpcap-dev

2. Compile: gcc prober.c mac_address.c print_helpers.c 80211.h -l pcap

3. Run: sudo ./a.out interface ssid
