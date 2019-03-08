#ifndef PACKET_H
#define PACKET_H

typedef struct packet {
	size_t size;
	uint8_t * buffer;
} Packet;

#endif
