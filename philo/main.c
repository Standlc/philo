/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:31:30 by stde-la-          #+#    #+#             */
/*   Updated: 2023/08/13 13:07:03 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_solo_routine(t_philosopher *curr)
{
	pthread_mutex_lock(&(curr->fork_mutex));
	put_philosopher_status(curr, "has taken a fork");
	pthread_mutex_unlock(&(curr->fork_mutex));
	return (NULL);
}

void	wait_for_other_philos(t_philosopher *curr)
{
	pthread_mutex_lock(curr->start_mutex);
	pthread_mutex_unlock(curr->start_mutex);
}

void	*routine(void *args)
{
	t_philosopher	*left;
	t_philosopher	*curr;

	curr = (t_philosopher *)args;
	if (curr->rules->amount == 1)
		return (philo_solo_routine(curr));
	left = get_philosopher_to_left(curr);
	wait_for_other_philos(curr);
	if (curr->id % 2 == 0)
		usleep(500);
	while (!is_end_of_simulation(curr))
	{
		take_forks(left, curr);
		eat(left, curr);
		put_philosopher_to_bed(curr);
		think(curr);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		launched_threads;

	if (argc != 5 && argc != 6)
		return (printf("error: required arguments: \
<nb philos> <time die> <time eat> <time sleep> (<nb meals>)"), 1);
	if (init_data(&data, argc, argv))
		return (1);
	if (create_philos(&data))
		return (1);
	launched_threads = start_threads(&data);
	if (!launched_threads)
		check_for_deads(data.philos, &(data.rules));
	join_threads(&data, launched_threads);
	destroy_mutexes(&data, launched_threads);
	free(data.philos);
	return (0);
}
