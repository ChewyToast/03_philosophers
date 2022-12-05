/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:08:24 by bruno             #+#    #+#             */
/*   Updated: 2022/12/03 20:29:02 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int		clean_philo(t_table *table);
static _Bool	destroy_mutex(t_table *table);

int	main(int argc, char **argv)
{
	t_table	table;
	int		tmp;

	tmp = philo_init(argc, argv, &table);
	if (tmp == 18)
		return (1);
	else if (tmp)
		return (clean_philo(&table));
	if (philo_start(&table))
		return (clean_philo(&table));
	clean_philo(&table);
	return (0);
}

static int	clean_philo(t_table *table)
{
}

static _Bool	destroy_mutex(t_table *table)
{
}
