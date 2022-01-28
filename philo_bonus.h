/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollin <jcollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:03:55 by jcollin           #+#    #+#             */
/*   Updated: 2022/01/26 17:13:01 by jcollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo {
	int				id;
	pthread_t		death_check;
	int				count_eat;
	long int		last_eat;
	struct s_table	*table;
}	t_philo;

typedef struct s_table {
	int				count_philo;
	int				count_eat;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		start;
	pid_t			*pids;
	sem_t			*sem_forks;
	sem_t			*text;	
}	t_table;
//parser
int		parser(int argc, char **argv, t_table *table);
int		ft_error(int error, t_table *table);
long	get_time(void);
void	control_time(long time);
//philo_utils_bonus
void	init_philo(t_table *table, t_philo *philo, int i);
int		init_semaphore(t_table *table);
int		create_pids(t_table *table);
void	*check_death(void *args);
void	ft_simulation(t_table *table, int i);
void	ft_kill_pids(t_table *table);

#endif
