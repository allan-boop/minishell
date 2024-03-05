/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_y.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:55:00 by gdoumer           #+#    #+#             */
/*   Updated: 2024/03/05 17:55:14 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_len_y(int fd)
{
	size_t	len;
	char	*s;

	if (fd == -1)
		return (0);
	len = 0;
	s = get_next_line(fd);
	while (s)
	{
		s = get_next_line(fd);
		free(s);
		len++;
	}
	close (fd);
	return (len);
}
