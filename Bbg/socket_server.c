#include <stdio.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
  
#include "socket_server.h"

void socket_start() 
{  
  int sock0;  
  struct sockaddr_in addr;  
  struct sockaddr_in client;  
  socklen_t len;  
  int sock_client;  
  
  /* create socket */  
  sock0 = socket(AF_INET, SOCK_STREAM, 0);  
  
  /* set up socket */  
  addr.sin_family = AF_INET;  
  addr.sin_port = htons(12345);  
  addr.sin_addr.s_addr = INADDR_ANY;  
  bind(sock0, (struct sockaddr*)&addr, sizeof(addr));  
  printf("\t[Info] binding...\n");  
  
  /* listening */  
  listen(sock0, 5);  
  printf("\t[Info] listening...\n");  
  
  /* waiting for the client */  
  printf("\t[Info] wait for connection...\n");  
  len = sizeof(client);  
  sock_client = accept(sock0, (struct sockaddr *)&client, &len);  
  if(sock_client < 0)
  {
    printf("Failed when accepting client");
    return 1;
  }
  char *paddr_str = inet_ntoa(client.sin_addr);  
  printf("\t[Info] Receive connection from %s...\n", paddr_str);  
  
  /* send something back */  
  printf("\t[Info] Say hello back...\n");  
  float temperature = 123.456789;
  char send_data[32];
  gcvt(temperature, 6, send_data);
  write(sock_client, send_data, sizeof(send_data));  
  
  /* close client connection */  
  printf("\t[Info] Close client connection...\n");  
  close(sock_client);  
  
  /* close listening */  
  printf("\t[Info] Close self connection...\n");  
  close(sock0);  
  return NULL;  
} 
