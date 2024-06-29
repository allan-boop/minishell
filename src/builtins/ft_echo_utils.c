/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:30:31 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 14:30:33 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_in_quote(char *line, char *str)
{
	int		i;
	int		quote_count;

	quote_count = 0;
	i = 0;
	while (line[i] != str[0])
	{
		if (line[i] == 3)
			quote_count++;
		i++;
	}
	if (quote_count % 2 == 0)
		return (0);
	return (1);
}
