/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:49:00 by rtamouss          #+#    #+#             */
/*   Updated: 2024/05/13 09:10:44 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *str, char sep)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == sep))
			i++;
		if (str[i] && !(str[i] == sep))
		{
			count++;
			while (str[i] && !(str[i] == sep))
				i++;
		}
	}
	return (count);
}

static char	**ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (0);
}

static char	**do_it(char **res, char const *s, char c, int i)
{
	int	start;
	int	end;
	int	j;

	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		end = i;
		if (end > start)
		{
			res[j] = (char *)malloc((end - start + 1) * sizeof(char));
			if (!res[j])
				return (ft_free(res));
			ft_strlcpy(res[j], &s[start], end - start + 1);
			j++;
		}
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	res = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	return (do_it(res, s, c, i));
}

// #include <stdio.h>
// int	 main(void)
// {
// 	char *s  = ",,,,hello,world,this,a test   ,,,,, helo,,,";
// 	char **split = ft_split(s,',');
// 	int i = 0;
// 	while (split[i] != NULL)
// 	{
// 		printf("%d = |%s|\n" , i, split[i]);
// 		i++;
// 	}
// 	return 0;
// }