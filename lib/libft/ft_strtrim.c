/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:55:54 by rtamouss          #+#    #+#             */
/*   Updated: 2023/11/17 16:11:09 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*res;

	if (!s1 || !set)
		return (0);
	len = 0;
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len > 0 && ft_strchr(set, s1[len - 1]))
		len--;
	res = (char *)malloc(len + 1);
	if (!res)
		return (0);
	ft_strlcpy(res, s1, len + 1);
	return (res);
}

// int	main(void)
// {
// 	printf("|%s|",ft_strtrim("-----trim-------------","--"));
// 	return (0);
// }