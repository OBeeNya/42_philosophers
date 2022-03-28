/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:10:46 by baubigna          #+#    #+#             */
/*   Updated: 2022/03/21 16:12:02 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_fork(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_of_philos)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		if (i == 0)
			rules->philos[i].right_fork = \
				&rules->forks[rules->nb_of_philos - 1];
		else
			rules->philos[i].right_fork = &rules->forks[i - 1];
		i++;
	}
}

long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	init_rules(t_rules *rules)
{
	int				i;

	rules->starting_time = get_time();
	pthread_mutex_init(&rules->check_death, NULL);
	pthread_mutex_init(&rules->msg, NULL);
	rules->philos = malloc(sizeof(t_philo) * rules->nb_of_philos);
	if (!rules->philos)
		return ;
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_of_philos);
	if (!rules->forks)
		return ;
	i = 0;
	while (i < rules->nb_of_philos)
	{
		rules->philos[i].position = i + 1;
		rules->philos[i].cycles_left = rules->nb_of_cycles;
		rules->philos[i].dead = 0;
		rules->philos[i].last_eaten = rules->starting_time;
		rules->philos[i].rules = rules;
		rules->philos[i].left_fork = &rules->forks[i];
		rules->philos[i].rules = rules;
		pthread_mutex_init(&rules->philos[i].lock, NULL);
		i++;
	}
	init_fork(rules);
}

int	create_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_of_philos)
	{
		if (pthread_create(&rules->philos[i].philo_thread, NULL,
				(void *)pre_routine, (void *)&rules->philos[i]))
			return (0);
		i++;
	}
	if (pthread_create(&rules->checker, NULL, (void *)checker, (void *)rules))
		return (0);
	return (1);
}

void	free_rules(t_rules *rules)
{
	int	i;

	pthread_mutex_destroy(&rules->msg);
	pthread_mutex_destroy(&rules->check_death);
	i = 0;
	while (i < rules->nb_of_philos)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		pthread_mutex_destroy(&rules->philos[i].lock);
		i++;
	}
	free(rules->forks);
	free(rules->philos);
}
