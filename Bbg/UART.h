#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

struct termios *uart_config;
extern int file_descriptor;
extern char *uart_port;

void uart4_config(struct termios *configuration, int descriptor);
void uart4_init(void);

