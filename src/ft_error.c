/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:32:51 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 14:32:53 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_nb_args(int argc)
{
	if (argc != 1)
	{
		ft_printf(MANY_ARGS);
		exit (1);
	}
}

int	syntax_error(char *msg)
{
	ft_printf("%s", msg);
	return (1);
}

int	ft_check_quote(char *line)
{
	char	quote;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			quote = line[i];
			i++;
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] != quote)
				return (syntax_error(QUOTE_FAIL));
		}
		i++;
	}
	return (0);
}

int	ft_error_parsing(t_list_struct	*list)
{
	if (list && list->is_operator == true)
		return (syntax_error(OPERATOR_FAIL));
	while (list)
	{
		if (list->is_redir == true)
		{
			if (list->next == NULL)
				return (syntax_error(REDIR_FAIL));
			else if (list->next->is_redir == true
				|| list->next->is_operator == true)
				return (syntax_error(REDIR_FAIL));
		}
		if (list->is_operator == true)
		{
			if (list->next == NULL)
				return (syntax_error(OPERATOR_FAIL));
			else if (list->next->is_operator == true)
				return (syntax_error(OPERATOR_FAIL));
		}
		list = list->next;
	}
	return (0);
}

bool	ft_error(char *cmd, char *msg, int ret)
{
	ft_printf("%s: %s\n", cmd, msg);
	return (ret);
}
