/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:08:24 by bruno             #+#    #+#             */
/*   Updated: 2022/12/07 03:05:52 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int		clean_philo(t_table *table);
static _Bool	destroy_mutex(t_table *table);

int	main(int argc, char **argv)
{
	t_table	table;
	int		tmp;

	tmp = philo_init(argc, argv, &table);
	if (tmp == 18)
		return (1);
	else if (tmp)
		return (clean_philo(&table));
	if (philo_start(&table))
		return (clean_philo(&table));
	clean_philo(&table);
	return (0);
}

static int	clean_philo(t_table *table)
{
	if (destroy_mutex(table))
		write(2, "Error destroying mutex recurse\n", 31);
	if (table->forks)
		free(table->forks);
	if (table->time)
		free(table->time);
	if (table->philo)
		free(table->philo);
	return (1);
}

static _Bool	destroy_mutex(t_table *table)
{
	size_t	count;

	count = 0;
	while (count < table->n_phi)
		pthread_mutex_destroy(&table->forks[count++]);
	pthread_mutex_destroy(&table->util);
	pthread_mutex_destroy(&table->print);
	return (0);
}
