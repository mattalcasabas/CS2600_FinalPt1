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

void lsh_loop()
{
   char *line;
   char **args;
   int status;

   do
   {
      printf("> ");
      line = lsh_read_line();
      args = lsh_split_line(line);
      status = lsh_execute(args);

      free(line);
      free(args);
   } while (status);
}
