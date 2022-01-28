/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollin <jcollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:04:53 by jcollin           #+#    #+#             */
/*   Updated: 2022/01/27 10:07:36 by jcollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo {
	pthread_t		thread;
	int				id;
	int				count_eat;
	int				left;
	int				right;
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
	pthread_t		death;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*text;
}	t_table;
//parser
int		parser(int argc, char **argv, t_table *table);
void	ft_error(int error, t_table *table);
long	get_time(void);
void	control_time(long time);
//philo_utils
void	*check_death(void *args);
void	*ft_living(void *args);

void	create_thread(t_table *table);
void	init_philo(t_table *table);

#endif
