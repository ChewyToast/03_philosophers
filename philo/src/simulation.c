/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 09:48:52 by bruno             #+#    #+#             */
/*   Updated: 2022/12/06 04:05:23 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void		philo_routine(t_table *table);
static _Bool	eat_enough(size_t eat_count, ssize_t eat_times);
static _Bool	routine_init(t_table *table, t_philo *this_philo);
static void		philo_start_iter(t_table *table);

int	philo_start(t_table *table)
{
	pthread_t	tmp;
	size_t		count;

	count = 0;
	tmp = 0;
	pthread_mutex_lock(&table->util);
	while (count < table->n_phi)
	{
		if (pthread_create(&tmp, NULL, (void *)&philo_routine, (void *)table))
			return (write(2, "philo: Error creating thread\n", 29));
		count++;
	}
	pthread_mutex_unlock(&table->util);
	table->time->tstart = get_time();
	philo_start_iter(table);
	my_sleep(255);
	return (0);
}

static void	philo_start_iter(t_table *table)
{
	size_t	count;

	count = 0;
	while (!table->dead)
	{
		if (count == table->n_phi)
			count = 0;
		if (table->philo[count].eat_count == 0)
		{
			if (table->time->tdie <= get_time() - table->time->tstart)
				set_dead(table, count);
		}
		else
		{
			if (table->time->tdie <= get_time() - table->philo[count].last_eat)
				set_dead(table, count);
		}
		count++;
	}
}

static void	philo_routine(t_table *table)
{
	t_philo	*this_philo;

	pthread_mutex_lock(&table->print);
	this_philo = &table->philo[table->phi_counter];
	routine_init(table, this_philo);
	while (!table->dead)
	{
		pthread_mutex_lock(this_philo->left);
		printer(TAF, table, this_philo, get_time() - table->time->tstart);
		pthread_mutex_lock(this_philo->right);
		printer(TAF, table, this_philo, get_time() - table->time->tstart);
		this_philo->last_eat = get_time();
		this_philo->eat_count += 1;
		printer(IEA, table, this_philo,
			this_philo->last_eat - table->time->tstart);
		my_sleep(table->time->teat);
		pthread_mutex_unlock(this_philo->left);
		pthread_mutex_unlock(this_philo->right);
		if (eat_enough(this_philo->eat_count, table->time->eat_times))
			break ;
		printer(ISS, table, this_philo, get_time() - table->time->tstart);
		my_sleep(table->time->tsleep);
		printer(IST, table, this_philo, get_time() - table->time->tstart);
	}
}

static _Bool	routine_init(t_table *table, t_philo *this_philo)
{
	table->phi_counter += 1;
	this_philo->num = table->phi_counter;
	this_philo->eat_count = 0;
	if (this_philo->num == 1)
		this_philo->right = &table->forks[table->n_phi - 1];
	else
		this_philo->right = &table->forks[table->phi_counter - 2];
	this_philo->left = &table->forks[table->phi_counter - 1];
	pthread_mutex_unlock(&table->print);
	pthread_mutex_lock(&table->util);
	pthread_mutex_unlock(&table->util);
	if (this_philo->num % 2)
		my_sleep(8);
	return (0);
}

static _Bool	eat_enough(size_t eat_count, ssize_t eat_times)
{
	if (eat_times == -1)
		return (0);
	if ((size_t)eat_times > eat_count)
		return (0);
	return (1);
}
