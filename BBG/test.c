#include <stdlib.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "UART.h"

void test_uart_config(void **state)
{
  assert_int_equal(0, uart4_init());
}

int main(int argc, char **argv)
{
  const UnitTest tests []=
  {
    unit_test(test_uart_config),
  };
  return run_tests(tests);
}
