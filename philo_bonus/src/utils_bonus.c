/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:29:23 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/06 04:15:37 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

#include "../inc/philo_bonus.h"

void	printer(char *to_print, t_table *table, t_philo *phi, long long time)
{
	sem_wait(table->print);
	if (printf("%lld %zu %s\n", time, phi->num, to_print) < 0)
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
	while (get_time() < sleep_time)
		usleep(64);
}

void	killer_thread(t_table *table)
{
	sem_wait(table->dead);
	kill_all(table);
	sem_post(table->dead);
}
