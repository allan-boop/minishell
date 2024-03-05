/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:31:18 by gdoumer           #+#    #+#             */
/*   Updated: 2024/02/02 21:52:28 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

int	ft_atoi_base(char *nb)
{
	int		i;
	int		j;
	int		nb_base;
	char	*base;

	if (!nb)
		return (0);
	i = 0;
	j = 0;
	nb_base = 0;
	base = "0123456789abcdef";
	while (nb[i])
	{
		while (base[j] && base[j] != nb[i])
			j++;
		if (base[j] == nb[i])
			nb_base = nb_base * 16 + j;
		i++;
		j = 0;
	}
	return (nb_base);
}
