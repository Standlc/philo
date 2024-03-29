/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:26:48 by stde-la-          #+#    #+#             */
/*   Updated: 2023/08/13 12:30:28 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	destroy_mutexes(t_data *data, int launched_threads)
{
	int	i;

	pthread_mutex_destroy(&(data->is_end_mutex));
	pthread_mutex_destroy(&(data->start_mutex));
	pthread_mutex_destroy(&(data->print_mutex));
	pthread_mutex_destroy(&(data->philos_finished_eating_mutex));
	if (launched_threads == 0)
		launched_threads = data->rules.amount;
	i = 0;
	while (i < launched_threads)
	{
		pthread_mutex_destroy(&(data->philos[i].fork_mutex));
		pthread_mutex_destroy(&(data->philos[i].last_meal_mutex));
		pthread_mutex_destroy(&(data->philos[i].eating_count_mutex));
		i++;
	}
}

int	ft_atoi(char *str, int *status)
{
	long	n;

	if (*status)
		return (0);
	n = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	while (n <= INT_MAX && *str >= '0' && *str <= '9')
	{
		n = n * 10 + *str - '0';
		str++;
	}
	if (n > INT_MAX)
		*status = INT_OVERFLOW;
	else if (*str != '\0' && *str != '-')
		*status = CONTAINS_ALPHA;
	else if (*str == '-')
		*status = NEGATIVE_NB;
	return (n);
}

void	wait_time(t_philosopher *philo, double mseconds)
{
	int	start;

	start = now();
	while (now() - start < mseconds && !is_end_of_simulation(philo))
	{
		usleep(500);
	}
}

int	now(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

t_philosopher	*get_philosopher_to_left(t_philosopher *curr)
{
	return (curr + (curr->id == 1) * curr->rules->amount - 1);
}
