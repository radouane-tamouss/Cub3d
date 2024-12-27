/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:16:59 by rtamouss          #+#    #+#             */
/*   Updated: 2023/11/16 17:54:12 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;
	size_t	len;

	len = ft_strlen(s);
	i = 0;
	ptr = NULL;
	while (i <= len)
	{
		if (s[i] == (const char)c)
			ptr = (char *)(s + i);
		i++;
	}
	if (ptr != NULL)
		return (ptr);
	else
		return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int		main(void)
// {
// 	char *s = "helloecc";
// 	char *k = "helloecc";
// 	printf("located pointer : %p\nvalue : %s\n", ft_strrchr(s,'e')
// ,ft_strrchr(s,'e'));
// 	printf("located pointer : %p\nvalue : %s\n", strrchr(k,'e'),strrchr(k,'e'));
// 	return (0);
// }