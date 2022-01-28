/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollin <jcollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:04:05 by jcollin           #+#    #+#             */
/*   Updated: 2022/01/26 17:19:54 by jcollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	control_time(long time)
{
	long	t;

	t = get_time() + time;
	usleep((time - 10) * 1000);
	while (get_time() < t)
		usleep(500);
}

void	ft_error(int error, t_table *table)
{
	if (error == 0)
		write(1, "incorrect arguments\n", 20);
	if (error == 1)
		write(1, "mutex error\n", 10);
	if (error == 2)
		write(1, "create thread error\n", 20);
	if (error == 3)
		write(1, "malloc error\n", 20);
	free(table);
	return ;
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	c;

	c = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] <= 47 || str[i] >= 58)
			return (-1);
		i++;
	}
	i = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		c *= 10;
		c += (str[i] - '0');
		i++;
	}
	if (c > 2147483647)
		return (-1);
	return ((int) c);
}

int	parser(int argc, char **argv, t_table *table)
{
	if (argc < 5 || argc > 6)
	{
		ft_error(0, table);
		return (0);
	}
	table->count_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->count_eat = ft_atoi(argv[5]) + 1;
	else
		table->count_eat = -2;
	if (table->count_philo == -1 || table->count_philo == 0 \
	|| table->time_to_die == -1 || table->time_to_die == 0 \
	|| table->count_philo > 200 \
	|| table->time_to_eat == -1 || table->time_to_eat == 0 \
	|| table->time_to_sleep == -1 || table->time_to_sleep == 0 \
	|| table->count_eat == -1 || table->count_eat == 1)
	{
		ft_error(0, table);
		return (0);
	}
	return (1);
}
