/* Ring.c 
 * Unix CS5375 Weekly Activity
 * Anoop S Somashekar
 */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )
{
int i, fd[2];
int childpid; 
int nprocs = atoi( argv[1]);
dup2 (fd[0], 0);
dup2 (fd[1], 1);
close ( fd[0] );
close ( fd[1] );

for ( i = 1; i < nprocs; i++ )
{
	pipe( fd );
	childpid = fork();

	if ( childpid > 0 )
		dup2(fd[1], 1);
	else
    { 
		dup2(fd[0], 0);
        char str[12];
        read(fd[0], str, sizeof(str));
        fprintf(stderr, "Message \" %s \" received at PID %d: from PID %d\n", str, getpid(), getppid());
    }

    close ( fd[0] );
    if (childpid) break;
	close ( fd[1] );
}
char str[12] = "Hello World";
write(fd[1], str, sizeof(str));
fprintf( stderr, "Message \" %s \" sent from PID %d\n",str, getpid());
close(fd[1]);

/*
if (i == 1)
{
    sleep(5);
    char str[12];
    read(fd[0], str, sizeof(str));
    fprintf(stderr, "Message received at PID %d: %s from PID %d\n", getpid(),str, getppid());
    close(fd[0]);
}
*/

if (i == nprocs)
    fprintf(stderr, "Message \" %s \" received from %d\n", str, getpid());
return 0;
}
