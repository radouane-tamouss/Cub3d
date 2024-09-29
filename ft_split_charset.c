#include "cube.h"


int	check_charset(char *charset, char c)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_count_words(char const *str, char *charset)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && check_charset(charset, str[i]) == 1)
			i++;
		if (str[i] && !(check_charset(charset, str[i]) == 1))
		{
			count++;
			while (str[i] && !(check_charset(charset, str[i]) == 1))
				i++;
		}
	}
	return (count);
}

static char	**ft_free2(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (0);
}

static char	**do_it(char **res, char const *s, char* charset, int i)
{
	int	start;
	int	end;
	int	j;

	j = 0;
	while (s[i])
	{
		while (s[i] && check_charset(charset, s[i]) == 1)
			i++;
		start = i;
		while (s[i] && check_charset(charset, s[i]) != 1)
			i++;
		end = i;
		if (end > start)
		{
			res[j] = (char *)malloc((end - start + 1) * sizeof(char));
			if (!res[j])
				return (ft_free2(res));
			ft_strlcpy(res[j], &s[start], end - start + 1);
			j++;
		}
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split2(char const *s, char *charset)
{
	char	**res;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	res = (char **)malloc((ft_count_words(s, charset) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	return (do_it(res, s, charset, i));
}