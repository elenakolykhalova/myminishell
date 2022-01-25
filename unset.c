/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 14:03:26 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/21 16:04:24 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_var(char **array)
{
	char	**variable;
	int		i;
	int		j;

	i = 0;
	while (array[i])
		i++;
	variable = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (array[++i])
		variable[i] = ft_strdup(array[i]);
	variable[i] = NULL;
	i = 0;
	while (variable[i])
	{
		j = 0;
		while (variable[i][j] && variable[i][j] != '=')
			j++;
		variable[i][j] = '\0';
		i++;
	}
	return (variable);
}

int	first_el(char *arguments)
{
	if (ft_isalpha(arguments[0]) || arguments[0] == '_')
		return (0);
	return (1);
}

char	**turnoff(char **array, char **arguments, char **variable)
{
	int		i;
	int		j;
	int		count;
	char	**tmp;

	tmp = NULL;
	j = 0;
	while (variable[j])
		j++;
	count = 0;
	i = 1;
	while (arguments[i])
	{
		if (!first_el(arguments[i]))
			count = turnoff_del_arg(array, arguments, variable, i);
		i++;
	}
	tmp = (char **)malloc(sizeof(char *) * (j - count + 1));
	if (!tmp)
		return (NULL);
	tmp[j - count] = NULL;
	cp_tmp(array, tmp);
	return (tmp);
}

char	**record_list(char **array, char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
		i++;
	array = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (tmp[++i])
		array[i] = ft_strdup(tmp[i]);
	array[i] = NULL;
	return (array);
}

int	ft_unset(t_shell *g_mini)
{
	int		i;

	i = 0;
	g_mini->ft_errno = 0;
	while (g_mini->split_buf[++i])
	{
		if (first_el(g_mini->split_buf[i]))
		{
			printf("Prompt: unset: '%s': not a valid identifier\n",
				g_mini->split_buf[i]);
			g_mini->ft_errno = 1;
		}
	}
	g_mini->str_exp = unset_array(g_mini->str_exp, g_mini);
	g_mini->str_env = unset_array(g_mini->str_env, g_mini);
	return (0);
}
