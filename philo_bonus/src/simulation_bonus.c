/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 09:48:52 by bruno             #+#    #+#             */
/*   Updated: 2022/12/06 18:29:03 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static _Bool	eat_enough(size_t eat_count, ssize_t eat_times);
static void		philo_routine(t_table *table, size_t count);
static void		thread_of_fork(t_table *table);
static void		father_wait(t_table *table);

int	philo_start(t_table *table)
{
	pthread_t	tmp;

	tmp = 0;
	sem_wait(table->util);
	while (table->phi_counter < table->n_phi)
	{
		table->pid[table->phi_counter] = fork();
		if (table->pid[table->phi_counter] < 0)
			return (write(2, "philo: error creating fork\n", 27));
		if (!table->pid[table->phi_counter])
			philo_routine(table, table->phi_counter);
		table->phi_counter++;
	}
	my_sleep(128);
	sem_post(table->util);
	father_wait(table);
	my_sleep(510);
	return (0);
}

static void	philo_routine(t_table *table, size_t count)
{
	pthread_t	tmp;
	t_philo		this_philo;

	this_philo.num = count + 1;
	this_philo.eat_count = 0;
	this_philo.last_eat = 0;
	sem_wait(table->util);
	sem_post(table->util);
	this_philo.tstart = get_time();
	this_philo.last_eat = this_philo.tstart;
	table->this_philo = &this_philo;
	if (pthread_create(&tmp, NULL, (void *)&thread_of_fork, (void *)table))
		exit (write(2, "philo: Error creating thread\n", 29));
	while (1)
	{
		sem_wait(table->print);
		sem_post(table->print);
		pick_fork(table, &this_philo);
		eating(table, &this_philo);
		if (eat_enough(this_philo.eat_count, table->time->eat_times))
			break ;
		sleeping(table, &this_philo);
		printer(IST, table, &this_philo, get_time() - this_philo.tstart);
	}
	exit (0);
}

static void	thread_of_fork(t_table *table)
{
	long long	time;

	while (1)
	{
		if (table->this_philo->eat_count == 0)
		{
			if (table->time->tdie <= get_time() - table->this_philo->tstart)
			{
				time = get_time() - table->this_philo->tstart;
				sem_wait(table->print);
				printf("%lld %zu died\n", time, table->this_philo->num);
				exit (1);
			}
		}
		else
		{
			if (table->time->tdie <= table->this_philo->last_eat - get_time())
			{
				time = table->this_philo->last_eat - get_time();
				sem_wait(table->print);
				printf("%lld %zu died\n", time, table->this_philo->num);
				exit (1);
			}
		}
	}
}

static	void	father_wait(t_table *table)
{
	int	status;

	status = 0;
	while (table->end < table->n_phi)
	{
		waitpid(-1, &status, WUNTRACED);
		if (WEXITSTATUS(status) == 1)
			break ;
		if (WEXITSTATUS(status) == 0)
		{
			table->end++;
		}
	}
	kill_all(table);
}

static _Bool	eat_enough(size_t eat_count, ssize_t eat_times)
{
	if (eat_times == -1)
		return (0);
	if ((size_t)eat_times > eat_count)
		return (0);
	return (1);
}
