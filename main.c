#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define LSH_RL_BUFSIZE 1024

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

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

char **lsh_split_line(char *line)
{
   int bufsize = LSH_TOK_BUFSIZE, position = 0;
   char **tokens = malloc(bufsize * sizeof(char *));
   char *token;

   if (!tokens)
   {
      fprintf(stderr, "lsh: allocation error\n");
      exit(EXIT_FAILURE);
   }

   token = strtok(line, LSH_TOK_DELIM);
   while (token != NULL)
   {
      tokens[position] = token;
      position++;

      if (position >= bufsize)
      {
         bufsize += LSH_TOK_BUFSIZE;
         tokens = realloc(tokens, bufsize * sizeof(char *));
         if (!tokens)
         {
            fprintf(stderr, "lsh: allocation error\n");
            exit(EXIT_FAILURE);
         }
      }

      token = strtok(NULL, LSH_TOK_DELIM);
   }

   tokens[position] = NULL;
   return tokens;
}

int lsh_launch(char **args)
{
   pid_t pid, wpid;
   int status;

   pid = fork();
   if (pid == 0)
   {
      // child process
      if (execvp(args[0], args) == -1)
      {
         perror("lsh");
      }
      exit(EXIT_FAILURE);
   }
   else if (pid < 0)
   {
      // error forking
      perror("lsh");
   }
   else
   {
      do
      {
         wpid = waitpid(pid, &status, WUNTRACED);
      } while (!WIFEXITED(status) && !WIFSIGNALED(status));
   }

   return 1;
}

int main(int argc, char **argv)
{
   // load config files, if any

   // run command loop
   lsh_loop();

   // perform any shutdown / cleanup

   return EXIT_SUCCESS;
}
