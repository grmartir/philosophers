/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmartir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:34:29 by grmartir          #+#    #+#             */
/*   Updated: 2023/11/06 22:34:30 by grmartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	take_fork(char fork_name, t_phil *phil)
{
	int		*taken;
	t_fork	*fork;

	if (!is_dead(phil))
	{
		taken = &(phil->r_taken);
		fork = phil->r_fork;
		if (fork_name == 'l')
		{
			taken = &(phil->l_taken);
			fork = phil->l_fork;
		}
		pthread_mutex_lock(&(fork->lock));
		if (!(*taken) && !fork->used)
		{
			*taken = 1;
			fork->used = 1;
			pthread_mutex_unlock(&(fork->lock));
			write_state("has taken a fork", phil);
		}
		else
			pthread_mutex_unlock(&(fork->lock));
	}
}

void	release_fork(char fork_name, t_phil *phil)
{
	int		*taken;
	t_fork	*fork;

	taken = &(phil->r_taken);
	fork = phil->r_fork;
	if (fork_name == 'l')
	{
		taken = &(phil->l_taken);
		fork = phil->l_fork;
	}
	pthread_mutex_lock(&(fork->lock));
	*taken = 0;
	fork->used = 0;
	pthread_mutex_unlock(&(fork->lock));
}

void	release_forks_and_sleep(t_phil *phil)
{
	release_fork('r', phil);
	release_fork('l', phil);
	write_state("is sleeping", phil);
	ft_usleep(phil->params->time_to_sleep);
}
