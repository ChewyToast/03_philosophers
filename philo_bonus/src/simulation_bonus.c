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
static _Bool	eat_enough(size_t eat_count, ssize_t eat_times);
static _Bool	routine_init(t_table *table, t_philo *this_philo);
static void		philo_start_iter(t_table *table);

int	philo_start(t_table *table)
{
	pid_t	pid;
	size_t	count;

	count = 0;
	sem_wait(table->util);
	while (count < table->n_phi)
	{
		s
	}
}

static void	philo_start_iter(t_table *table)
{
}

static void	philo_routine(t_table *table)
{
}

static _Bool	routine_init(t_table *table, t_philo *this_philo)
{
}

static _Bool	eat_enough(size_t eat_count, ssize_t eat_times)
{
}
