/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:40:02 by rtamouss          #+#    #+#             */
/*   Updated: 2024/05/28 18:36:26 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	size;

	size = ft_strlen(s);
	i = 0;
	while (s && i <= size)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (c == 0)
		return ((char *)(s + i));
	return (NULL);
}

// #include <string.h>
// int	main()
// {
// 	char *s = "helskj";
// 	char c = 'w';
// 	printf("%s\n", ft_strchr(s,c));
// 	printf("-----------------\n");
// 	char *s1 = "hleskj";
// 	char c1 = 'w';
// 	printf("%s\n", strchr(s1,c1));
// 	return 0;
// }