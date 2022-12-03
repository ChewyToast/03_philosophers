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

typedef struct s_philo
{
	size_t			num;
	size_t			eat_count;
	long long		last_eat;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
}	t_philo;

typedef struct s_table
{
	size_t			n_phi;
	size_t			phi_counter;
	char			**argv;
	t_philo			*philo;
	_Bool			dead;
	t_time			*time;
	pthread_mutex_t	util;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
}	t_table;

#endif