#ifndef WIFI_H
#define WIFI_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include "packet.h"

#define RADIOTAP_LEN 18
#define MAC_LEN 6
#define WLAN_FC_TYPE_MGMT 0x0000
#define WLAN_FC_SUBTYPE_BEACON 0x0080
#define IEEE80211_STYPE_PROBE_RESP  0x0050
#define WLAN_FC_SUBTYPE_PROBE_REQ  0x0040
#define IEEE80211_STYPE_AUTH        0x00B0
#define IEEE80211_FCTL_RETRY        0x0800

static const uint8_t BROADCAST_MAC[6]= {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
static const uint8_t radioTapHeader[] = {
    0x00, 0x00,
    0x12, 0x00,
    0x2e, 0x48, 0x00, 0x00,
    0x00,
    0x02,
    0x6c, 0x09, 0xa0, 0x00,
    0xcd,
    0x00,
    0x00, 0x00
};

struct i80211_hdr {
    /* Defines the basic 80211 header, may need to edit this for cases where 4
     * addresses are needed
     */
    uint16_t frame_ctrl;
    uint16_t duration_id;
    uint8_t addr1[6];
    uint8_t addr2[6];
    uint8_t addr3[6];
    uint16_t seq_ctrl;
}__attribute__((packed));

struct frame_variable {
    /* Defines a a simple TLV structure that is used accross control frame 
     * messages.
     */
    uint8_t id;
    uint8_t len;
    uint8_t buf[];
}__attribute__((packed));

static const struct frame_variable BROADCAST_SSID = { 0 , 0 , 0 };

struct beacon_hdr {
    uint64_t timestamp;
    uint16_t interval;
    uint16_t capability_info;
}__attribute__((packed));

struct beacon_pkt {
    size_t size;
    struct i80211_hdr *hdr;
    struct beacon_hdr *b_hdr;
    uint8_t *pkt;
};

struct frame_variable * create_frame_variable(uint8_t id, uint8_t len, const void * buf);

struct beacon_pkt * create_beacon(struct beacon_pkt *b, int num_arg, ...);

Packet * create_probe_request(uint8_t source_mac_address[6], int num_of_args, ...);

#endif
