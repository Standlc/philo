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

void	*routine(void *args)
{
	t_philosopher	*left;
	t_philosopher	*curr;

	curr = (t_philosopher *)args;
	left = get_philosopher_to_left(curr);
	if (curr->id % 2 == 0)
		usleep(curr->rules->time_to_eat);
	while (has_eaten_enough(curr) && !curr->rules->some_dead)
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

	if (argc != 5 && argc != 6)
		return (printf("You must pass the required arguments.\n"), 1);
	if (init_data(&data, argc, argv))
		return (1);
	if (create_philos(&data))
		return (printf("Malloc error\n"), 1);
	start_threads(&data);
	check_for_deads(data.philos, &(data.rules));
	join_threads(&data);
	free(data.philos);
	return (0);
}
