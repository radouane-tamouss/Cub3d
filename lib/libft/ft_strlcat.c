/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:42:55 by rtamouss          #+#    #+#             */
/*   Updated: 2023/11/16 17:37:52 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	slen;
	size_t	dlen;

	i = 0;
	slen = ft_strlen(src);
	if (dstsize == 0)
		return (slen);
	dlen = ft_strlen(dst);
	if (dstsize <= dlen)
		return (slen + dstsize);
	while (src[i] && i < (dstsize - dlen - 1))
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}

// #include <string.h>
// int main()
// {
// 	char *s = "hello";
// 	char d[15] = "hello world ";
// 	int res = ft_strlcat(d,s,15);
// 	char *s1 = "hello";
// 	printf("returned : %d\nsrc ; %s\ndst : %s\n",res, s, d);
// 	char d1[] = "hello world ";
// 	int res1 = strlcat(d1,s1,15);
// 	printf("returned : %d\nsrc ; %s\ndst : %s\n",res1, s1, d1);
// 	return (0);
// }