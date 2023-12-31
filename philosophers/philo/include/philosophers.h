/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmartir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:33:16 by grmartir          #+#    #+#             */
/*   Updated: 2023/11/06 22:33:19 by grmartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_params
{
	int				num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_max;
	long			start_time;
	pthread_mutex_t	console_mutex;
	int				is_dead;
	pthread_mutex_t	m_is_dead;
	pthread_t		death_thread;
}	t_params;

typedef struct s_fork
{
	int				used;
	pthread_mutex_t	lock;
}	t_fork;

typedef struct s_phil
{
	pthread_t		thread;
	int				pos;
	long			last_meal;
	pthread_mutex_t	m_last_meal;
	int				meal_count;
	t_fork			*r_fork;
	int				r_taken;
	t_fork			*l_fork;
	int				l_taken;
	t_params		*params;
}	t_phil;

// death.c
int		is_dead(t_phil *phil);
void	*check_philos_death(void *arg);
int		stop_threads(t_phil *phil);
// forks.c
void	take_fork(char fork_name, t_phil *phil);
void	release_fork(char fork_name, t_phil *phil);
void	release_forks_and_sleep(t_phil *phil);
// init.c
int		create_philos(t_phil **philos, t_fork **forks, t_params	*params);
int		init_params(t_params *params, int argc, char **argv);
// main.c
void	*philo_life(void *arg);
// threads.c
int		create_threads(t_phil **philos, t_params *params, int argc);
int		wait_threads(t_phil **philos, t_params *params);
// utils.c
int		ft_atoi(const char *str);
void	ft_usleep(long int time_in_ms);
void	write_state(char *str, t_phil *phil);
long	get_timestamp(void);
size_t	ft_strlen(const char *str);
void	*check_philos_death2(void *arg);
int		check_philo_death2(t_phil *phil, long cur_time);
int		ft_error(char *str);

#endif
