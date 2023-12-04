/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmartir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:35:34 by grmartir          #+#    #+#             */
/*   Updated: 2023/11/06 22:35:36 by grmartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

int	stop_process(t_phil **philos, t_params *params)
{
	int	cur;

	cur = 0;
	while (cur < params->num)
		kill((*philos)[cur++].pid, SIGTERM);
	return (0);
}

void	*check_death(void *arg)
{
	t_phil		*phil;
	t_params	*params;
	int			cur_time;

	phil = (t_phil *)arg;
	params = phil->params;
	while (1)
	{
		cur_time = get_timestamp() - params->start_time;
		if (cur_time - phil->last_meal > phil->params->time_to_die)
		{
			sem_wait(phil->params->sem_console);
			printf("%09d %d died\n", cur_time, phil->pos);
			sem_post(phil->params->finished);
		}
		ft_usleep(1);
	}
	return (NULL);
}

void	*wait_death(void *arg)
{
	t_phil		**philos;
	t_params	*params;

	philos = (t_phil **)arg;
	params = philos[0]->params;
	sem_wait(params->finished);
	stop_process(philos, params);
	return (NULL);
}
