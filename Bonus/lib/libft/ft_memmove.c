/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 01:51:52 by rtamouss          #+#    #+#             */
/*   Updated: 2023/11/12 02:35:22 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dstptr;
	unsigned char	*srcptr;

	dstptr = (unsigned char *)dst;
	srcptr = (unsigned char *)src;
	i = 0;
	if (dstptr == NULL && srcptr == NULL)
		return (NULL);
	if (dstptr > srcptr)
	{
		while (len-- > 0)
			dstptr[len] = srcptr[len];
	}
	else
	{
		while (i < len)
		{
			dstptr[i] = srcptr[i];
			i++;
		}
	}
	return (dst);
}
