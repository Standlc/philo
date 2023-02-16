/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:31:30 by stde-la-          #+#    #+#             */
/*   Updated: 2023/02/14 12:55:16 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophing(t_philosopher	*curr)
{
	// sem_wait(curr->rules->forks);
	// int value;
	// sem_getvalue(curr->rules->forks, &value);
	// printf("%d\n", value);
	printf("id: %d pid: %d \n", curr->id, curr->pid);
	// printf("%d\n", value);
	// sem_post(curr->rules->forks);

	// if (curr->id % 2 == 0)
	// 	usleep(curr->rules->time_to_eat / 2);
	while (has_eaten_enough(curr) && !curr->rules->some_dead)
	{
		// take_forks(curr);
		// eat(curr);
		// printf("%d\n", curr->rules->some_dead);
		put_philosopher_to_bed(curr);
		think(curr);
	}
	return (NULL);
}

void	start_processes(t_philosopher *philosophers, int size, int i)
{
	if (i == size)
		return ;
	if (fork() == 0)
		start_processes(philosophers, size, i + 1);
	else
	{
		philosophers[i].pid = getpid();
		philosophing(philosophers + i);
	}
}

void	kill_processes(t_philosopher *philosophers, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		kill(philosophers[i].pid, SIGSEGV);
		i++;
	}
}

void	close_program(t_data *data)
{
	// kill_processes(data->philos, data->rules.amount);
	// sem_close(data->rules.forks);
	// free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (printf("You must pass the required arguments.\n"), 1);
	if (init_data(&data, argc, argv))
		return (1);
	if (create_philos(&data))
		return (printf("Malloc error\n"), 1);
	start_processes(data.philos, data.rules.amount, 0);
	check_for_deads(data.philos, &(data.rules));
	close_program(&data);
	return (0);
}
