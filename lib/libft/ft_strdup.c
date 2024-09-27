/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 23:31:14 by rtamouss          #+#    #+#             */
/*   Updated: 2023/11/16 23:15:57 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*s;

	i = 0;
	len = ft_strlen(s1);
	s = (char *)malloc(len * sizeof(char) + 1);
	if (s == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char *test = "whhat ?  ";	
// 	printf("%s\n", ft_strdup(test));
// 	printf("%s", strdup(test));
// 	return 0;	
// }