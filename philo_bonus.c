/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollin <jcollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:04:13 by jcollin           #+#    #+#             */
/*   Updated: 2022/01/26 17:13:17 by jcollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphore(t_table *table)
{
	sem_unlink("fork_sem");
	sem_unlink("text");
	table->text = sem_open("fork_sem", O_CREAT | O_EXCL, 0777, 1);
	table->sem_forks = sem_open("text", O_CREAT | O_EXCL, 0777, \
								table->count_philo);
	if (table->text <= 0 || table->sem_forks <= 0)
		return (1);
	return (0);
}

void	init_philo(t_table *table, t_philo *philo, int i)
{
	philo->id = i + 1;
	philo->count_eat = table->count_eat;
	philo->last_eat = table->start;
	philo->table = table;
}

void	ft_wait(t_table *table)
{
	int	i;
	int	status;

	i = -1;
	while (++i < table->count_philo)
	{
		waitpid(-1, &status, 0);
		if (status)
		{
			ft_kill_pids(table);
			break ;
		}
	}
	sem_close(table->sem_forks);
	sem_close(table->text);
	free(table->pids);
	free(table);
}

int	create_pids(t_table *table)
{
	int	i;

	i = -1;
	table->pids = (pid_t *)(malloc(sizeof(pid_t) * table->count_philo));
	if (table->pids == NULL)
		return (1);
	table->start = get_time();
	while (++i < table->count_philo)
	{
		table->pids[i] = fork();
		if (table->pids[i] == -1)
			return (1);
		else if (table->pids[i] == 0)
			ft_simulation(table, i);
		usleep(100);
	}
	ft_wait(table);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		*table;

	table = malloc(sizeof(t_table));
	if (!(parser(argc, argv, table)))
		return (0);
	if (init_semaphore(table))
		return (ft_error(1, table));
	if (create_pids(table))
		return (ft_error(2, table));
}
