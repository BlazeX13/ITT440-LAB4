#include<stdlib.h>
#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>

int main()
{
	int sockd, sockClient, c;
	struct sockaddr_in server, client;
	int port = 8888;
	char msg[2000];

	sockd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockd < 0)
	{
		printf("Socket Connection error\n");
	}
	else
		printf("Socket Connection connected\n");

	server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr("192.168.56.114");
        server.sin_port = htons(port);

        if( bind(sockd, (struct sockaddr *)&server, sizeof(server)) <0)
        {
                printf("Binding error\n");
        }
        else
        printf("Binding successful %d \n", port);

        if (listen(sockd, 3) < 0)
        {
                printf("Port listening error %d \n", port);
        }
        else
                printf("Listening to port... \n");

        c = sizeof(struct sockaddr_in);

        while( (sockClient = accept(sockd, (struct sockaddr *)&client,(socklen_t*)&c )) )
        {
                printf("Incoming message... \n");
                printf("Client message: ");

		recv(sockClient, msg, 2000, 0);
		puts(msg);
	}

	close(sockd);
	return 0;
}
