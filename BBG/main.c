#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/stat.h>  
#include <sys/types.h>  
#include <time.h>
#include <signal.h>
#include <assert.h>
#include <mqueue.h>  

#include "main.h"
#include "UART.h"
#include "socket_server.h"

#define BUFFER_SIZE   (64)
#define NUM_THREADS   2
#define INTERVAL      100

pthread_t socket_thread, logger_thread, external_thread;

clock_t t; //Caculate the timestamp when entering/exiting the threads

static void * socket_task(void *arg);
static void * logger_task(void *arg);
static void * external_task(void *arg);

void signal_handler(int arg)
{
  if(arg==SIGINT)
  {
    printf("receive INT signal\n");
    pthread_cancel(logger_thread);
    pthread_cancel(socket_thread);
    pthread_cancel(external_thread);
  }else if(arg==SIGUSR2)
  {
    printf("receive USR2 signal\n");
    pthread_cancel(socket_thread);
    pthread_cancel(logger_thread);
    pthread_cancel(external_thread);
  }else if(arg==SIGUSR1)
  {
    printf("receive USR1 signal\n");
    pthread_cancel(socket_thread);
    pthread_cancel(logger_thread);
    pthread_cancel(external_thread);
  }
}

void send_msg_from_socket(Type type, uint32_t data, Data sensor, uint8_t source)
{
  message_t msg; 
  //gettimeofday(&msg.timestamp, NULL);
  msg.timestamp = 999;
  msg.type = type;
  msg.source = source;
  msg.data = data; 
  msg.sensor = sensor;
  msg.length = 0;
  if(mq_send(socket_to_log, (char*)&msg, sizeof(msg), 0) == -1)
  {
    printf("\nUnable to send message from socket task\n");
    return 1;
  }
}

static void * external_task(void * arg)
{
  printf("In external Task\n");
  socket_start();
}

static void * socket_task (void *arg)
{
  printf("In socket Task\n");
  uart4_init();
  printf("Init UART\n");

  while(1)
  {
    memset(&uart_receive,'\0',sizeof(uart_receive));
    int receive;
    write(file_descriptor, &uart_transfer, sizeof(uart_transfer));
	receive = read(file_descriptor, &uart_receive, sizeof(uart_receive));
    if(receive > 0)
    {
      if(uart_receive.type == 2)
      {
        if(uart_receive.sensor == 2)
        {   
          printf("[DATA] Pedometer: %d\n",uart_receive.data);
        }else if(uart_receive.sensor == 1)
        {   
          printf("[DATA] Humidity: %d\n",uart_receive.data);
        }else if(uart_receive.sensor == 0)
        {   
          printf("[DATA] Temperature: %d\n",uart_receive.data);
        }
      }else if(uart_receive.type ==1)
      {
        if(uart_receive.source == 1)
        {
          printf("[HEARTBEAT] pedometer alive\n");
        }else if(uart_receive.source == 2)
        {
          printf("[HEARTBEAT] weather alive\n");
        }
      }else if(uart_receive.type == 3)
      {
        if(uart_receive.sensor == 2)
        {   
          printf("[FATAL ERROR] Pedometer\n");
        }else if(uart_receive.sensor == 1)
        {   
          printf("[FATAL ERROR] Humidity\n");
        }else if(uart_receive.sensor == 0)
        {   
          printf("[FATAL ERROR] Temperature\n");
        }
      }
      send_msg_from_socket(uart_receive.type, uart_receive.data, uart_receive.sensor, uart_receive.source);

    }else{
      printf("No Data from UART\n");
    }
    fflush(stdout);
   }
  return NULL;  
}

