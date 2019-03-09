#ifndef PACKET_H
#define PACKET_H

#include <stdlib.h>
#include <stdint.h>

typedef struct packet {
	size_t size;
	uint8_t * buffer;
} Packet;

#endif
