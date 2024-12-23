/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:50:15 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/23 13:48:21 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

unsigned int	create_trgb(unsigned char t, unsigned char r,
		unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

unsigned char	get_t(unsigned int trgb)
{
	return ((trgb >> 24) & 255);
}

unsigned char	get_r(unsigned int trgb)
{
	return ((trgb >> 16) & 255);
}

unsigned char	get_g(unsigned int trgb)
{
	return ((trgb >> 8) & 255);
}

unsigned char	get_b(unsigned int trgb)
{
	return (trgb & 255);
}
