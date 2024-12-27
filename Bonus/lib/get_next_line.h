/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamousse.red <atamousse.red@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 00:47:16 by atamousse.red     #+#    #+#             */
/*   Updated: 2024/12/27 00:47:17 by atamousse.red    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// clang-format off

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include "../cube.h"

size_t	ft_strlen(const char *theString);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t num, size_t size);
char	*ft_strchr(const char *string, int searchedChar);
char	*ft_get_line(char *buffer);
char	*ft_rest(char *buffer);
char	*read_file(int fd, char *result);
char	*get_next_line(int fd);

#endif
