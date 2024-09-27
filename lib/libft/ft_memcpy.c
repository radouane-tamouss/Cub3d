/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 22:20:39 by rtamouss          #+#    #+#             */
/*   Updated: 2023/11/15 21:16:32 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dstptr;
	unsigned char	*srcptr;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	dstptr = (unsigned char *)dst;
	srcptr = (unsigned char *)src;
	while (i < n)
	{
		dstptr[i] = srcptr[i];
		i++;
	}
	return (dst);
}
