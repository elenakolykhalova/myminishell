/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 14:50:58 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/20 15:15:04 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sort_malloc(t_shell *g_mini)
{
	char	**str_sort;
	int		i;

	i = 0;
	while (g_mini->str_exp[i])
		i++;
	str_sort = (char **)malloc(sizeof(char *) * (i + 2));
	if (!str_sort)
		return (NULL);
	i = -1;
	while (g_mini->str_exp[++i])
		str_sort[i] = ft_strdup(g_mini->str_exp[i]);
	str_sort[i] = NULL;
	return (str_sort);
}

char	**sort_ar(t_shell *g_mini)
{
	char	**str_sort;
	char	*tmp;
	int		i;

	str_sort = sort_malloc(g_mini);
	i = 1;
	while (str_sort[i])
	{
		if (i > 0 && ((ft_strncmp(str_sort[i - 1], str_sort[i],
						ft_strlen(str_sort[i]))) > 0))
		{
			tmp = str_sort[i];
			str_sort[i] = str_sort[i - 1];
			str_sort[i - 1] = tmp;
			i--;
		}
		else
			i++;
	}
	return (str_sort);
}

void	print_array(char **str_sort)
{
	int	i;
	int	j;

	i = 0;
	while (str_sort[i])
	{
		printf("declare -x ");
		j = 0;
		if (ft_strchr(str_sort[i], '='))
		{
			while (str_sort[i][j])
			{
				if (str_sort[i][j] == '=')
					printf("%c\"", str_sort[i][j]);
				else
					printf("%c", str_sort[i][j]);
				j++;
			}
			printf("\"\n");
		}
		else
			printf("%s\n", str_sort[i]);
		i++;
	}
}

int	check_twin(char **array, char *str, char c)
{
	int	j;
	int	count;

	count = 0;
	while (str[count] != c)
	{
		count++;
	}
	j = 0;
	while (array[j])
	{
		if (!ft_strncmp(array[j], str, count))
		{
			free(array[j]);
			array[j] = ft_strdup(str);
			return (0);
		}
		j++;
	}
	return (1);
}
