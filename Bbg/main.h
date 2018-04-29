#define SOCKET_TO_LOG "/sockettolog"

char data[500];
struct	mq_attr	attr;
mqd_t socket_to_log; 

typedef enum task
{
    MAIN_TASK,
    SOCKET_TASK,
    LOGGER_TASK
}Task;

typedef enum type
{
    INIT,
    HEARTBEAT,
    DATA,
    ERROR
}Type;

typedef enum data
{
    TEMPERATURE, //0
    HUMIDITY,
    PEDOMETER
}Data;

typedef struct
{
  uint32_t type;
  uint32_t timestamp;
  uint8_t source;
  uint32_t data;
  uint32_t sensor;
  size_t length;
}message_t;

message_t uart_receive;
