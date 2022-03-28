/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:35:01 by baubigna          #+#    #+#             */
/*   Updated: 2022/03/21 15:23:50 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_rules *rules)
{
	int	i;

	if (pthread_join(rules->checker, NULL))
		return (0);
	i = 0;
	while (i < rules->nb_of_philos)
	{
		if (pthread_join(rules->philos[i].philo_thread, NULL))
			return (0);
		i++;
	}
	return (1);
}

void	display_msg(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->rules->check_death);
	if (!philo->dead && philo->cycles_left && !philo->rules->death)
	{
		pthread_mutex_lock(&philo->rules->msg);
		printf("%ld %d %s\n", get_time() - philo->rules->starting_time,
			philo->position, s);
		pthread_mutex_unlock(&philo->rules->msg);
	}
	pthread_mutex_unlock(&philo->rules->check_death);
}

void	waiting(long int time)
{
	long int	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(500);
}

void	philo_eats(t_philo *philo, pthread_mutex_t *fork_a,
	pthread_mutex_t *fork_b)
{
	pthread_mutex_lock(fork_a);
	display_msg(philo, "has taken a fork");
	pthread_mutex_lock(fork_b);
	display_msg(philo, "has taken a fork");
	display_msg(philo, "is eating");
	pthread_mutex_lock(&philo->lock);
	philo->cycles_left--;
	philo->last_eaten = get_time();
	pthread_mutex_unlock(&philo->lock);
	waiting(philo->rules->time_to_eat);
	pthread_mutex_unlock(fork_b);
	pthread_mutex_unlock(fork_a);
}

void	pre_routine(t_philo *philo)
{
	if (philo->rules->nb_of_philos == 1)
	{
		display_msg(philo, "has taken a fork");
		waiting(philo->rules->time_to_die);
	}
	else
		routine(philo);
	return ;
}
