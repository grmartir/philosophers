/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmartir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:34:42 by grmartir          #+#    #+#             */
/*   Updated: 2023/11/06 22:34:46 by grmartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	free_all(t_phil*philos, t_fork *forks, int exit_code)
{
	free(philos);
	free(forks);
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
	t_fork		*forks;
	int			return_code;

	return_code = EXIT_SUCCESS;
	if (!check_num(argc, argv))
		return (ft_error("Error"));
	if (!init_params(&params, argc, argv))
		return (0);
	if (!create_philos(&philos, &forks, &params))
		return (0);
	if (!create_threads(&philos, &params, argc))
		return_code = stop_threads(&philos[0]);
	if (!wait_threads(&philos, &params))
		return (free_all(philos, forks, 0));
	return (free_all(philos, forks, return_code));
}
