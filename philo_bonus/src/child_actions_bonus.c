/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_actions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 01:45:49 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/07 05:27:58 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	pick_fork(t_table *table, t_philo *this_philo)
{
	sem_wait(table->forks);
	printer(TAF, table, this_philo, 0);
	sem_wait(table->forks);
	printer(TAF, table, this_philo, 0);
}

void	eating(t_table *table, t_philo *this_philo)
{
	printer(IEA, table, this_philo, 1);
	this_philo->eat_count += 1;
	my_sleep(table->time->teat);
	sem_post(table->forks);
	sem_post(table->forks);
}

void	sleeping(t_table *table, t_philo *this_philo)
{
	printer(ISS, table, this_philo, 0);
	my_sleep(table->time->tsleep);
}
