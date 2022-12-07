/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:29:23 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/07 02:54:51 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	printer(char *to_print, t_table *table, t_philo *phi)
{
	pthread_mutex_lock(&table->print);
	if (!table->dead)
	{
		if (printf("%lld %zu %s\n", get_time() - table->time->tstart,
				phi->num, to_print) < 0)
		{
			write(2, "printf: Bad file descriptor\n", 28);
			table->dead = 1;
		}
	}
	pthread_mutex_unlock(&table->print);
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
		usleep(100);
}

void	set_dead(t_table *table, ssize_t count)
{
	pthread_mutex_lock(&table->print);
	if (printf("%lld %zu %s\n", get_time() - table->time->tstart,
			count + 1, "died") < 0)
		write(2, "printf: Bad file descriptor\n", 28);
	table->dead = 1;
	pthread_mutex_unlock(&table->print);
}
