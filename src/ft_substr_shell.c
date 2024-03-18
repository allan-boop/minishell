#include "../include/minishell.h"

char	*ft_substr_shell(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	int		j;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
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
