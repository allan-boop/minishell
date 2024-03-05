/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:57:37 by gdoumer           #+#    #+#             */
/*   Updated: 2024/01/23 14:27:52 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

static int	is_in_set(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*end;
	char	*result;
	size_t	len;

	if (!s1 || !set)
		return (0);
	while (*s1 && is_in_set(*s1, set))
		s1++;
	end = (char *)(s1 + ft_strlen(s1) - 1);
	while (end > s1 && is_in_set(*end, set))
		end--;
	len = end - s1 + 1;
	result = malloc(len + 1);
	if (!result)
		return (0);
	ft_strlcpy(result, s1, len + 1);
	result[len] = '\0';
	return (result);
}
