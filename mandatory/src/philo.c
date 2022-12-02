/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:08:24 by bruno             #+#    #+#             */
/*   Updated: 2022/12/02 23:51:23 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc.philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (philo_init(argc, argv, &table))
		return (write(2, "Error\n", 6));
}

static _Bool	philo_init(int argc, char **argv, t_table *table)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (parse_init(argv))
		return (1);
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
}

static _Bool	parse_init(char **argv)
{
	if (ft_strlen(argv[1]) > 5 || ft_strlen(argv[2]) > 5
		|| ft_strlen(argv[3]) > 5 || ft_strlen(argv[4]) > 5)
	return (1);
	while (*argv[1] && (*argv[1] >= '0' || *argv[1] <= '9'))
		argv[1] += 1;
	while (*argv[2] && (*argv[2] >= '0' || *argv[2] <= '9'))
		argv[2] += 1;
	while (*argv[3] && (*argv[3] >= '0' || *argv[3] <= '9'))
		argv[3] += 1;
	while (*argv[4] && (*argv[4] >= '0' || *argv[4] <= '9'))
		argv[4] += 1;
	if (argv[5])
	{
		if (ft_strlen(*argv[5]) > 5)
		while (*argv[5] && (*argv[5] >= '0' || *argv[5] <= '9'))
			argv[5] += 1;
		if (*argv[5])
			return (0);
	}
	if (*argv[1] || *argv[2] || *argv[3] || *argv[4])
		return (1);
	return (0);
}