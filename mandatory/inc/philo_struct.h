/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:18:15 by bruno             #+#    #+#             */
/*   Updated: 2022/12/02 23:31:44 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

typedef struct s_time
{
	long long	tstart;
	int			tdie;
	int			teat;
	int			tsleep;
	int			tthink;
	int			eat_count;
}

typedef struct s_philo
{
	int	num;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	pthread_mutex_t	*print;
}	t_philo;

typedef struct s_table
{
	int				n_forks;
	t_phi			*philo;
	_Bool			dead;
	pthread_mutex_t	*forks;

}	t_table;

#endif