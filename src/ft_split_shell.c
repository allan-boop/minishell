#include "../include/minishell.h"

static size_t	count_words_split(char const *s, char c)
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

static char	**allocate_memory(size_t count)
{
	char	**tab_shell;

	tab_shell = (char **)ft_alloc(sizeof(char *) * (count + 1));
	if (!tab_shell)
		return (NULL);
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

static char	**divide(char const *s, char c, char **tab_shell)
{
	unsigned int		i;
	int					j;
	size_t				start;
	char				quote;

	i = 0;
	j = 0;
	while (s[i])
	{
		printf("s[i] = %c\n", s[i]);
		quote = 'a';
		if (s[i] == c)
			while (s[i] == c)
				i++;
		if (s[i] == 34 || s[i] == 39)
		{
			quote = s[i];
			i++;
		}
		start = i;
		if (quote == 34 || quote == 39)
		{
			i++;
			while (s[i] != '\0' && s[i] != quote)
				i++;
			tab_shell[j] = ft_substr_shell(s, start, i - start);
			if (!tab_shell[j])
			{
				unblock(tab_shell);
				return (NULL);
			}
			j++;
			i++;
		}
		else if (s[i] != c && s[i] != '\0')
		{
			while (s[i] != '\0' && s[i] != c && s[i] != 34 && s[i] != 39)
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

	count = count_words_split(s, c);
	tab_shell = allocate_memory(count);
	if (!tab_shell)
		return (NULL);
	if (!divide(s, c, tab_shell))
	{
		return (NULL);
	}
	return (tab_shell);
}
