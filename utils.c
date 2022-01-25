/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 11:03:55 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/21 18:59:33 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cp_ar(char **array)
{
	int		i;
	char	**copy;

	copy = NULL;
	i = 0;
	while (array[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (array[i])
	{
		copy[i] = ft_strdup(array[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	cp_tmp(char **array, char **tmp)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (array[i])
	{
		if (array[i][0] == '1')
			count++;
		else
			tmp[i - count] = ft_strdup(array[i]);
		i++;
	}
	tmp[i - count] = NULL;
}

char	**unset_array(char **array, t_shell *g_mini)
{
	char	**variable;
	char	**tmp;
	char	**tmp2;

	tmp = NULL;
	variable = create_var(array);
	tmp = turnoff(array, g_mini->split_buf, variable);
	tmp2 = array;
	array = cp_ar(tmp);
	free_list(variable);
	free_list(tmp);
	free_list(tmp2);
	return (array);
}

int	turnoff_del_arg(char **array, char **arguments, char **variable, int i)
{
	int		j;
	int		count;

	j = 0;
	count = 0;
	while (variable[j])
	{
		if ((ft_strnstr(arguments[i], variable[j],
					ft_strlen(variable[j]))))
		{
			count++;
			free(array[j]);
			array[j] = ft_strdup("1");
		}
		j++;
	}
	return (count);
}
