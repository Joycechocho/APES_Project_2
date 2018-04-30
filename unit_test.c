#include <stdlib.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "UART.h"
#include "socket_server.h"

void test_uart_config(void **state)
{
  int status = uart4_init();
  assert_int_equal(0, status);
}

void test_socket_config(void **state)
{
  int status = socket_start();
  assert_int_equal(0, status);
}

void test_openMsgQueue(void **state)
{
  int status = openMsgQueue();
  assert_int_equal(0, status);
}

void test_closeMsgQueue(void **state)
{
  int status = closeMsgQueue();
  assert_int_equal(0, status);
}

int main(int argc, char **argv)
{
  const UnitTest tests []=
  {
    unit_test(test_uart_config),
    unit_test(test_socket_config),
    unit_test(test_openMsgQueue),
    unit_test(test_closeMsgQueue),
  };
  return run_tests(tests);
}
