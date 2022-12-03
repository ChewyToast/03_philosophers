/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:08:24 by bruno             #+#    #+#             */
/*   Updated: 2022/12/03 13:51:42 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	clean_philo(t_table *table);
_Bool	destroy_mutex(t_table *table);

int	main(int argc, char **argv)
{
	t_table	table;
	int		tmp;

	printf("-------INIT---------\n");
	tmp = philo_init(argc, argv, &table);
	if (tmp == 18)
	{
		printf("parse error\n");
		return (1);
	}
	else if (tmp)
	{
		printf("Parse error\n");
		clean_philo(&table);
		return (1);
	}
	printf("---------------------\n");
	printf("-------start---------\n");
	printf("NUMBER: |%ld|\n", table.n_phi);
	if (philo_start(&table))
	{
		clean_philo(&table);
		return (1);
	}
	printf("---------------------\n");
	printf("-------clean---------\n");
	clean_philo(&table);
	return (0);
}

void	clean_philo(t_table *table)
{
	if (destroy_mutex(table))
		printf("Error destroying mutex recurse\n");
	if (table->forks)
		free(table->forks);
	if (table->time)
		free(table->time);
	if (table->philo)
		free(table->philo);
}

_Bool	destroy_mutex(t_table *table)
{
	size_t	count;

	count = 0;
	while (count < table->n_phi)
	{
		pthread_mutex_destroy(&table->forks[count]);
		printf("destroying mutex: |%ld| n_phi: |%ld|\n", count, table->n_phi);
		count++;
	}
	pthread_mutex_destroy(&table->util);
	pthread_mutex_destroy(&table->print);
	(void)table;
	return (0);
}
