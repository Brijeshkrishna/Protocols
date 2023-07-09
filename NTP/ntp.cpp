#include "ntp.hpp"




int main() {
    int sock;
    struct sockaddr_in server_addr;
    struct ntp_packet request, response;

    // Create a UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);


   
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(123);
    server_addr.sin_addr.s_addr = inet_addr("162.159.200.123");
    

    // Prepare the NTP request packet
    request.flags = 0x1B;

    // Send the NTP request
    sendto(sock, &request, sizeof(request), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
       

    // Receive the NTP response
    socklen_t server_addr_len = sizeof(server_addr);
    recvfrom(sock, &response, sizeof(response), 0, (struct sockaddr*)&server_addr, &server_addr_len);
    

    // Print the Transmit Timestamp from the response
    u32 transmit_seconds = ntohl(response.transmit_timestamp[0]);
    u32 transmit_fraction = ntohl(response.transmit_timestamp[1]);
    time_t transmit_time = (transmit_seconds - 2208988800U) + (transmit_fraction / (double)0x100000000U);
    printf("Transmit Timestamp: %s", ctime(&transmit_time));

    close(sock);
    return 0;
}
