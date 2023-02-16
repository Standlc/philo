#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
// -lpthread -lrt

void	start_processes(int size)
{
	if (!size)
		return ;
	if (fork() == 0)
	{
		printf("fork\n");
		start_processes(size - 1);
	}
	// else
	// 	printf("starting\n");
}

int main()
{
	start_processes(3);
}