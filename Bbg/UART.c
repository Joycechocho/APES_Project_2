#include "UART.h"

char *uart_port = "/dev/ttyO4";
int file_descriptor;

void uart4_config(struct termios *configuration, int descriptor)
{
  tcgetattr(descriptor, configuration);

  configuration->c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK | ISTRIP | IXON);
  configuration->c_oflag = 0;
  configuration->c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
  configuration->c_cc[VMIN] = 1;
  configuration->c_cc[VTIME] = 0;

  if(cfsetispeed(configuration, B57600) || cfsetospeed(configuration, B57600))
  {
    perror("Failed to set the baud rate\n");
  }

  if(tcsetattr(descriptor, TCSAFLUSH, configuration) < 0)
  {
    perror("Failed to set the attribute\n");
  }
}

void uart4_init()
{
  file_descriptor = open(uart_port, O_RDWR | O_NOCTTY | O_SYNC);
  if(file_descriptor == -1)
  {
    perror("Fail to open file descriptor\n");
  }

  uart_config = (struct termios*)malloc(sizeof(struct termios));
  uart4_config(uart_config, file_descriptor);
}
