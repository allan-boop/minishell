/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_args_p.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 10:12:11 by gdoumer           #+#    #+#             */
/*   Updated: 2024/01/23 14:28:16 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

static int	ft_len_puthex(unsigned long long adress)
{
	int	len;

	len = 0;
	while (adress)
	{
		len++;
		adress = adress / 16;
	}
	return (len);
}

static void	ft_puthex(unsigned long long adress)
{
	if (adress >= 16)
	{
		ft_puthex(adress / 16);
		ft_puthex(adress % 16);
	}
	else
	{
		if (adress < 10)
			ft_putchar_fd((adress + '0'), 1);
		else
			ft_putchar_fd((adress - 10 + 'a'), 1);
	}
}

int	ft_write_args_p(unsigned long long adress)
{
	int	len_adress;

	len_adress = 0;
	len_adress += write(1, "0x", 2);
	if (adress == 0)
	{
		ft_putchar_fd('0', 1);
		len_adress++;
	}
	else
	{
		ft_puthex(adress);
		len_adress += ft_len_puthex(adress);
	}
	return (len_adress);
}
