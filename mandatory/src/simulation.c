/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 09:48:52 by bruno             #+#    #+#             */
/*   Updated: 2022/12/03 17:17:08 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void		philo_routine(t_table *table);
static _Bool	routine_init(t_table *table, t_philo *this_philo);

_Bool	philo_start(t_table *table)
{
	pthread_t	tmp;
	size_t		count;

	count = 0;
	tmp = 0;
	if (pthread_mutex_lock(&table->util))
	{
		printf("Lock error\n");
		return (1);
	}
	while (count < table->n_phi)
	{
		if (pthread_create(&tmp, NULL, (void *)&philo_routine, (void *)table))
		{
			printf("create error\n");
			return (1);
		}
		count++;
	}
	if (usleep(500))
	{
		printf("usleep error\n");
		return (1);
	}
	if (pthread_mutex_unlock(&table->util))
	{
		printf("unlocl error\n");
		return (1);
	}
	while (1);
	return (0);
}

static void	philo_routine(t_table *table)
{
	t_philo	*this_philo;

	this_philo = &table->philo[table->phi_counter];
	if (pthread_mutex_lock(&table->print))
		printf("ERROR\n");
	routine_init(table, this_philo);
	if (pthread_mutex_unlock(&table->print))
		printf("ERROR\n");
	if (pthread_mutex_lock(&table->util))
		printf("ERROR\n");
	if (pthread_mutex_unlock(&table->util))
		printf("ERROR\n");
	if (pthread_mutex_lock(&table->print))
		printf("ERROR\n");
	printf("finish %ld with right: [%p]\n", this_philo->num, this_philo->right);
	if (pthread_mutex_unlock(&table->print))
		printf("ERROR\n");
}

static _Bool	routine_init(t_table *table, t_philo *this_philo)
{
	table->phi_counter += 1;
	this_philo->num = table->phi_counter;
	printf("\n\n>>>>> PHILO |%ld|(%ld)\n", this_philo->num,
		table->phi_counter - 1);
	this_philo->eat_count = 0;
	printf("Eat count: |%ld|\n", this_philo->eat_count);
	if (this_philo->num == 1)
	{
		this_philo->right = &table->forks[table->n_phi - 1];
		printf("Right fork: |%ld|(%ld)\n", table->n_phi, table->n_phi - 1);
	}
	else
	{
		this_philo->right = &table->forks[table->phi_counter - 2];
		printf("Right fork: |%ld|(%ld)\n", table->phi_counter - 1, table->phi_counter - 2);
	}
	this_philo->left = &table->forks[table->phi_counter - 1];
	printf("Left fork: |%ld|(%ld)\n", table->phi_counter,
		table->phi_counter - 1);
	return (0);
}
