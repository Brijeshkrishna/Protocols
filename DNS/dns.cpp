#include "dns.hpp"

using namespace std;


int main(int argc, char *argv[])
{
	
	struct sockaddr_in dest;
	char buf[1000];

	bzero((void *)&buf,sizeof(buf));

	int sock = socket(AF_INET, SOCK_DGRAM, 0);

	dest.sin_family = AF_INET; // IP4
	dest.sin_port = htons(53); // DNS PORT 53
	dest.sin_addr.s_addr = inet_addr("8.8.8.8"); // google DNS server IP

	DNS_HEADER *dns = (DNS_HEADER *)&buf;

	dns->id = 0;   // unique id 
	dns->flages = htons(0x00101); // for request 
	dns->answer_count = 0; // answer 0 for request
	dns->question_count = htons(1); // requied IP for 1 domain
	dns->additional_count = 0; 
	dns->authoritative_count = 0;


	char *web = argv[1];

	ChangetoDnsNameFormat(&buf[sizeof(DNS_HEADER)], web); // fill the DNS header 

	DNS_QUESTION *q = (DNS_QUESTION *)&buf[sizeof(DNS_HEADER) + strlen(web) + 1]; // fill the question field
	q->qtype = htons(1);
	q->qclass = htons(1);

	// send the request
	sendto(sock, buf, sizeof(struct DNS_HEADER) + sizeof(DNS_QUESTION) + strlen(web) + 1, 0, (struct sockaddr *)&dest, sizeof(dest));

	// recv the responce 
	socklen_t r;
	recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&dest,&r);

	// move the pointer to the answer field
	unsigned char *data = (unsigned char *)&buf[sizeof(DNS_HEADER) + sizeof(DNS_QUESTION) + strlen(web) + 1];

	// read the answer 
	DNS_ANSWER a;
	getans(data,a);
		
	return 0;
}
