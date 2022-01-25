/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 10:40:11 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/20 14:58:28 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**increase_array(char **array, char *insert)
{
	char	**tmp;
	int		j;

	j = 0;
	while (array[j])
		j++;
	tmp = (char **)malloc(sizeof(char *) * (j + 2));
	j = 0;
	while (array[j])
	{
		tmp[j] = ft_strdup(array[j]);
		j++;
	}
	tmp[j] = ft_strdup(insert);
	tmp[j + 1] = NULL;
	free_list(array);
	return (tmp);
}

char	**export_env_or_exp(t_shell *g_mini, char **array, int i)
{
	char	**tmp;

	tmp = increase_array(array, g_mini->split_buf[i]);
	array = cp_ar(tmp);
	free_list(tmp);
	return (array);
}

void	export_twin(t_shell *g_mini, int i)
{
	char	**tmp;

	if (ft_strchr(g_mini->split_buf[i], '='))
	{
		if (check_twin(g_mini->str_env, g_mini->split_buf[i], '='))
			g_mini->str_env = export_env_or_exp(g_mini, g_mini->str_env, i);
		if (check_twin(g_mini->str_exp, g_mini->split_buf[i], '='))
			g_mini->str_exp = export_env_or_exp(g_mini, g_mini->str_exp, i);
	}
	else
	{
		if (check_twin(g_mini->str_exp, g_mini->split_buf[i], '\0'))
		{
			tmp = increase_array(g_mini->str_exp, g_mini->split_buf[i]);
			g_mini->str_exp = cp_ar(tmp);
			free_list(tmp);
		}
	}
}

void	export_sort(t_shell *g_mini)
{
	char	**str_sort;

	str_sort = sort_ar(g_mini);
	print_array(str_sort);
	free_list(str_sort);
}

int	ft_export(t_shell *g_mini)
{
	int		i;

	g_mini->ft_errno = 0;
	if (g_mini->arg_buf > 1)
	{
		i = 1;
		while (g_mini->split_buf[i])
		{
			if (!first_el(g_mini->split_buf[i]))
				export_twin(g_mini, i);
			else
			{
				printf("Prompt: export: '%s': not a valid identifier\n",
					g_mini->split_buf[i]);
				g_mini->ft_errno = 1;
			}
			i++;
		}
	}
	else
		export_sort(g_mini);
	return (0);
}
