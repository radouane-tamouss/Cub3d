/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:21:54 by rtamouss          #+#    #+#             */
/*   Updated: 2023/11/17 17:13:50 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new -> next = *lst;
	*lst = new;
}

// int	main(void)
// {
// 	t_list *n = malloc(sizeof(t_list));
// 	t_list *n2 = ft_lstnew("world");
// 	n -> content = "hello";
// 	n -> next = NULL;
// 	ft_lstadd_front(&n, n2);
// 	while(n)
// 	{
// 		printf("%s\n", n->content);
// 		n = n->next;
// 	}
// 	return (0);
// }