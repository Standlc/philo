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

void	*routine(void *args)
{
	t_philosopher	*left;
	t_philosopher	*curr;

	curr = (t_philosopher *)args;
	left = get_philosopher_to_left(curr);
	if (curr->id % 2 == 0)
		usleep(500);
	while (!is_end_of_simulation(curr))
	{
		if (curr->rules->amount == 1)
			return (put_philosopher_status(curr, "has taken a fork"), NULL);
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
		return (printf("error: required arguments: \
<nb philos> <time die> <time eat> <time sleep> (<nb meals>)"), 1);
	if (init_data(&data, argc, argv))
		return (1);
	if (create_philos(&data))
		return (1);
	start_threads(&data);
	check_for_deads(data.philos, &(data.rules));
	join_threads(&data);
	free(data.philos);
	return (0);
}
