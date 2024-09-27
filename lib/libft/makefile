# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akrid <akrid@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 21:37:56 by rtamouss          #+#    #+#              #
#    Updated: 2024/06/08 13:57:52 by akrid            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC
SRCS = ft_atoi.c ft_isalnum.c ft_isdigit.c ft_memcmp.c  ft_strchr.c  ft_strlcat.c ft_strncmp.c ft_substr.c \
ft_bzero.c   ft_isalpha.c ft_isprint.c ft_memcpy.c  ft_strdup.c  ft_strlcpy.c ft_strnstr.c ft_tolower.c \
ft_calloc.c  ft_isascii.c ft_memchr.c  ft_memset.c  ft_strjoin.c ft_strlen.c  ft_strrchr.c ft_toupper.c ft_split.c ft_itoa.c \
ft_strtrim.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_strmapi.c ft_memmove.c

BSRCS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS:.c=.o)
NAME = libft.a

all: $(NAME)


$(NAME) : $(OBJS)
	@ar rcs $@ $^

bonus: $(OBJS) ${BOBJS}

$(OBJS) : $(SRCS)
	@$(CC) $(CFLAGS) -c $^

$(BOBJS) : $(BSRCS)
	@$(CC) $(CFLAGS) -c $^
	@ar rcs $(NAME) $(BOBJS)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(BOBJS)

fclean : clean
	@rm -rf $(NAME)

re: fclean all


.PHONY : all bonus clean fclean re