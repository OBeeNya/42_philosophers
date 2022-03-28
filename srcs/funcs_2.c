/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:24:42 by baubigna          #+#    #+#             */
/*   Updated: 2022/03/21 15:23:44 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleeps(t_philo *philo)
{
	display_msg(philo, "is sleeping");
	waiting(philo->rules->time_to_sleep);
}

int	philo_dies(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if ((get_time() - philo->last_eaten) >= philo->rules->time_to_die && \
		!philo->rules->death)
	{
		display_msg(philo, "died");
		pthread_mutex_unlock(&philo->lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->lock);
	return (1);
}

void	checker(t_rules *rules)
{
	int	i;

	waiting(2);
	while (1)
	{
		i = 0;
		while (i < rules->nb_of_philos)
		{
			if (!philo_dies(&rules->philos[i]))
			{
				pthread_mutex_lock(&rules->check_death);
				rules->death = 1;
				pthread_mutex_unlock(&rules->check_death);
				return ;
			}
			i++;
			waiting(2);
		}
	}
}

void	routine(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->rules->check_death);
		if (!philo->rules->death)
		{
			pthread_mutex_unlock(&philo->rules->check_death);
			if (!(philo->position % 2))
				philo_eats(philo, philo->left_fork, philo->right_fork);
			else
				philo_eats(philo, philo->right_fork, philo->left_fork);
			philo_sleeps(philo);
			display_msg(philo, "is thinking");
			waiting(1);
			if (!philo->cycles_left)
				return ;
		}
		else
		{
			pthread_mutex_unlock(&philo->rules->check_death);
			return ;
		}
	}
}
