/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:49:10 by eouhrich          #+#    #+#             */
/*   Updated: 2024/12/23 19:43:30 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// clang-format off
double	ft_abs(double nbr)
{
	return (((nbr >= 0) - (nbr < 0)) * nbr);
}

float	ft_min(float nbr1, float nbr2)
{
	if (nbr1 >= nbr2)
		return (nbr2);
	return (nbr1);
}

float	ft_max(float nbr1, float nbr2)
{
	if (nbr1 >= nbr2)
		return (nbr1);
	return (nbr2);
}
