#include "../../include/minishell.h"

static char	**allocate_memory(size_t count)
{
	char	**tab_shell;

	tab_shell = (char **)ft_alloc(sizeof(char *) * (count + 1));
	tab_shell[0] = NULL;
	return ((char **) tab_shell);
}

static void	unblock(char **tab_shell)
{
	int	i;

	i = 0;
	while (tab_shell[i])
	{
		free(tab_shell[i]);
		tab_shell[i] = NULL;
		i++;
	}
	free(tab_shell);
}

static char	**divide(char const *s, char c, char **tab_shell, size_t start)
{
	unsigned int		i;
	int					j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		if (s[i] != c && s[i] != '\0')
		{
			while (s[i] != '\0' && s[i] != c)
				i++;
			tab_shell[j] = ft_substr_shell(s, start, i - start);
			if (!tab_shell[j])
			{
				unblock(tab_shell);
				return (NULL);
			}
			j++;
		}
	}
	tab_shell[j] = NULL;
	return (tab_shell);
}

char	**ft_split_shell(char const *s, char c)
{
	size_t	count;
	char	**tab_shell;
	size_t	start;

	start = 0;
	count = count_words_split(s, c);
	tab_shell = allocate_memory(count);
	if (!tab_shell)
		return (NULL);
	if (!divide(s, c, tab_shell, start))
	{
		return (NULL);
	}
	return (tab_shell);
}
