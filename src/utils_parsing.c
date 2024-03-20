#include "../include/minishell.h"

void	del_if_same(t_malloc_ptr *l_m, t_malloc_ptr *tmp, void *var)
{
	if (l_m->next && l_m->next->ptr == var)
	{
		tmp = l_m->next;
		l_m->next = tmp->next;
		free(tmp->ptr);
		tmp->ptr = NULL;
		free(tmp);
		tmp = NULL;
	}
}

char	*ft_strdup_shell(const char *s)
{
	char	*str;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	str = ft_alloc(len);
	if (!str)
		return (NULL);
	ft_memcpy(str, s, len);
	return (str);
}

char	*ft_substr_shell(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	int		j;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup_shell(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	i = 0;
	j = start;
	ptr = ft_alloc(len + 1);
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

size_t	count_words_split(char const *s, char c)
{
	int		i;
	size_t	count;

	if (!s)
		return (0);
	if (c == '\0')
	{
		if (*s == '\0')
			return (0);
		else
			return (1);
	}
	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}
