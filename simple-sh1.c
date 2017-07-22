/*
 * sh1.c: sample version 1 of a UNIX command shell/interpreter.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <sys/types.h>
#include <unistd.h>

/* Perform string split on delimiter */
void strsplit(char *str, char *retVal[], char *delim)
{
    char *cmd = strdup(strtok(str, delim));
    char *dest = strtok(NULL, delim);

    retVal[0] = cmd;
    retVal[1] = dest;
    //printf("done\n");
}
int main()
{
    char line[256];
    char prompt[] = "SimpleShell: Enter command or exit % ";
    pid_t pid;

    /* spit out the prompt */
    printf("%s", prompt );

    /* Try getting input. If error or EOF, exit */
    while( fgets(line, sizeof line, stdin) != NULL )
    {
	/* fgets leaves '\n' in input buffer. ditch it */
	line[strlen(line)-1] = '\0';

    if(strcmp(line,"exit") == 0){
        break;
    } else {
      pid = fork();
      if(pid == 0)
      {
        char **res = (char **)malloc(sizeof(char *) * 2);
        strsplit(line, res, " ");
        execlp(res[0], res[0], res[1], NULL);
        printf("execlp command failed\n");
        exit(127);
      }
      else if(pid > 0)
      {
        wait(0);
      }
      else
      {
        printf("fork failed\n");
      }       
    }

	printf("%s", prompt );
    }

    return 0;
}
