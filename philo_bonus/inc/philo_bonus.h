/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:08:59 by bruno             #+#    #+#             */
/*   Updated: 2022/12/06 17:18:24 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stddef.h>

# include <stdlib.h>

# include <stdio.h>

# include <unistd.h>

# include "philo_struct_bonus.h"

//	----- philo_bonus.c
void		kill_all(t_table *table);

//	----- parsing_bonus.c
int			philo_init(int argc, char **argv, t_table *table);

//	----- simulation_bonus.c
int			philo_start(t_table *table);

//	----- utils_bonus.c
void		printer(char *to_print, t_table *table,
				t_philo *phi, long long time);
long long	get_time(void);
void		my_sleep(long long sleep_time);

//	----- child_actions_bonus.c
void		pick_fork(t_table *table, t_philo *this_philo);
void		eating(t_table *table, t_philo *this_philo);
void		sleeping(t_table *table, t_philo *this_philo);

//	----- libft_bonus.c
int			ft_strlen(const char *s);
void		*ft_calloc(size_t nmemb, size_t size);

#endif