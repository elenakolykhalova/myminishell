/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinigo <jinigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:20:30 by jinigo            #+#    #+#             */
/*   Updated: 2021/04/13 16:23:31 by jinigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	cycle(char *output, char const *s, unsigned int start, size_t len)
{
	unsigned int	i;

	i = 0;
	while (i < len)
	{
		output[i] = s[start + i];
		i++;
	}
	output[i] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	s_len;
	char			*output;

	if (!s)
		return (NULL);
	s_len = ft_strlen((char *)s);
	if (s_len < start)
	{
		output = malloc(sizeof(char) * 1);
		if (!output)
			return (NULL);
		output[0] = '\0';
		return (output);
	}
	output = malloc(sizeof(char) * (len + 1));
	if (!output)
		return (NULL);
	cycle(output, s, start, len);
	return (output);
}
