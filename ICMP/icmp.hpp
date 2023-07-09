#ifndef __ICMP__
#define __ICMP__

#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

typedef unsigned short int u16;
typedef unsigned int       u32;
typedef unsigned char      u8;

#define MESSAGE_SIZE 68 //  size of the payload (it can be any size (depend on server)) 

struct icmp
{

    u8 type;      // message type
    u8 code;      // subject code
    u16 checksum; // CRC checksum

    u16 id;       // unique id
    u16 sequence; // sequence number

    char msg[MESSAGE_SIZE]; // payload
};

void print_icmp(const icmp& icmp) {
  std::cout << "\033[1;31mType: " << (int)icmp.type << "\033[0m" << std::endl;
  std::cout << "\033[1;32mCode: " << (int)icmp.code << "\033[0m" << std::endl;
  std::cout << "\033[1;33mChecksum: " << (int)icmp.checksum << "\033[0m" << std::endl;
  std::cout << "\033[1;34mID: " << (int)icmp.id << "\033[0m" << std::endl;
  std::cout << "\033[1;35mSequence: " << (int) icmp.sequence << "\033[0m" << std::endl;
  std::cout << "\033[1;36mMessage: " << icmp.msg << "\033[0m" << std::endl;
}

u16 checksum(u8 *data,size_t length)
{

  u32 sum ;
  for (sum = 0; length > 1; length -= 2)
    sum += *data++;

  if (length == 1)
    sum += *(unsigned char*)data;

  sum = (sum >> 16) + (sum & 0xFFFF);
  sum += (sum >> 16);
  return ~sum;
}



#endif