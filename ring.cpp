//ring.cpp
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
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
		dup2(fd[0], 0);

	close ( fd[0] );
	close ( fd[1] );
	if (childpid) break;
}

fprintf( stderr, "This is process %d with ID %d and parent ID is %d\n",i, getpid(), getppid() );
return 0;
}