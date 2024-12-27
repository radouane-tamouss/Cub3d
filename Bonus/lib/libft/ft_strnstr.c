/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:43:24 by rtamouss          #+#    #+#             */
/*   Updated: 2024/03/08 09:46:05 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[j] == '\0' && len == 0)
		return ((char *)haystack);
	else if (!len)
		return (NULL);
	else if (needle[j] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

// #include <string.h>
// int	main(void)
// {
// 	char *needle = "sss";
// 	char *haystack = "sss";
// 	printf("%s",ft_strnstr(haystack,needle, 5));
// 	printf("\n%s",strnstr(haystack,needle,5));
// 	return (0);
// }
