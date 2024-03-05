/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:15:20 by gdoumer           #+#    #+#             */
/*   Updated: 2024/01/23 14:26:41 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

int	ft_sort(const char *str, int *i, va_list args)
{
	(*i)++;
	if (str[*i] == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	else if (str[*i] == 'c')
		return (ft_write_args_c(args));
	else if (str[*i] == 'd' || str[*i] == 'i')
		return (ft_write_args_d(args));
	else if (str[*i] == 'u')
		return (ft_write_args_u(args));
	else if (str[*i] == 'x')
		return (ft_write_args_x(va_arg(args, int), 'a'));
	else if (str[*i] == 'X')
		return (ft_write_args_x(va_arg(args, int), 'A'));
	else if (str[*i] == 'p')
		return (ft_write_args_p(va_arg(args, unsigned long long)));
	else if (str[*i] == '%')
		return (ft_write_args_percent('%'));
	return (-1);
}

int	verif_char(const char *str, int *i, int h, va_list args)
{
	int	l;
	int	z;

	l = 0;
	z = 0;
	while (str[*i])
	{
		if (str[*i] == '%')
		{
			z++;
			h = ft_sort(str, i, args);
			if (h == -1)
				return (-1);
			l += h;
		}
		else
		{
			h = ft_putchar_fd(str[*i], 1);
			if (h == -1)
				return (-1);
			l += h;
		}
		(*i)++;
	}
	return ((*i - (z * 2)) + l);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		h;
	va_list	args;

	i = 0;
	h = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	i = verif_char(format, &i, h, args);
	va_end(args);
	return (i);
}
