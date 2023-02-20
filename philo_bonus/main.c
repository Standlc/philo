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

void	philosophing(t_philosopher	*curr)
{
	if (curr->id % 2 == 0)
		usleep(curr->rules->time_to_eat / 2);
	while (has_eaten_enough(curr) && !curr->rules->some_dead)
	{
		take_forks(curr);
		eat(curr);
		put_philosopher_to_bed(curr);
		think(curr);
	}
}

void	print_pid(t_philosopher *philosophers, int size)
{
	int i = 0;
	while (i < size)
	{
		printf("%d ", philosophers[i].pid);
		i++;
	}
	printf("\n");
}

void	start_processes(t_philosopher *philosophers, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		philosophers[i].pid = fork();
		if (philosophers[i].pid == 0)
		{
			philosophing(philosophers + i);
			return ;
		}
		i++;
	}
	print_pid(philosophers, size);
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
	sem_close(data->rules.forks);
	free(data->philos);
}

void	wait_philosophers(t_philosopher *philosophers, int size)
{
	int	i;
	int	status_ptr;

	i = 0;
	while (i < size)
	{
		waitpid(philosophers[i].pid, &status_ptr, 0);
		i++;
	}
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
	start_processes(data.philos, data.rules.amount);
	// check_for_deads(data.philos, &(data.rules));
	wait_philosophers(data.philos, data.rules.amount);
	close_program(&data);
	return (0);
}
