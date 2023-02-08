/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:28:21 by stde-la-          #+#    #+#             */
/*   Updated: 2023/02/07 17:27:49 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_forks
{
	int	left;
	int	right;
}				t_forks;


typedef struct s_philosopher
{
	int		id;
	t_forks	forks;
}				t_philosopher;


typedef struct s_data
{
	int 			philosophers_amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				required_eating_amount;
	t_philosopher	*philosophers;
}				t_data;


#endif