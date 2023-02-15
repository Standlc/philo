#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
// -lpthread -lrt

void	print()
{
	if (fork() == 0)
		printf("fork\n");
}

void	start_processes(int size)
{
	int i = 0;
	while (i < size)
	{
		print();
		i++;
	}
}

int main()
{
	start_processes(3);
}