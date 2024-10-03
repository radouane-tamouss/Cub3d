/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:02:06 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/27 12:49:03 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../cube.h"

// this will act as clean exiter , that free and remove leaks before exiting
void	exiter(int code)
{
	free_all_heap();
	exit(code);
}