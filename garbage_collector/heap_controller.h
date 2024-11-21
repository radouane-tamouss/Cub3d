/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_controller.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 01:17:41 by eouhrich          #+#    #+#             */
/*   Updated: 2024/11/21 01:20:12 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_CONTROLLER_H
# define HEAP_CONTROLLER_H
# include <stdlib.h>

//==== struct of HEAP CONTROLLER ==
typedef struct	s_heap
{
	void	*ptr;
	struct s_heap	*next;
} t_heap;
// the api functions to use 

void	*mallocate(size_t size);
void	free_all_heap(void);
void	free_ptr(void *ptr);

#endif