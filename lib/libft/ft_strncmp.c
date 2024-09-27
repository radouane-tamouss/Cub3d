/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:19:14 by rtamouss          #+#    #+#             */
/*   Updated: 2023/11/16 18:04:35 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		return (0);
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// int	main(void)
// {
// 	char *s1 = "hello world";
// 	char *s2 = "yello world";
// 	printf("%d", ft_strncmp(s1,s2,20));
// 	printf("\n%d\n", strncmp(s1,s2,20));
// 	return (0);
// }