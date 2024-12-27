/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:58:16 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/26 23:58:20 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


void	sprint(int keycode)
{
	if (keycode == SHIFT_LIN)
		get_data()->speed = 10;
}

