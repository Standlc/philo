/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:31:30 by stde-la-          #+#    #+#             */
/*   Updated: 2023/02/07 22:36:52 by stde-la-         ###   ########.fr       */
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

void	*test(void *args)
{
	// printf("%d\n", *(int *)args);
	printf("YES\n");
	return (NULL);
}

void	init_philosophers(t_data *data)
{
	int	i;

	data->philosophers = malloc(sizeof(t_philosopher) * data->philosophers_amount);
	if (!data->philosophers)
		exit(1);
	i = 0;
	while (i < data->philosophers_amount)
	{
		pthread_create(&(data->philosophers[i].thread), NULL, test, (void*)&(data->philosophers[i]));
		data->philosophers[i].id = i + 1;
		data->philosophers[i].fork = 1;
		i++;
	}
}

void	init_data(t_data *data, int argc, char **argv)
{
	data->philosophers_amount = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->required_eating_amount = ft_atoi(argv[5]);
	else
		data->required_eating_amount = -1;
	init_philosophers(data);
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (printf("You must pass the required arguments.\n"), 1);
	init_data(&data, argc, argv);
	free_philosophers(data.philosophers, data.philosophers_amount);
	return (0);
}