#include "server.h"


int
main(int argc, char **argv){

	int socket_desc, new_socket, *new_sock, portno, clilen;
	struct sockaddr_in server, client;
	int n;
	FILE *fp;
	time_t current_time;
	char* c_time_string;
	pthread_t thread_id;

	fp = fopen("log.txt", "w+");

	if(fp == NULL){
		error("ERROR opening file");
	}

	fflush(fp);
	fprintf(fp, "creating log\n", NULL);
	fclose(fp);

	if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

 	if (socket_desc < 0) {
    	error("ERROR opening socket");
    }


	bzero((char *) &server, sizeof(server));
    portno = atoi(argv[1]);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(portno);

    if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0){
    	error("ERROR on binding");
    }

	listen(socket_desc,5);

	clilen = sizeof(client);

	while(new_socket = accept(socket_desc, (struct sockaddr *) &client, &clilen)){

	    if (new_socket < 0){
	    	error("ERROR on accept");
	    }

	    printf("client connected\n");



	   	new_sock = malloc(sizeof(int));
    	*new_sock = new_socket;

    	pthread_create(&thread_id, NULL, handler, (void*)new_sock);

    	close(new_sock);

    
	}
}


void*
handler(void* sockfd){

	char buffer[256];
	int n;
	FILE *fp;
	time_t current_time;
	char* c_time_string;

	int sock = *(int*)sockfd;
	printf("in handler\n");

	bzero(buffer, 256);

	while( (n = read(sock, buffer, 255)) > 0){
		printf("client says: %s\n", buffer);

		fp = fopen("log.txt", "a");
		fprintf(fp, "client said %s\n", buffer);
		fclose(fp);
	}

	



}