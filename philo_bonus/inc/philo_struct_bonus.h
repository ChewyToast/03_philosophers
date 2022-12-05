/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:18:15 by bruno             #+#    #+#             */
/*   Updated: 2022/12/03 22:05:17 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

# include <pthread.h>

typedef struct s_time
{
	long long	tstart;
	long long	tdie;
	long long	teat;
	long long	tsleep;
	ssize_t		eat_times;
}	t_time;

typedef struct s_table
{
	size_t	n_phi;
	size_t	phi_counter;
	char	**argv;
	_Bool	dead;
	t_time	*time;
	sem_t	*util;
	sem_t	*print;
	sem_t	**forks;
}	t_table;

# define TAF "has taken a fork"
# define IEA "is eating"
# define ISS "is sleeping"
# define IST "is thinking"

#endif