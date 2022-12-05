/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 08:52:54 by bruno             #+#    #+#             */
/*   Updated: 2022/12/03 19:33:25 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*mall;

	if ((nmemb * size) > 0xffffffff)
		return (NULL);
	mall = malloc (size * nmemb);
	if (mall == NULL)
		return (NULL);
	size *= nmemb;
	while (size--)
		mall[size] = 0;
	return (mall);
}
