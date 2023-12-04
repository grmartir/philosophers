/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmartir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:35:25 by grmartir          #+#    #+#             */
/*   Updated: 2023/11/06 22:35:26 by grmartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H
# include <semaphore.h>
# include <signal.h>
# include <pthread.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_params
{
	pthread_t	death_thread;
	int			num;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meal_max;
	long		start_time;
	sem_t		*sem_console;
	sem_t		*sem_forks;
	sem_t		*finished;
}	t_params;

typedef struct s_phil
{
	pid_t		pid;
	int			pos;
	long		last_meal;
	sem_t		*sem_last_meal;
	int			meal_count;
	t_params	*params;
}	t_phil;

// death.c
void	*check_death(void *arg);
void	*wait_death(void *arg);
int		stop_process(t_phil **philos, t_params *params);
// forks.c
void	take_fork(t_phil *phil);
void	release_forks_and_sleep(t_phil *phil);
// init.c
int		create_philos(t_phil **philos, t_params	*params);
int		init_params(t_params *params, int argc, char **argv);
// main.c
int		philo_life(t_phil *phil);
// process.c
int		create_process(t_phil **philos, t_params *params);
int		wait_process(t_phil **philos, t_params *params);
// utils.c
void	ft_usleep(long int time_in_ms);
void	write_state(char *str, t_phil *phil);
long	get_timestamp(void);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
int		ft_error(char *str);
#endif
