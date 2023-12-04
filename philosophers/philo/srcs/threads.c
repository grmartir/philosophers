/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmartir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:34:51 by grmartir          #+#    #+#             */
/*   Updated: 2023/11/06 22:34:53 by grmartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	create_threads(t_phil **philos, t_params *params, int argc)
{
	int	cur;

	params->start_time = get_timestamp();
	cur = 0;
	while (cur < params->num)
	{
		if (pthread_create(&((*philos)[cur].thread), NULL,
			philo_life, &((*philos)[cur])))
			return (0);
		cur++;
	}
	if (argc == 5)
	{
		if (pthread_create(&(params->death_thread), NULL,
				check_philos_death, philos))
			return (0);
	}
	else
		if (pthread_create(&(params->death_thread), NULL,
				check_philos_death2, philos))
			return (0);
	return (1);
}

int	wait_threads(t_phil **philos, t_params *params)
{
	int	cur;
	int	return_code;

	cur = 0;
	return_code = 1;
	while (cur < params->num)
	{
		if (pthread_join((*philos)[cur].thread, NULL))
			return_code = 0;
		cur++;
	}
	pthread_join((params->death_thread), NULL);
	return (return_code);
}

void	*philo_life(void *arg)
{
	t_phil		*phil;

	phil = (t_phil *)arg;
	if (phil->pos % 2 != 0)
		ft_usleep(phil->params->time_to_eat);
	while (!is_dead(phil))
	{
		if (phil->meal_count >= phil->params->meal_max
			&& phil->params->meal_max > 0)
			break ;
		take_fork('l', phil);
		if (phil->l_taken)
			take_fork('r', phil);
		if (phil->r_taken && phil->l_taken)
		{
			write_state("is eating", phil);
			ft_usleep(phil->params->time_to_eat);
			phil->meal_count++;
			pthread_mutex_lock(&(phil->m_last_meal));
			phil->last_meal = get_timestamp() - phil->params->start_time;
			pthread_mutex_unlock(&(phil->m_last_meal));
			release_forks_and_sleep(phil);
		}
	}
	return (NULL);
}

int	check_philo_death2(t_phil *phil, long cur_time)
{
	int	dead;
	int	last_meal;

	dead = 0;
	pthread_mutex_lock(&(phil->m_last_meal));
	last_meal = cur_time - phil->last_meal;
	pthread_mutex_unlock(&(phil->m_last_meal));
	if (last_meal > phil->params->time_to_die)
	{
		pthread_mutex_lock(&(phil->params->console_mutex));
		pthread_mutex_lock(&(phil->params->m_is_dead));
		phil->params->is_dead = 1;
		pthread_mutex_unlock(&(phil->params->m_is_dead));
		printf("%09ld %d is eating\n", cur_time, phil->pos);
		pthread_mutex_unlock(&(phil->params->console_mutex));
		dead = 1;
	}
	return (dead);
}

void	*check_philos_death2(void *arg)
{
	t_params	*params;
	t_phil		**philos;
	long		cur_time;
	int			cur;

	philos = (t_phil **)arg;
	params = philos[0]->params;
	while (1)
	{
		cur = 0;
		cur_time = get_timestamp() - params->start_time;
		while (cur < params->num)
		{
			if (check_philo_death2(&(*philos)[cur], cur_time))
				return (NULL);
			cur++;
		}
		ft_usleep(1);
	}
	return (NULL);
}
