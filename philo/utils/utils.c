/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:26:48 by stde-la-          #+#    #+#             */
/*   Updated: 2023/02/15 15:26:49 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	else if (*str == '-' || n == 0)
		*status = NEGATIVE_NB;
	return (n);
}

int	has_eaten_enough(t_philosopher *curr)
{
	int	result;

	pthread_mutex_lock(&(curr->eating_count_mutex));
	if (curr->rules.required_eat_count == -1)
		result = 0;
	else
		result = curr->eating_count == curr->rules.required_eat_count;
	pthread_mutex_unlock(&(curr->eating_count_mutex));
	return (result);
}

void	wait_time(int time)
{
	int	start;

	start = now();
	while (now() - start < time)
		usleep(50);
}

int	now(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

t_philosopher	*get_philosopher_to_left(t_philosopher *curr)
{
	return (curr + (curr->id == 1) * curr->rules.amount - 1);
}
