/* Program: server.c
*	A simple TCP server using sockets.
*	Server is executed before Client.
*	Port number is to be passed as an argument.
 
*
*	To test: Open a terminal window.
*	At the prompt ($ is my prompt symbol) you may
*	type the following as a test:
*
* $ ./server 54554
*	Run client by providing host and port
*
*
*/
#include <arpa/inet.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#include <pthread.h>
#include <sys/queue.h>
#include <stdio.h>


void error(const char *msg);

void* charA( void *messageQueue )
{
	char *data;
	int i=0;
	if(messageQueue)
	{
		data = (char*)messageQueue;
		while(data[i]!='\0'){
			if(data[i] =='a'){
				data[i] = 'A';			
			}	
			i++;
		}
		//printf("Data: %s\n",data);
	}
	return 0;
}

void* charE( void *messageQueue )
{
	char *data;
	int i=0;
	if(messageQueue)
	{
		data = (char*)messageQueue;
		while(data[i]!='\0'){
			if(data[i] =='e'){
				data[i] = 'E';			
			}	
			i++;
		}
		//printf("Data: %s\n",data);
	}
	return 0;
}

void* charI( void *messageQueue )
{
	char *data;
	int i=0;
	if(messageQueue)
	{
		data = (char*)messageQueue;
		while(data[i]!='\0'){
			if(data[i] =='i'){
				data[i] = 'I';			
			}	
			i++;
		}
		//printf("Data: %s\n",data);
	}
	return 0;
}

void* charO( void *messageQueue )
{
	char *data;
	int i=0;
	if(messageQueue)
	{
		data = (char*)messageQueue;
		while(data[i]!='\0'){
			if(data[i] =='O'){
				data[i] = 'o';			
			}	
			i++;
		}
		//printf("Data: %s\n",data);
	}
	return 0;
}

void* charU( void *messageQueue )
{
	char *data;
	int i=0;
	if(messageQueue)
	{
		data = (char*)messageQueue;
		while(data[i]!='\0'){
			if(data[i] =='u'){
				data[i] = 'U';			
			}	
			i++;
		}
		//printf("Data: %s\n",data);
	}
	return 0;
}

void* digitThread( void *messageQueue )
{
	char *data;
	int i=0;
	int sum = 0;
	if(messageQueue)
	{
		data = (char*)messageQueue;
		while(data[i]!='\0'){
			if(data[i] =='1'){
				sum = sum+1;		
			}
			else if(data[i] == '2'){
				sum = sum+2;			
			}
			else if(data[i] == '3'){
				sum = sum+3;			
			}
			else if(data[i] == '4'){
				sum = sum+4;			
			}
			else if(data[i] == '5'){
				sum = sum+5;			
			}
			else if(data[i] == '6'){
				sum = sum+6;			
			}
			else if(data[i] == '7'){
				sum = sum+7;			
			}
			else if(data[i] == '8'){
				sum = sum+8;			
			}
			else if(data[i] == '9'){
				sum = sum+9;			
			}
			i++;
		}
		printf("Sum= %d\n",sum);
	}
	return 0;
}


int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	struct sockaddr_in serv_addr, cli_addr; 
	socklen_t clilen;
	char buffer[256];
	int n;

	// if not enough variables sent
	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n"); 
		exit(1);
	}
	fprintf(stdout, "Run client by providing host and port\n");

	//creating a socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");

	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	//getting port number from command line
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY; serv_addr.sin_port = htons(portno);

	//making a connection
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding"); listen(sockfd,5);
	clilen = sizeof(cli_addr); newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	
	if (newsockfd < 0)
		error("ERROR on accept");
	bzero(buffer,256);
	
	//reading from socket
	n = read(newsockfd,buffer,255);
	if (n < 0)
		error("ERROR reading from socket");

	printf("Here is the message:\n %s",buffer);
	
	int j=0, size=0;
	static char messageQueue[100];
	while(buffer[j]!='\0'){

		messageQueue[j]=buffer[j];
		j++;
	}
	messageQueue[j] ='\0';

	pthread_t threadA;
	if( pthread_create( &threadA, NULL, charA, (void*)messageQueue)  != 0)
	{
		return 0;
	}

	pthread_join( threadA, NULL);

	pthread_t threadE;
	if( pthread_create( &threadE, NULL, charE, (void*)messageQueue)  != 0)
	{
		return 0;
	}

	pthread_join( threadE, NULL);


	pthread_t threadI;
	if( pthread_create( &threadI, NULL, charI, (void*)messageQueue)  != 0)
	{
		return 0;
	}

	pthread_join( threadI, NULL);

	pthread_t threadO;
	if( pthread_create( &threadO, NULL, charO, (void*)messageQueue)  != 0)
	{
		return 0;
	}

	pthread_join( threadO, NULL);

	pthread_t threadU;
	if( pthread_create( &threadU, NULL, charU, (void*)messageQueue)  != 0)
	{
		return 0;
	}

	pthread_join( threadU, NULL);

	pthread_t threadD;
	if( pthread_create( &threadD, NULL, digitThread, (void*)messageQueue)  != 0)
	{
		return 0;
	}
	pthread_join( threadD, NULL);


	//writing to socket
	size = sizeof(messageQueue) / sizeof(messageQueue[0]);
	n = write(newsockfd,messageQueue,size); 
	if (n < 0)
		error("ERROR writing to socket");

	close(newsockfd);
	close(sockfd);

	return 0;
	

}

void error(const char *msg)
{
	perror(msg); exit(1);
}

