/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:50:01 by baubigna          #+#    #+#             */
/*   Updated: 2022/03/21 14:43:05 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_numeric(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

long int	ft_atoi(char *str)
{
	int			i;
	int			minus_count;
	long int	result;

	i = 0;
	minus_count = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus_count++;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	if (minus_count % 2 == 0)
		return (result);
	else
		return (-result);
}

int	check_args(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
	{
		printf("Please give 4 or 5 arguments.\n");
		return (0);
	}
	i = 1;
	while (i < ac)
	{
		if (!is_numeric(av[i]) || ft_atoi(av[i]) < 1
			|| ft_atoi(av[i]) > 2147483647)
		{
			printf("Please give positive int arguments.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_rules(int ac, char **av, t_rules *rules)
{
	rules->nb_of_philos = ft_atoi(av[1]);
	rules->time_to_die = ft_atoi(av[2]);
	rules->time_to_eat = ft_atoi(av[3]);
	rules->time_to_sleep = ft_atoi(av[4]);
	if (rules->nb_of_philos < 1 || rules->time_to_die < 1
		|| rules->time_to_eat < 1 || rules->time_to_sleep < 1)
	{
		printf("Please give positive int arguments.\n");
		return (0);
	}
	if (ac == 6)
	{
		rules->nb_of_cycles = ft_atoi(av[5]);
		if (rules->nb_of_cycles < 1)
		{
			printf("Please give positive int arguments.\n");
			return (0);
		}
	}
	else
		rules->nb_of_cycles = -1;
	rules->death = 0;
	init_rules(rules);
	return (1);
}

int	main(int ac, char **av)
{
	t_rules	rules;

	if (!check_args(ac, av) || !check_rules(ac, av, &rules))
		return (1);
	if (!create_threads(&rules))
	{
		free_rules(&rules);
		return (1);
	}
	if (!join_threads(&rules))
	{
		free_rules(&rules);
		return (1);
	}
	free_rules(&rules);
	return (0);
}
