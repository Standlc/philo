#include "../philo.h"

void	put_philosopher_status(t_philosopher *curr, char *status)
{
	int	timestamp;

	pthread_mutex_lock(curr->print_mutex);
	if (!is_end_of_simulation(curr))
	{
		timestamp = now() - curr->rules->starting_time;
		printf("%d %d %s\n", timestamp, curr->id, status);
	}
	pthread_mutex_unlock(curr->print_mutex);
}

void	count_philo_meals(t_philosopher *curr)
{
	pthread_mutex_lock(&(curr->eating_count_mutex));
	curr->eating_count += 1;
	if (curr->eating_count == curr->rules->required_eat_count)
	{
		pthread_mutex_lock(curr->philos_finished_eating_mutex);
		*(curr->philos_finished_eating) += 1;
		if (*(curr->philos_finished_eating) == curr->rules->amount)
			end_simulation(curr);
		pthread_mutex_unlock(curr->philos_finished_eating_mutex);
	}
	pthread_mutex_unlock(&(curr->eating_count_mutex));
}

void	give_forks_back(t_philosopher *left, t_philosopher *curr)
{
	pthread_mutex_unlock(&(left->fork_mutex));
	pthread_mutex_unlock(&(curr->fork_mutex));
}