static void * logger_task (void *arg)
{
  printf("In Logger Task\n");

  FILE * FH_p;
  FH_p = fopen("output.txt", "a+");

  t=clock();
  fprintf(FH_p, "[Logger] The timestamp is: %d\n", (int)t);

  /* Receive data from socket task */
  message_t msg; 
  while(1){
    if(mq_receive(socket_to_log, (char*)&msg, sizeof(msg), 0) == -1)
    {
      printf("\nFailed to receive from logger task\n");
    }else
    { 
      /* Reading DATA */
      if(msg.type == 2)
      {
        if(msg.sensor == 2)
        {
          sprintf(data, "Source : socket task | PEDOMEER : %d \n", msg.data);
          fprintf(FH_p, "%s\n", data);
        }else if(msg.sensor == 1)
        {
          sprintf(data, "Source : socket task | HUMIDITY : %d \n", msg.data);
          fprintf(FH_p, "%s\n", data);
        }else if(msg.sensor == 0)
        {
          sprintf(data, "Source : socket task | TEMPERATURE : %d \n", msg.data);
          fprintf(FH_p, "%s\n", data);
        }
      /* Reading HeartBeat */
      }else if(msg.type == 1)
      {
        if(msg.source == 1)
        {
          sprintf(data, "Source : socket task | HEARTBEAT from pedometer");
          fprintf(FH_p, "%s\n", data);
        }else if(msg.source == 2)
        {
          sprintf(data, "Souce: socket task | HEARTBEAT from weather");
          fprintf(FH_p, "%s\n", data);
        }
      /* Receiving Error from Tiva*/
      }else if(msg.type == 3)
      {
        if(msg.sensor == 2)
        {
          sprintf(data, "Source : socket task | PEDOMEER ERROR");
          fprintf(FH_p, "%s\n", data);
        }else if(msg.sensor == 1)
        {
          sprintf(data, "Source : socket task | HUMIDITY ERROR");
          fprintf(FH_p, "%s\n", data);
        }else if(msg.sensor == 0)
        {
          sprintf(data, "Source : socket task | TEMPERATURE ERROR");
          fprintf(FH_p, "%s\n", data);
        }
      }
    }
  fflush(FH_p);
  }
  return NULL;
}

void openMsgQueue(void)
{
  socket_to_log = mq_open(SOCKET_TO_LOG, O_CREAT|O_RDWR, 0644, &attr);
  if(socket_to_log == -1)
  {
    printf("open failed\n");
  }
}

void closeMsgQueue(void)
{
  mq_close(socket_to_log);
  mq_unlink(SOCKET_TO_LOG);
}

void main()
{   

    
  /* initialize the queue attributes */  
  attr.mq_flags = 0;  
  attr.mq_maxmsg = 10;  
  attr.mq_msgsize = sizeof(message_t);  

  closeMsgQueue();
  openMsgQueue();

  signal(SIGSEGV, signal_handler);
  signal(SIGINT, signal_handler);
  signal(SIGUSR1, signal_handler);
  signal(SIGUSR2, signal_handler);
  
  sigset_t alarm_sig;
  sigemptyset(&alarm_sig);
  for (int i = SIGRTMIN; i <= SIGRTMAX; i++)
  sigaddset(&alarm_sig, i);
  sigprocmask(SIG_BLOCK, &alarm_sig, NULL);

  if(pthread_create(&socket_thread, NULL, socket_task, NULL))
  {
    printf("ERROR: Could not creat socket thread!\n");
    exit(1);
  }
  
  if(pthread_create(&logger_thread, NULL, logger_task, NULL))
  {
    printf("ERROR: Could not creat logger thread!\n");
    exit(1);
  }

  if(pthread_create(&external_thread, NULL, external_task, NULL))
  {
    printf("ERROR: Could not creat external thread!\n");
    exit(1);
  }

  sleep(3);

  if(pthread_join(socket_thread, NULL))
  {
    printf("ERRORL Could not join thread!\n"); 
    exit(1);
  }

  if(pthread_join(logger_thread, NULL))
  {
    printf("ERRORL Could not join thread!\n"); 
    exit(1);
  }

  if(pthread_join(external_thread, NULL))
  {
    printf("ERRORL Could not join thread!\n"); 
    exit(1);
  }
  /* Threads closed */

  return 0;
}

