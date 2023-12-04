/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmartir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:35:47 by grmartir          #+#    #+#             */
/*   Updated: 2023/11/06 22:35:49 by grmartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

void	take_fork(t_phil *phil)
{
	sem_wait(phil->params->sem_forks);
	write_state("has taken a fork", phil);
}

void	release_forks_and_sleep(t_phil *phil)
{
	sem_post(phil->params->sem_forks);
	sem_post(phil->params->sem_forks);
	write_state("is sleeping", phil);
	ft_usleep(phil->params->time_to_sleep);
}
