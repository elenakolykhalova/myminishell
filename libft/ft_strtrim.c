/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinigo <jinigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:55:00 by jinigo            #+#    #+#             */
/*   Updated: 2021/04/13 16:15:56 by jinigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*tmp;
	int		left;
	int		right;

	i = 0;
	left = 0;
	if (!s1 || !set)
		return ((char *)s1);
	right = ft_strlen(s1) - 1;
	while (is_in_set(set, s1[left]) == 1)
		left++;
	while (left < right && is_in_set(set, s1[right]) == 1)
		right--;
	tmp = (char *)ft_calloc((right - left + 2) * sizeof(char), 1);
	if (!tmp)
		return (0);
	while (left <= right)
	{
		tmp[i] = s1[left];
		i++;
		left++;
	}
	return (tmp);
}
