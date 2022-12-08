/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:29:23 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/08 02:59:41 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include "../inc/philo_bonus.h"

void	printer(char *to_print, t_table *table, t_philo *phi, int mode)
{
	sem_wait(table->print);
	if (mode)
		phi->last_eat = get_time();
	(void)mode;
	if (printf("| %.4lld | %.3zu %s\n", get_time() - table->time->tstart,
			phi->num, to_print) < 0)
	{
		write(2, "printf: Bad file descriptor\n", 28);
		sem_wait(table->print);
		kill(table->pid[table->phi_counter], SIGTERM);
	}
	sem_post(table->print);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	my_sleep(long long sleep_time)
{
	sleep_time += get_time();
	while (get_time() <= sleep_time)
		usleep(600);
}

void	wait_until(long long wait_time)
{
	while (get_time() < wait_time)
		usleep(100);
}
