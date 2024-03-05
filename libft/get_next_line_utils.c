/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:39:26 by gdoumer           #+#    #+#             */
/*   Updated: 2024/01/23 14:28:33 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	all_size;

	if (!s1 || !s2)
	{
		if (s1)
			return (ft_strdup_gnl(s1));
		else if (s2)
			return (ft_strdup_gnl(""));
		return (NULL);
	}
	all_size = ft_strlen_gnl(s2) + ft_strlen_gnl(s1);
	str = (char *)malloc((all_size + 1) * sizeof(char));
	if (!str)
		return (str);
	i = 0;
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	int		j;

	if (!s)
		return (NULL);
	if (start >= ft_strlen_gnl(s))
		return (ft_strdup_gnl(""));
	if (len > ft_strlen_gnl(s) - start)
		len = ft_strlen_gnl(s) - start;
	i = 0;
	j = start;
	ptr = malloc(len + 1);
	if (!ptr)
		return (0);
	while (s[j] != '\0' && i < len)
	{
		ptr[i] = s[j];
		j++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	ft_bzero_gnl(void *s, size_t n)
{
	unsigned char	*str;

	if (!s)
		return ;
	str = s;
	while (n > 0)
	{
		*str = '\0';
		str++;
		n--;
	}
}

char	*ft_strdup_gnl(const char *s)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(ft_strlen_gnl(s) + 1);
	if (!str)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (0);
}
