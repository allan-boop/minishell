/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_args_u.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:03:37 by gdoumer           #+#    #+#             */
/*   Updated: 2024/01/23 14:28:24 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

static int	nblen(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*ft_unsigned_itoa(unsigned int n)
{
	char	*result;
	int		len;

	len = 0;
	len = nblen(n);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (n == 0)
		result[0] = '0';
	while (n)
	{
		result[--len] = (n % 10) + '0';
		n = n / 10;
	}
	return (result);
}

int	ft_write_args_u(va_list args)
{
	char	*nb;
	int		len;

	nb = ft_unsigned_itoa(va_arg(args, unsigned int));
	len = ft_strlen(nb);
	ft_putstr_fd(nb, 1);
	if (!nb)
	{
		free(nb);
		return (-1);
	}
	free(nb);
	return (len);
}
