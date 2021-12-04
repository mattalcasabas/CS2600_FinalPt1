#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define LSH_RL_BUFSIZE 1024

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

char *lsh_read_line(void)
{
   int bufsize = LSH_RL_BUFSIZE;
   int position = 0;
   char *buffer = malloc(sizeof(char) * bufsize);
   int c;

   if (!buffer)
   {
      fprintf(stderr, "lsh: allocation error\n");
      exit(EXIT_FAILURE);
   }

   while (1)
   {
      // read character
      c = getchar();

      // if we hit EOF, replace it with null character and return
      if (c == EOF || c == '\n')
      {
         buffer[position] = '\0';
         return buffer;
      }
      else
      {
         buffer[position] = c;
      }
      position++;

      // if we exceed the buffer, reallocate
      if (position >= bufsize)
      {
         bufsize += LSH_RL_BUFSIZE;
         buffer = realloc(buffer, bufsize);
         if (!buffer)
         {
            fprintf(stderr, "lsh: allocation error\n");
            exit(EXIT_FAILURE);
         }
      }
   }
}
