/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:08:59 by bruno             #+#    #+#             */
/*   Updated: 2022/12/03 22:08:08 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>

# include <stdlib.h>

# include <stdio.h>

# include <pthread.h>

# include <unistd.h>

# include "philo_struct.h"

//	----- parsing.c
int			philo_init(int argc, char **argv, t_table *table);

//	----- simulation.c
_Bool		philo_start(t_table *table);

//	----- utils.c
long long	get_time(void);
void		my_sleep(int32_t sleep_time);
void		printer(char *to_print, t_table *table, t_philo *phi, long long time);

//	----- libft.c
int			ft_strlen(const char *s);
void		*ft_calloc(size_t nmemb, size_t size);

#endif