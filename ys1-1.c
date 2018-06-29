#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#define HOST "challenge.yuansuan.cn"
#define PORT "7042"
#define oops(m) {perror(m); exit(1);}


void handleShark(int sock);
void receiveData(int sock);
void decodeFrame(int sock);



int main() {
    int sock_id, rc;
    struct addrinfo * info, dint;
    char buf[BUFSIZ];

    memset(&dint, 0, sizeof(dint));

    dint.ai_socktype = SOCK_STREAM;
    dint.ai_family = AF_INET;

    rc = getaddrinfo(HOST, PORT, &dint, &info);
    
    if (rc == -1) {
        oops("getaddrinfo");
    }

    sock_id = socket(PF_INET, info->ai_socktype, info->ai_protocol);



    if (sock_id == -1) {
        oops("create socket");
    }

    if (connect(sock_id, info->ai_addr, info->ai_addrlen) == -1) {
        oops("connect error");
    }

    free(info);

    handleShark(sock_id);
    // while(1) {
    //     decodeFrame(sock_id);
    // }
    /*
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    decodeFrame(sock_id);
    */
   int i;
   for (i = 0; i < 100; i++) {
      // printf("i = %d\n", i);
       decodeFrame(sock_id);
       
   }

//    printf("i = %d\n", i);



    





    


    return 0;
}


void handleShark(int sock) {
    char buf[BUFSIZ];
    char * number;
    char handSharkMsg[BUFSIZ];
    unsigned int len;
    if (read(sock, buf, BUFSIZ) > 0) {
        printf("%s", buf);
        number = strchr(buf, ':') + 1;
        len = strlen(number);
        number[len - 1] = '\0';
        printf("number: %s, len is %d\n", number, len);
        sprintf(handSharkMsg, "IAM:%s:77875894q@gmail.com\n", number);
        printf("msg: %s\n", handSharkMsg);
        write(sock, handSharkMsg, strlen(handSharkMsg));
        read(sock, buf, BUFSIZ);
        printf("%s", buf);
    }
}

void receiveData(int sock) {
    char buf[BUFSIZ * 10];
    int rc;

    if ((rc = read(sock, buf, BUFSIZ * 10)) > 0) {
        printf("rc %d\n", rc);
    }
}

void decodeFrame(int sock) {
    char seq[4];
    char checksum[4];
    char len[4];
    char * data;

    if (read(sock, seq, 4) != 4) {
        return;
    }

    if (read(sock, checksum, 4) != 4) {
        return;
    }

    if (read(sock, len, 4) != 4) {
        return;
    }

    uint32_t s = ntohl(*(uint32_t *)seq);

    uint32_t l = ntohl(*(uint32_t *)len);

    printf("data length %u, seq is %u\n", l, s);
    data = (char *) malloc(l);

    read(sock, data, l);
}