#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#define oops(m) {perror(m); exit(1);}
#define HOST "challenge.yuansuan.cn"
#define PORT "7042"
#define SIZE BUFSIZ * 10

void CheckData(char * p, int num);

int main() {
	struct addrinfo * result, dint;
	int rc, readc;
	int sock;
	char buf[SIZE];
	char sendMsg[BUFSIZ];
	memset(&dint, 0, sizeof(dint));
	memset(buf, 0, SIZE);
	printf("%d\n", SIZE);
	dint.ai_socktype = SOCK_STREAM;
	dint.ai_family = AF_INET;
	rc = getaddrinfo(HOST, PORT, &dint, &result);

	if (rc == -1) {
		oops("getaddrinfo");
	}

	sock = socket(PF_INET, result->ai_socktype, result->ai_protocol);

	if (sock == -1) {
		oops("create socket");
	}

	if (connect(sock, result->ai_addr, result->ai_addrlen) == -1) {
		oops("connect");
	}

	free(result);

	if ((readc = read(sock, buf, SIZE)) > 0) {
		printf("read %s\n", buf);
		char * str = strchr(buf, ':') + 1;
		str[strlen(str) - 1] = '\0';
		sprintf(sendMsg, "IAM:%s:77875894q@gmail.com\n", str);
		write(sock, sendMsg, strlen(sendMsg));
		readc = read(sock, buf, SIZE);
		printf("%s\n", buf);
		while ((readc = read(sock, buf, SIZE)) > 0) {
			// 获取

			CheckData(buf, readc);
			// printf("%d bytes data receiving\n", readc);
			// printf("%s", buf);
		}
	}
	return 0;
}

void CheckData(char * p, int num) {

	int i;
	int xor;
	int data32;

	int last = (num - 12) % 4;

	int lastElem = num-last;

	int bu = 0xAB;


	int sq = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
	int checksum = (p[4] << 24) | (p[5] << 16) | (p[6] << 8) | p[7];


	xor = sq;

	for(i = 12; i < lastElem; i+=4) {
		data32 = (p[i] << 24) | (p[i + 1] << 16) | (p[i + 2] << 8) | p[i + 3];
		xor ^= data32;
	}

	switch (last) {
		case 1:
			data32 = (p[lastElem] << 24) | (bu << 16) | (bu << 8) | bu;
			xor ^= data32;
			break;

		case 2: 
			data32 = (p[lastElem] << 24) | (p[lastElem + 1] << 16) | (bu << 8) | bu;
			xor ^= data32;
			break;


		case 3: 
			data32 = (p[lastElem] << 24) | (p[lastElem + 1] << 16) | (p[lastElem + 2] << 8) | bu;
			xor ^= data32;
			break;
	}

	printf("%d\n", xor == checksum);


	

}