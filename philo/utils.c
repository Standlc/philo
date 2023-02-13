#include "philo.h"

int	ft_atoi(char *str)
{
	int	n;
	int	sign;

	n = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + *str - '0';
		str++;
	}
	return (n * sign);
}

void	free_philosophers(t_philosopher *philosophers, int size)
{
	(void)size;
	free(philosophers);
}

int	now(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

t_philosopher	*get_philosopher_to_left(t_philosopher *curr)
{
	if (curr->id != 1)
		return (curr - 1);
	return (curr + curr->philosophers_amount - 1);
}

t_philosopher	*get_philosopher_to_right(t_philosopher *curr)
{
	if (curr->id != curr->philosophers_amount)
		return (curr + 1);
	return (curr - curr->philosophers_amount + 1);
}
