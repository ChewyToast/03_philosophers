/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:18:15 by bruno             #+#    #+#             */
/*   Updated: 2022/12/06 17:17:07 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_BONUS_H
# define PHILO_STRUCT_BONUS_H

# include <pthread.h>

# include <semaphore.h>

# include <signal.h>

typedef struct s_philo
{
	size_t		num;
	long long	tstart;
	long long	last_eat;
	long long	eat_count;
	sem_t		*right;
	sem_t		*left;
}	t_philo;

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
	size_t	end;
	pid_t	*pid;
	size_t	phi_counter;
	t_philo	*this_philo;
	char	**argv;
	t_time	*time;
	sem_t	*util;
	sem_t	*dead;
	sem_t	*print;
	sem_t	*forks;
}	t_table;

# define TAF "has taken a fork"
# define IEA "is eating"
# define ISS "is sleeping"
# define IST "is thinking"

#endif