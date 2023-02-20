# include <stdio.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>

int main(int argc, char **argv)
{
	int i = 1;
	while (i < argc)
	{
		kill(atoi(argv[i]), SIGSEGV);
		i++;
	}
}