/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinigo <jinigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 14:19:51 by jinigo            #+#    #+#             */
/*   Updated: 2021/04/13 16:05:25 by jinigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	find_start(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '\f' || str[i] == '\t' || str[i] == ' '
			|| str[i] == '\n' || str[i] == '\r' || str[i] == '\v'))
	{
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;
	int	j;

	res = 0;
	sign = 1;
	j = find_start(str);
	if (str[j] == '-' || str[j] == '+')
	{
		if (str[j] == '-')
		{
			sign = -1;
		}
		j++;
	}
	while (str[j] && str[j] >= '0' && str[j] <= '9')
	{
		res = res * 10 + str[j] - '0';
		j++;
	}
	res = res * sign;
	return (res);
}
