
#include "icmp.hpp"



int main(int argc, char *argv[])
{


    icmp pack;

    sockaddr_in serv_add;

    pack.type = 8;
    pack.code = 0;
    pack.sequence = 1;
    pack.id = htons(3853);
    
    strcpy(pack.msg, argv[2]);
    pack.checksum = 0;


    pack.checksum = checksum((u8*)&pack,sizeof(pack));


    serv_add.sin_family = AF_INET;
    serv_add.sin_port = htons(0);
    serv_add.sin_addr.s_addr = inet_addr(argv[1]);

    // create socket
    int sock = socket(AF_INET, SOCK_DGRAM, 1);

    sendto(sock, &pack, sizeof(pack) , 0, (struct sockaddr *)&serv_add, sizeof(serv_add));
    
    bzero((void*)&pack, sizeof(pack));

    socklen_t a = 0;
    recvfrom(sock, &pack, sizeof(pack), 0, (struct sockaddr *)&serv_add, &a);


    print_icmp(pack);
    

    return 0;
}


