#ifndef __DNS__
#define __DNS__

#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

typedef unsigned short int 		u16;
typedef unsigned int       		u32;
typedef unsigned char       	u8;


/*
The DNS header is a 12-byte structure that is present at the beginning of every DNS message. It contains information about the message, such as its type, class, and length. The DNS header is encoded in ASCII, and its format is as follows:

```
1  2  3  4  5  6  7  8  9  0  1  2
+-----+-----+-----+-----+-----+-----+-----+
| ID | QR | Opcode | AA | TC | RD | RA | Z | RCODE
+-----+-----+-----+-----+-----+-----+-----+
```

* ID: A 16-bit identifier that is assigned to each DNS message by the sender. This identifier is used to match responses to requests.
* QR: A 1-bit field that indicates whether the message is a query (0) or a response (1).
* Opcode: A 4-bit field that specifies the type of DNS message. The most common opcodes are:
    * QUERY (0): A request for information from a DNS server.
    * RESPONSE (1): A response to a DNS query.
    * NOTIFY (4): A notification from a DNS server that a zone has changed.
    * UPDATE (5): A request to update a DNS record.
* AA: A 1-bit field that indicates whether the response was authoritative. If this bit is set, the response should be considered to be the final authority on the requested information.
* TC: A 1-bit field that indicates whether the message is truncated. If this bit is set, the message is too long to fit in a single packet, and the rest of the message will be sent in a subsequent packet.
* RD: A 1-bit field that indicates whether the requester wants recursive processing. If this bit is set, the DNS server should perform recursive lookups to resolve the requested name.
* RA: A 1-bit field that indicates whether the DNS server supports recursive queries. If this bit is set, the DNS server can perform recursive lookups to resolve the requested name.
* Z: A 3-bit field that is reserved for future use.
* RCODE: A 4-bit field that indicates the status of the DNS query. The most common RCODEs are:
    * NOERROR (0): The query was successful.
    * FORMERR (1): The query was malformed.
    * SERVFAIL (2): The DNS server was unable to fulfill the request.
    * NXDOMAIN (3): The requested name does not exist.
    * TYPEERR (4): The requested type of record does not exist.
    * ERROR (5): An unspecified error occurred.

The DNS header is followed by a variable number of resource records, which contain the actual information that was requested.
*/

struct DNS_FLAGE
{
	enum QR
	{
		query = 0b0,
		response = 0b1,
	};
	enum opcode{
		standard_query = 0b00,
		inverse_query = 0b100,
		status_request = 0b1000,
	};
	enum AA{
		non_authoritative = 0b000000,
		authoritative = 0b100000
	};

	enum TC{
		truncation = 0b1000000,
	};

	enum RD{
		recursion_desired = 0b10000000,
	};
	enum RA{
		recursion_available = 0b10000000,
	};

	enum rcode{
		no_error = 0b0,
		format_error = 0x1000,
		server_failure = 0x10000,
		domain_not_exist = 0x100000,
		not_supported = 0x1000000,
		nonexecution = 0x1000000,
	};
};


struct DNS_HEADER
{
	u16 id;
	u16 flages;
	u16 question_count;
	u16 answer_count;
	u16 authoritative_count;
	u16 additional_count;
};

struct DNS_QUESTION
{	
	u16 qtype;
	u16 qclass;
};




struct DNS_ANSWER
{

	u16 name;
	u16 type;
	u16 class_;
	u32 ttl;
	u16 length;
	u8 ip[4];
};

void getans(unsigned char * data, DNS_ANSWER ans){

	ans.name = htons( *(unsigned short *) data);

	data = data+2;
	ans.type = htons(*(unsigned short *)data);
	
	data = data+2;
	ans.class_ = htons(*(unsigned short *)data);

	data = data+2;
	ans.ttl = htonl(*(unsigned int *)data);

	data = data+4;
	ans.length = htons(*(unsigned short *)data);
	data = data+2;
	
	ans.ip[0] = data[0];
	ans.ip[1] = data[1];
	ans.ip[2] = data[2];
	ans.ip[3] = data[3];

	printf("name : %d , type : %d , class : %d , TTL %d ,length %d , IP : %d.%d.%d.%d\n",ans.name,ans.type,ans.class_,ans.ttl,ans.length,ans.ip[0],ans.ip[1],ans.ip[2],ans.ip[3]);
}

void ChangetoDnsNameFormat(char *dns, char *host)
{
	size_t lock = 0, i;
	strcat(host, ".");

	for (i = 0; i < strlen(host); i++)
	{
		if (host[i] == '.')
		{
			*dns++ = i - lock;
			for (; lock < i; lock++)
			{
				*dns++ = host[lock];
			}
			lock++;
		}
	}
	*dns++ = '\0';
}


#endif 