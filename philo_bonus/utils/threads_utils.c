/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:26:42 by stde-la-          #+#    #+#             */
/*   Updated: 2023/02/15 15:26:43 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// int	join_threads(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->rules.amount)
// 	{
// 		pthread_join(data->philos[i].thread, NULL);
// 		i++;
// 	}
// 	return (0);
// }


// int	start_threads(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->rules.amount)
// 	{
// 		pthread_create(&(data->philos[i].thread),
// 			NULL, routine, &(data->philos[i]));
// 		i++;
// 	}
// 	return (0);
// }
