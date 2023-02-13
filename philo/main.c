/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:31:30 by stde-la-          #+#    #+#             */
/*   Updated: 2023/02/11 22:35:03 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_philosopher *get_philosopher_to_left(t_philosopher *curr)
{
	if (curr->id != 1)
		return (curr - 1);
	return (curr + curr->philosophers_amount - 1);
}

t_philosopher *get_philosopher_to_right(t_philosopher *curr)
{
	if (curr->id != curr->philosophers_amount)
		return (curr + 1);
	return (curr - curr->philosophers_amount + 1);
}

void	eat(t_philosopher *left, t_philosopher *curr)
{
	struct timeval	tv;

	curr->is_thinking = 0;

	// pthread_mutex_lock(&(curr->starving_mutex));
	gettimeofday(&tv, NULL);
	curr->time = tv.tv_usec;
	// pthread_mutex_unlock(&(curr->starving_mutex));

	printf("%d is eating\n", curr->id);
	usleep(curr->time_to_eat);

	pthread_mutex_lock(&(left->fork_mutex));
	pthread_mutex_lock(&(curr->fork_mutex));
	left->fork = 1;
	curr->fork = 1;
	pthread_mutex_unlock(&(left->fork_mutex));
	pthread_mutex_unlock(&(curr->fork_mutex));
}

void	*starving(void *args)
{
	t_philosopher	*curr;
	struct timeval	tv;

	curr = (t_philosopher *)args;
	while (1)
	{
		gettimeofday(&tv, NULL);
		if (tv.tv_usec - curr->time >= curr->time_to_die)
		{
			curr->is_alive = 0;
			printf("%d died\n", curr->id);
			break ;
		}
		usleep(1000);
	}
	return (curr);
}

void	think(t_philosopher *curr)
{
	if (!curr->is_thinking)
		printf("%d is thinking\n", curr->id);
	curr->is_thinking = 1;
}

void	sleep_time(t_philosopher *curr)
{
	printf("%d is sleeping\n", curr->id);
	usleep(curr->time_to_eat);
}

int	take_forks(t_philosopher *left, t_philosopher *curr)
{
	pthread_mutex_lock(&(left->fork_mutex));
	pthread_mutex_lock(&(curr->fork_mutex));
	if (left->fork && curr->fork)
	{
		printf("%d has taken a fork\n", curr->id);
		printf("%d has taken a fork\n", curr->id);
		curr->fork = 0;
		left->fork = 0;
		pthread_mutex_unlock(&(left->fork_mutex));
		pthread_mutex_unlock(&(curr->fork_mutex)); 
		return (2);
	}
	pthread_mutex_unlock(&(left->fork_mutex));
	pthread_mutex_unlock(&(curr->fork_mutex)); 
	return (0);
}

void	*routine(void *args)
{
	int				eating_count;
	t_philosopher	*left;
	t_philosopher	*curr;

	curr = (t_philosopher *)args;
	left = get_philosopher_to_left(curr);
	pthread_create(&(curr->starving_thread), NULL, starving, curr);
	pthread_mutex_init(&(curr->starving_mutex), NULL);
	eating_count = 0;
	while (curr->is_alive
		&& (curr->required_eating_amount == -1 || eating_count <= curr->required_eating_amount))
	{
		if (take_forks(left, curr) == 2)
		{
			eat(left, curr);
			sleep_time(curr);
			eating_count++;
		}
		think(curr);
	}
	return (NULL);
}

void	init_philosopher(t_philosopher *curr, int argc, char **argv, int i)
{
	curr->philosophers_amount = ft_atoi(argv[1]);
	curr->time_to_die = ft_atoi(argv[2]);
	curr->time_to_eat = ft_atoi(argv[3]);
	curr->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		curr->required_eating_amount = ft_atoi(argv[5]);
	else
		curr->required_eating_amount = -1;
	curr->id = i + 1;
	curr->fork = 1;
	curr->is_thinking = 0;
	curr->time = 
	pthread_mutex_init(&(curr->fork_mutex), NULL);
	curr->is_alive = 1;
}

void	init_philosophers(t_data *data, int argc, char **argv)
{
	int	i;

	data->philosophers = malloc(sizeof(t_philosopher) * data->philosophers_amount);
	if (!data->philosophers)
		exit(1);
	i = 0;
	while (i < data->philosophers_amount)
	{
		data->philosophers[i].time = data->time;
		init_philosopher(&(data->philosophers[i]), argc, argv, i);
		i++;
	}
	i = 0;
	while (i < data->philosophers_amount)
	{
		pthread_create(&(data->philosophers[i].thread), NULL, routine, &(data->philosophers[i]));
		i++;
	}
	i = 0;
	while (i < data->philosophers_amount)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
}

// 5 800 200 200
int main(int argc, char **argv)
{
	struct timeval	tv;
    struct timezone	tz;
	t_data			data;

	if (argc != 5 && argc != 6)
		return (printf("You must pass the required arguments.\n"), 1);
	data.philosophers_amount = ft_atoi(argv[1]);
    gettimeofday(&tv, &tz);
	data.time = tv.tv_usec;
	init_philosophers(&data, argc, argv);
	free_philosophers(data.philosophers, data.philosophers_amount);
	return (0);
}