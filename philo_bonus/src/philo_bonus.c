/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:08:24 by bruno             #+#    #+#             */
/*   Updated: 2022/12/06 04:01:55 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static int		clean_philo(t_table *table, int8_t mode);
static _Bool	destroy_sem(t_table *table);

int	main(int argc, char **argv)
{
	t_table	table;
	int		tmp;

	tmp = philo_init(argc, argv, &table);
	if (tmp == 18)
		return (1);
	else if (tmp)
		exit (clean_philo(&table, 0));
	if (philo_start(&table))
		exit (clean_philo(&table, 1));
	clean_philo(&table, 0);
	exit (0);
}

static int	clean_philo(t_table *table, int8_t mode)
{
	if (mode)
		kill_all(table);
	if (destroy_sem(table))
		write(2, "Error destroying sem recurse\n", 29);
	if (table->time)
		free(table->time);
	// if (table->pid)
		// free(table->pid);
	return (1);
}

void	kill_all(t_table *table)
{
	// (void)table;
	while (*(table->pid))
		kill(*(table->pid++), SIGTERM);
}

static _Bool	destroy_sem(t_table *table)
{
	sem_close(table->forks);
	sem_close(table->util);
	sem_close(table->print);
	sem_close(table->dead);
	return (0);
}
