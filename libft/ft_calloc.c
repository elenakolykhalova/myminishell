/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinigo <jinigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:20:54 by jinigo            #+#    #+#             */
/*   Updated: 2021/04/13 16:07:49 by jinigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*dst;
	size_t	s_s;
	int		i;

	s_s = count * size;
	dst = malloc(s_s);
	if (!dst)
	{
		return (NULL);
	}
	i = 0;
	while (s_s-- > 0)
	{
		dst[i] = 0;
		i++;
	}
	return ((void *)dst);
}
