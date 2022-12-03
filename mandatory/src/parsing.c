/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 09:47:42 by bruno             #+#    #+#             */
/*   Updated: 2022/12/03 14:45:06 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static _Bool	parse_init(char **argv);
static _Bool	mutex_init(t_table *table);

int	philo_init(int argc, char **argv, t_table *table)
{
	if (argc < 5 || argc > 6)
		return (write(2, "Invalid arguments\n", 18));
	if (parse_init(argv))
		return (write(2, "Invalid Arguments\n", 18));
	table->dead = 0;
	table->argv = argv;
	table->n_phi = ft_atoi(argv[1]);
	table->phi_counter = 0;
	// printf("n_phi: |%ld| string: ->%s<-", table->n_phi, argv[1]);
	table->philo = ft_calloc(sizeof(t_philo), table->n_phi);
	table->time = ft_calloc(sizeof(t_time), 1);
	table->forks = ft_calloc(sizeof(pthread_mutex_t), table->n_phi);
	if (!(table->philo) || !(table->time) || !(table->forks))
		return (write(2, "Memory alloc error\n", 19));
	if (mutex_init(table))
	{
		printf("mutex init error\n");
		return (1);
	}
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
			|| argv[count][tmp] <= '9'))
			tmp++;
		if (argv[count][tmp] || tmp > 5)
			return (1);
		count++;
	}
	return (0);
}
