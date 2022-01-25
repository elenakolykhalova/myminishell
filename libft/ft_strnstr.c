/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:53:21 by jinigo            #+#    #+#             */
/*   Updated: 2021/07/22 10:55:51 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *nee, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	if (nee[0] == '\0')
		return ((char *)hay);
	i = 0;
	while (hay[i] && i < len)
	{
		j = 0;
		if (hay[i] == nee[j])
		{
			while (i + j < len && hay[i + j] == nee[j])
			{
				j++;
				if (!nee[j])
					return ((char *)&hay[i]);
			}
		}
		i++;
	}
	return (0);
}
