/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 09:47:42 by bruno             #+#    #+#             */
/*   Updated: 2022/12/03 22:06:38 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static _Bool	parse_init(char **argv);
static _Bool	mutex_init(t_table *table);
static _Bool	time_startup(t_table *table, char **argv, int argc);

int	philo_init(int argc, char **argv, t_table *table)
{
	if (argc < 5 || argc > 6)
		return (write(2, "Invalid arguments\n", 18));
	if (parse_init(argv))
		return (write(2, "Invalid Arguments\n", 18));
	table->n_phi = atoi(argv[1]);
	table->philo = ft_calloc(sizeof(t_philo), table->n_phi);
	table->time = ft_calloc(sizeof(t_time), 1);
	table->forks = ft_calloc(sizeof(pthread_mutex_t), table->n_phi);
	if (!(table->philo) || !(table->time) || !(table->forks))
		return (write(2, "Memory alloc error\n", 19));
	time_startup(table, argv, argc);
	if (mutex_init(table))
		return (write(2, "mutex init error\n", 17));
	return (0);
}

static _Bool	time_startup(t_table *table, char **argv, int argc)
{
	table->dead = 0;
	table->argv = argv;
	table->phi_counter = 0;
	table->time->tstart = 0;
	table->time->tdie = atoi(argv[2]);
	table->time->teat = atoi(argv[3]);
	table->time->tsleep = atoi(argv[4]);
	if (argc == 6)
		table->time->eat_times = atoi(argv[5]);
	else
		table->time->eat_times = -1;
	return (0);
}

static _Bool	mutex_init(t_table *table)
{
	size_t	count;

	count = 0;
	while (count < table->n_phi)
	{
		if (pthread_mutex_init(&table->forks[count], NULL))
			return (1);
		count++;
	}
	if (pthread_mutex_init(&table->util, NULL))
		return (1);
	if (pthread_mutex_init(&table->print, NULL))
		return (1);
	return (0);
}

static _Bool	parse_init(char **argv)
{
	size_t	count;
	size_t	tmp;

	count = 1;
	tmp = 0;
	while (argv[count])
	{
		tmp = 0;
		while (argv[count][tmp] && (argv[count][tmp] >= '0'
			&& argv[count][tmp] <= '9'))
			tmp++;
		if (argv[count][tmp] || tmp > 5)
			return (1);
		count++;
	}
	return (0);
}
