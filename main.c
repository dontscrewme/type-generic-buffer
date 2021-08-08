#include <stdio.h>
#include <string.h>
#include "buffer.h"


int main(void) {
  
  buffer_t* ipBuffer = newBuffer(100, 16);

  char input_ip[16] = {0};
  
  while (1)
  {
    printf("input ip: ");
    scanf("%s", input_ip);
    
    if (!strcmp(input_ip, "quit"))
    {
        break;
    }

    if (!item_in_buffer(ipBuffer, input_ip))
    {
        put(ipBuffer, input_ip);
        printf("%s is put in buffer\n", input_ip);
    }
    else
    {
        printf("%s is aleady in buffer!\n", input_ip);
    }
  }

  print_buffer(ipBuffer);
  deleteBuffer(ipBuffer);

  return 0;
}
