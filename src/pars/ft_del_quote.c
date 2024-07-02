/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:32:02 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 14:32:03 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_dell_all_quote_export(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			while (line[i])
			{
				line[i] = line[i + 1];
				i++;
			}
			line[i] = '\0';
			i = 0;
		}
		i++;
	}
}

void	ft_dell_simple_quote_export(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39)
		{
			while (line[i])
			{
				line[i] = line[i + 1];
				i++;
			}
			line[i] = '\0';
			i = 0;
		}
		i++;
	}
}

void	ft_dell_double_quote_export(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39)
		{
			while (line[i])
			{
				line[i] = line[i + 1];
				i++;
			}
			line[i] = '\0';
			i = 0;
		}
		i++;
	}
}
