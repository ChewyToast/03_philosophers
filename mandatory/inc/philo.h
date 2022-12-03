/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:08:59 by bruno             #+#    #+#             */
/*   Updated: 2022/12/03 12:47:13 by bruno            ###   ########.fr       */
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
int		philo_init(int argc, char **argv, t_table *table);

//	----- simulation.c
_Bool	philo_start(t_table *table);

//	----- libft.c
int		ft_strlen(const char *s);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

#endif