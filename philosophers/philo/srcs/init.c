/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmartir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:34:35 by grmartir          #+#    #+#             */
/*   Updated: 2023/11/06 22:34:37 by grmartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	init_philo(t_phil *phil, t_fork **forks, t_params *params, int cur)
{
	phil->params = params;
	phil->pos = cur;
	phil->last_meal = 0;
	phil->meal_count = 0;
	phil->r_fork = &((*forks)[cur]);
	phil->r_taken = 0;
	phil->l_taken = 0;
	if (cur == params->num - 1)
		phil->l_fork = &((*forks)[0]);
	else
		phil->l_fork = &((*forks)[cur + 1]);
	phil->l_fork->used = 0;
	pthread_mutex_init(&(phil->m_last_meal), NULL);
	pthread_mutex_init(&(phil->l_fork->lock), NULL);
}

int	create_philos(t_phil **philos, t_fork **forks, t_params	*params)
{
	int	cur;

	params->is_dead = 0;
	*philos = malloc(sizeof(t_phil) * params->num);
	if (!(*philos))
		return (0);
	*forks = malloc(sizeof(t_fork) * params->num);
	if (!(*forks))
	{
		free(*philos);
		return (0);
	}
	cur = 0;
	while (cur < params->num)
	{
		init_philo(&(*philos)[cur], forks, params, cur);
		cur++;
	}
	return (1);
}

int	ft_error(char *str)
{
	if (str && *str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		return (0);
	}
	return (1);
}

int	init_params(t_params *params, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_error("Wrong usage of arguments"));
	params->num = ft_atoi(argv[1]);
	if (params->num < 1 || params->num > 200)
		return (ft_error("Wrong philo num"));
	params->time_to_die = ft_atoi(argv[2]);
	if (params->time_to_die <= 0)
		return (ft_error("Wrong time_to_die num"));
	params->time_to_eat = ft_atoi(argv[3]);
	if (params->time_to_eat <= 0)
		return (ft_error("Wrong time_to_eat num"));
	params->time_to_sleep = ft_atoi(argv[4]);
	if (params->time_to_sleep <= 0)
		return (ft_error("Wrong time_to_sleep num"));
	if (argc == 6)
	{
		params->meal_max = ft_atoi(argv[5]);
		if (params->meal_max <= 0)
			return (ft_error("Wrong meal_max num"));
	}
	else
		params->meal_max = -1;
	pthread_mutex_init(&(params->console_mutex), NULL);
	pthread_mutex_init(&(params->m_is_dead), NULL);
	return (1);
}
