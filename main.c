#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
   // load config files, if any

   // run command loop
   lsh_loop();

   // perform any shutdown / cleanup

   return EXIT_SUCCESS;
}
