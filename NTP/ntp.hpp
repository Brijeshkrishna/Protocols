#ifndef __NTP__
#define __NTP__

#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

typedef unsigned short int 		u16;
typedef unsigned int       		u32;
typedef unsigned char       	u8;


// NTP packet structure
struct ntp_packet {
    u8 flags;                   // Leap indicator, Version number, Mode
    u8 stratum;                 // Stratum level of the local clock
    u8 poll;                    // Maximum interval between successive messages
    u8 precision;               // Precision of the local clock
    u32 root_delay;             // Round trip time to the primary reference source
    u32 root_dispersion;        // Maximum error relative to the primary reference source
    u32 reference_id;           // Reference identifier
    u32 reference_timestamp[2]; // Reference timestamp
    u32 originate_timestamp[2]; // Originate timestamp
    u32 receive_timestamp[2];   // Receive timestamp
    u32 transmit_timestamp[2];  // Transmit timestamp
};


#endif
