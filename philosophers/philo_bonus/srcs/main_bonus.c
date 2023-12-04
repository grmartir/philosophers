/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmartir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:36:54 by grmartir          #+#    #+#             */
/*   Updated: 2023/11/06 22:36:56 by grmartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

int	free_all(t_phil *philos, t_params *params, int exit_code)
{
	free(philos);
	sem_close(params->sem_forks);
	sem_close(params->sem_console);
	sem_close(params->finished);
	return (exit_code);
}

int	check_num(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_phil		*philos;
	int			return_code;

	return_code = EXIT_SUCCESS;
	if (!check_num(argc, argv))
		return (ft_error("Error"));
	if (!init_params(&params, argc, argv))
		return (0);
	if (!create_philos(&philos, &params))
		return (0);
	if (!create_process(&philos, &params))
		return_code = stop_process(&philos, &params);
	if (!wait_process(&philos, &params))
		return (free_all(philos, &params, 0));
	return (free_all(philos, &params, return_code));
}
