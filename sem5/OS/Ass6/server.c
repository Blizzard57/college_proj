/*
Server which sets up at 127.0.0.1:8080 and handles socket requests to transfer files over TCP.
Functionality :
    Finds and copies files from server to client.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024

int get_filesize(char *filename){
    FILE *fp = fopen(filename,"r");
    fseek(fp,0L,SEEK_END);
    int size = ftell(fp);
    fseek(fp,0,SEEK_SET);
    fclose(fp);
    return size;
}

void get_filename(int sockfd){
    int n;
    char *buffer = (char *)calloc(SIZE,sizeof(char));
    char *filename = (char *)calloc(SIZE,sizeof(char));

    n = recv(sockfd, buffer, SIZE, 0);
    strcpy(filename,buffer);
    bzero(buffer, SIZE);
    
    printf("[+]Filename %s received successfully\n",filename);

    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL){
        perror("[-]Error in reading file.");
        exit(1);
    }
    fclose(fp);

    printf("[+]Sending file %s\n",filename);
    char data[SIZE] = {0};

    int filesize = get_filesize(filename);
    char* send_size = (char *)calloc(sizeof(char),SIZE);
    sprintf(send_size,"%d",filesize);

    if (send(sockfd, send_size, SIZE, 0) == -1){
        printf("[-]Could not send filesize.");
        exit(1);
    }
    bzero(send_size,SIZE);
    free(send_size);

    fp = fopen(filename, "r");
    while (fgets(data, SIZE, fp) != NULL){
        if (send(sockfd, data, strlen(data), 0) == -1){
            perror("[-]Error in sending file.");
            exit(1);
        }
        //printf("%s",data);
        bzero(data, SIZE);
    }

    return;
}

int main(){
    // Parameters for server to operate on, thus server is at : 127.0.0.1:8080
    char *ip = "127.0.0.1";
    int port = 8080;
    int e;
    int opt = 1;

    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[SIZE];

    // Creating a socket
    // For connection between client <-> server
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created successfully.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    e = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (e < 0){
        perror("[-]Error in bind");
        exit(1);
    }
    printf("[+]Binding successfull.\n");
    
    if (listen(sockfd, 10) == 0)
        printf("[+]Listening....\n");
    
    else{
        perror("[-]Error in listening.");
        exit(1);
    }
    
    addr_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr *)&new_addr, &addr_size);
    
    while(1){
        //recv(new_sock, buffer, SIZE,0);
        get_filename(new_sock);
        printf("[+]Data sent successfully.\n");
    }
    return 0;
}