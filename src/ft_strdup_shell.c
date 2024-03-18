#include "../include/minishell.h"

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
