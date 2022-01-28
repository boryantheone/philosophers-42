/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollin <jcollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:04:34 by jcollin           #+#    #+#             */
/*   Updated: 2022/01/27 10:06:51 by jcollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *args)
{
	t_table		*table;
	int			count;
	long int	sum;

	table = (t_table *) args;
	while (1)
	{
		count = -1;
		while (++count < table->count_philo)
		{
			sum = get_time() - table->philo[count].last_eat;
			if (sum > table->time_to_die && table->philo[count].count_eat != 0)
			{
				pthread_mutex_lock(table->text);
				printf("%lu %d is died \n", (get_time() - \
				table->start), table->philo[count].id);
				return (NULL);
			}
			if (sum > table->time_to_die && table->philo[count].count_eat == 0)
				return (NULL);
		}
	}
}

static void	*ft_simulation(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->table->text);
	printf("%lu %d is %s \n", (get_time() - philo->table->start), \
	philo->id, str);
	pthread_mutex_unlock(philo->table->text);
	return (NULL);
}

static void	ft_eating(t_philo	*philo)
{
	pthread_mutex_lock(&philo->table->fork[philo->left]);
	ft_simulation(philo, "take a fork");
	pthread_mutex_lock(&philo->table->fork[philo->right]);
	ft_simulation(philo, "take a fork");
	philo->last_eat = get_time();
	ft_simulation(philo, "eating");
	control_time(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->fork[philo->left]);
	pthread_mutex_unlock(&philo->table->fork[philo->right]);
}

void	*ft_living(void *args)
{
	t_philo	*philo;

	philo = (t_philo *) args;
	philo->last_eat = philo->table->start;
	while (1)
	{
		if (--philo->count_eat != 0)
		{
			ft_eating(philo);
			if (philo->count_eat != 1)
			{
				ft_simulation(philo, "sleeping");
				control_time(philo->table->time_to_sleep);
				ft_simulation(philo, "thinking");
			}
		}
		else
			break ;
	}
	return (0);
}
