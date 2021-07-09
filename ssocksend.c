#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h> 	//inet_addr
#include<string.h>	//strlen
#include<unistd.h>	//write

int main(int argc , char *argv[])
{
	int socket_desc , new_socket , c;
	struct sockaddr_in server , client;
	char *message;

	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket\n");
	}

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );

	//Bind
	if(bind(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("Bind failed\n");
		return 1;
	}
	puts("Bind done\n");

	//Listen
	listen(socket_desc , 3);

	//Accept and incoming connection
	puts("Waiting for incoming connection...\n");

	while(new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))
	{
		puts("Connection accepted\n");

		//Reply to the client
		message = "Hello, I have accepted your connection\n";
		write(new_socket , message , strlen(message));
	}

	if (new_socket<0)
	{
		perror("Accept failed\n");
		return 1;
	}

	return 0;
}
