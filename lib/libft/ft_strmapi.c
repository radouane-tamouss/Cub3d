/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 22:26:13 by rtamouss          #+#    #+#             */
/*   Updated: 2023/11/16 22:15:10 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*ptr;
	size_t	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// char f(unsigned int index, char c)
// {
// 	if (index % 2 == 0)
// 		c = '0';
// 	return (c);
// }

// int 	main(void)
// {
// 	char *s = "hello world ";
// 	char *ptr = ft_strmapi(s, &f);
// 	printf("%s", ptr);
// 	return (0);
// }