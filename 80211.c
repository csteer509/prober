#include "80211.h"
#include "packet.h"

Packet * create_probe_request(uint8_t source_mac_address[6], int num_of_args, ...) {
    Packet *ret = malloc(sizeof(Packet));

    /* parse variable args */
    va_list variable_params;
    va_start(variable_params, num_of_args);
    size_t param_size = 0;
    struct frame_variable *params[num_of_args];
    for (int i = 0; i < num_of_args; i++) {
        struct frame_variable *cur = va_arg(variable_params,
                                            struct frame_variable *);
        param_size += cur->len + sizeof(struct frame_variable);
        params[i] = cur;
    }
    size_t size;
    
    size = sizeof(radioTapHeader)
         + sizeof(struct i80211_hdr)
         + param_size;

    ret->buffer = malloc(size);
    uint8_t *cur = ret->buffer;

    memcpy(cur, radioTapHeader, RADIOTAP_LEN);
    cur += RADIOTAP_LEN;

    struct i80211_hdr *hdr = (struct i80211_hdr *) cur;
    hdr->frame_ctrl = WLAN_FC_SUBTYPE_PROBE_REQ;
    hdr->duration_id = 0x0000;
    memcpy(hdr->addr1, BROADCAST_MAC, MAC_LEN);
    memcpy(hdr->addr3, BROADCAST_MAC, MAC_LEN);
    memcpy(hdr->addr2, source_mac_address, MAC_LEN);
    cur += sizeof(struct i80211_hdr);

    for (int i = 0; i < num_of_args; i++) {
        memcpy(cur, params[i], params[i]->len + sizeof(struct frame_variable));
        cur += params[i]->len + sizeof(struct frame_variable);
    }
    va_end(variable_params);
    ret->size = size;
    return ret;
}

struct beacon_pkt * create_beacon(struct beacon_pkt *b, int num_arg, ...) {
    b = malloc(sizeof(*b));

    va_list variable_params;
    va_start(variable_params, num_arg);
    size_t param_size = 0;
    struct frame_variable *params[num_arg];
    for (int i = 0; i < num_arg; i++) {
        struct frame_variable *cur = va_arg(variable_params, 
                                            struct frame_variable *);
        param_size += cur->len + sizeof(struct frame_variable);
        params[i] = cur;
    }
    b->size = RADIOTAP_LEN
                 + sizeof(struct i80211_hdr)
                 + sizeof(struct beacon_hdr)
                 + param_size;

    b->pkt = malloc(b->size);
    uint8_t *cur = b->pkt;
    memcpy(cur, radioTapHeader, RADIOTAP_LEN);
    cur+=RADIOTAP_LEN;

    b->hdr = (struct i80211_hdr *) cur;
    b->hdr->duration_id=0xffff;
    memcpy(b->hdr->addr1, BROADCAST_MAC, MAC_LEN);
    memcpy(b->hdr->addr2, BROADCAST_MAC, MAC_LEN);
    memcpy(b->hdr->addr3, BROADCAST_MAC, MAC_LEN);
    cur += sizeof(struct i80211_hdr);

    b->b_hdr = (struct beacon_hdr *) cur;
    b->b_hdr->interval = 0x0064;
    b->b_hdr->capability_info = 0x0431;
    cur += sizeof(struct beacon_hdr);

    for (int i = 0; i < num_arg; i++) {
        memcpy(cur, params[i], params[i]->len + sizeof(struct frame_variable));
        cur += params[i]->len + sizeof(struct frame_variable);
    }

    va_end(variable_params);
    return b;
}

struct frame_variable * create_frame_variable(uint8_t id, uint8_t len, const void * buf)
{
    struct frame_variable *v;
    v = malloc(sizeof(*v) + len); 
    v->id = id;
    v->len = len;
    memcpy(v->buf, buf, len);
    return v;
}
