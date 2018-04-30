#include <stdlib.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "UART.h"
#include "socket_server.h"

void test_uart_config(void **state)
{
  assert_int_equal(0, uart4_init());
}

void test_socket_config(void **state)
{
  int status = socket_start();
  assert_int_equal(0, status);
}

int main(int argc, char **argv)
{
  const UnitTest tests []=
  {
    unit_test(test_uart_config),
    unit_test(test_socket_config),
  };
  return run_tests(tests);
}
