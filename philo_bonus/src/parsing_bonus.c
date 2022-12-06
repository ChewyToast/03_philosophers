/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 09:47:42 by bruno             #+#    #+#             */
/*   Updated: 2022/12/06 19:11:33 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static _Bool	time_startup(t_table *table, char **argv, int argc);
static _Bool	sem_initer(t_table *table);
static _Bool	parse_init(char **argv);

int	philo_init(int argc, char **argv, t_table *table)
{
	if (argc < 5 || argc > 6)
		return (write(2, "Invalid arguments\n", 18));
	if (parse_init(argv))
		return (write(2, "Invalid Arguments\n", 18));
	table->n_phi = atoi(argv[1]);
	table->pid = ft_calloc(sizeof(pid_t), table->n_phi);
	table->time = ft_calloc(sizeof(t_time), 1);
	if (!(table->pid) || !(table->time))
		return (write(2, "philo: Memory alloc error\n", 26));
	time_startup(table, argv, argc);
	if (sem_initer(table))
		return (write(2, "philo: sem_open error\n", 22));
	return (0);
}

static _Bool	time_startup(t_table *table, char **argv, int argc)
{
	table->end = 0;
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

static _Bool	sem_initer(t_table *table)
{
	sem_unlink("sem_forks");
	sem_unlink("sem_util");
	sem_unlink("sem_print");
	sem_unlink("sem_dead");
	table->forks = sem_open("sem_forks", O_CREAT | O_EXCL, 0644, table->n_phi);
	table->util = sem_open("sem_util", O_CREAT | O_EXCL, 0644, 1);
	table->print = sem_open("sem_print", O_CREAT | O_EXCL, 0644, 1);
	table->dead = sem_open("sem_dead", O_CREAT | O_EXCL, 0644, 1);
	if (table->forks == SEM_FAILED
		|| table->util == SEM_FAILED
		|| table->print == SEM_FAILED
		|| table->dead == SEM_FAILED)
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
