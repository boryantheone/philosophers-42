/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollin <jcollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:04:24 by jcollin           #+#    #+#             */
/*   Updated: 2022/01/26 16:04:25 by jcollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_kill_pids(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->count_philo)
		kill(table->pids[i], SIGKILL);
}

void	*check_death(void *args)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *) args;
	table = philo->table;
	while (1)
	{
		if ((get_time() - philo->last_eat) > table->time_to_die \
		&& philo->count_eat != 0)
		{
			sem_wait(table->text);
			printf("%lu %d is died \n", (get_time() - \
			table->start), philo->id);
			exit(1);
		}
		if ((get_time() - philo->last_eat) > table->time_to_die \
		&& philo->count_eat == 0)
		{
			sem_wait(table->text);
			exit(1);
		}
		usleep(1000);
	}
	return (NULL);
}

void	ft_print(t_table *table, t_philo *philo, char *str)
{
	sem_wait(table->text);
	printf("%ld %d %s\n", get_time() - table->start, philo->id, str);
	sem_post(table->text);
}

static void	ft_eating(t_table *table, t_philo *philo)
{
	sem_wait(table->sem_forks);
	ft_print(table, philo, "has taken a fork");
	sem_wait(table->sem_forks);
	ft_print(table, philo, "has taken a fork");
	philo->last_eat = get_time();
	ft_print(table, philo, "is eating");
	control_time(table->time_to_eat);
	sem_post(table->sem_forks);
	sem_post(table->sem_forks);
}

void	ft_simulation(t_table *table, int i)
{
	t_philo	philo;

	init_philo(table, &philo, i);
	pthread_create(&philo.death_check, NULL, check_death, &philo);
	if (i % 2 != 0)
		usleep(10000);
	while (1)
	{
		if (--philo.count_eat != 0)
		{
			ft_eating(table, &philo);
			if (philo.count_eat != 1)
			{
				ft_print(table, &philo, "is sleeping");
				control_time(table->time_to_sleep);
				ft_print(table, &philo, "is thinking");
			}
		}
		else
			break ;
	}
	pthread_join(philo.death_check, NULL);
	exit(0);
}
