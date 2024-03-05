/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_args_x.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:25:31 by gdoumer           #+#    #+#             */
/*   Updated: 2024/01/23 14:28:28 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

static int	ft_len_puthex(unsigned int args)
{
	int	len;

	len = 0;
	while (args)
	{
		len++;
		args = args / 16;
	}
	return (len);
}

static void	ft_puthex(unsigned int args, char cha)
{
	if (args >= 16)
	{
		ft_puthex((args / 16), cha);
		ft_puthex((args % 16), cha);
	}
	else
	{
		if (args < 10)
			ft_putchar_fd((args + '0'), 1);
		else
			ft_putchar_fd((args - 10 + cha), 1);
	}
}

int	ft_write_args_x(int args, char cha)
{
	if (args == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	ft_puthex(args, cha);
	return (ft_len_puthex(args));
}
