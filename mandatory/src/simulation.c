/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 09:48:52 by bruno             #+#    #+#             */
/*   Updated: 2022/12/03 22:56:07 by bmoll-pe         ###   ########.fr       */
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
	pthread_mutex_lock(&table->util);
	while (count < table->n_phi)
	{
		if (pthread_create(&tmp, NULL, (void *)&philo_routine, (void *)table))
		{
			printf("create error\n");
			return (1);
		}
		count++;
	}
	my_sleep(200);
	pthread_mutex_unlock(&table->util);
	table->time->tstart = get_time();
	count = 0;
	while (!table->dead)
	{
		if (count == table->n_phi)
			count = 0;
		if (table->philo[count].eat_count == 0)
		{
			if (table->time->tdie <= get_time() - table->time->tstart)
			{
				table->dead = 1;
				pthread_mutex_lock(&table->print);
				printf("\n-1- %lld %zu %s\n", get_time() - table->time->tstart, count + 1, "died");
			}
		}
		else
		{
			if (table->time->tdie <= table->philo[count].last_eat - table->time->tstart)
			{
				table->dead = 1;
				pthread_mutex_lock(&table->print);
				printf("\n-2- %lld %zu %s---> |%lld|\n", get_time() - table->time->tstart, count + 1, "died", table->philo[count].last_eat - table->time->tstart);
			}
		}
		count++;
	}
	printf("\n---END----\n\n");
	pthread_mutex_unlock(&table->print);
	my_sleep(500);
	return (0);
}

static void	philo_routine(t_table *table)
{
	t_philo	*this_philo;

	pthread_mutex_lock(&table->print);
	this_philo = &table->philo[table->phi_counter];
	routine_init(table, this_philo);
	while (!table->dead)
	{
		pthread_mutex_lock(this_philo->left);// agafa esquerra
		printer("has taken a fork", table, this_philo, get_time() - table->time->tstart);
		pthread_mutex_lock(this_philo->right);// agafa dreta
		printer("has taken a fork", table, this_philo, get_time() - table->time->tstart);
		this_philo->last_eat = get_time();
		this_philo->eat_count += 1;
		printer("is eating", table, this_philo, this_philo->last_eat - table->time->tstart);
		my_sleep(table->time->teat);// menja
		pthread_mutex_unlock(this_philo->left);// deixa esquerra
		pthread_mutex_unlock(this_philo->right);// deixa dreta
		printer("is sleeping", table, this_philo, get_time() - table->time->tstart);
		my_sleep(table->time->tsleep);// dorm
		printer("is thinking", table, this_philo, get_time() - table->time->tstart);
	}
	pthread_mutex_lock(&table->print);
	printf("\n\n-> CHILD DEAD <-\n\n");
	pthread_mutex_unlock(&table->print);
}

static _Bool	routine_init(t_table *table, t_philo *this_philo)
{
	table->phi_counter += 1;
	this_philo->num = table->phi_counter;
	printf("\n>>>>> PHILO |%ld|(%ld)\n", this_philo->num,
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
	printf("Left fork: |%ld|(%ld)\n\n", table->phi_counter,
		table->phi_counter - 1);
	pthread_mutex_unlock(&table->print);
	pthread_mutex_lock(&table->util);
	pthread_mutex_unlock(&table->util);
	pthread_mutex_lock(&table->print);
	pthread_mutex_unlock(&table->print);
	if (this_philo->num % 2)
		my_sleep(8);
	return (0);
}
