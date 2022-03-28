/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:59:06 by baubigna          #+#    #+#             */
/*   Updated: 2022/03/21 14:59:48 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				position;
	int				cycles_left;
	int				dead;
	long int		last_eaten;
	pthread_mutex_t	lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		philo_thread;
	struct s_rules	*rules;
}				t_philo;

typedef struct s_rules
{
	int				nb_of_philos;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				nb_of_cycles;
	long int		starting_time;
	int				death;
	pthread_mutex_t	check_death;
	pthread_mutex_t	msg;
	pthread_mutex_t	*forks;
	pthread_t		checker;
	t_philo			*philos;
}				t_rules;

/* funcs_0 */
void		init_fork(t_rules *rules);
long int	get_time(void);
void		init_rules(t_rules *rules);
int			create_threads(t_rules *rules);
void		free_rules(t_rules *rules);

/* funcs_1 */
int			join_threads(t_rules *rules);
void		display_msg(t_philo *philo, char *s);
void		waiting(long int time);
void		philo_eats(t_philo *philo, pthread_mutex_t *fork_a,
				pthread_mutex_t *fork_b);
void		pre_routine(t_philo *philo);

/* funcs_2 */
void		philo_sleeps(t_philo *philo);
int			philo_dies(t_philo *philo);
void		checker(t_rules *rules);
void		routine(t_philo *philo);

#endif
