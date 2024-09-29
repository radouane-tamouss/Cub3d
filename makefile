CC = cc
# CFLAGS = -Werror -Wextra -Wall -O3 #-g3 #-fsanitize=address
MLX_FLAGS = -Lmlx -lmlx -lm -framework OpenGL -framework AppKit 
RM = rm -rf
# GARBAGE_COLLECTOR = ./garbage_collector/heap_controller.c
# UTILS_FILES =
# RENDER_FILES =
# PARSING_FILES =
GET_NEXT_LINE_FILES = lib/lib_utils.c lib/get_next_line.c lib/get_next_line_utils.c
ENV= 
CFILES = main.c ${RENDER_FILES} ${PARSING_FILES} ${UTILS_FILES} ${GARBAGE_COLLECTOR} ${GET_NEXT_LINE_FILES} ft_split_charset.c
OFILES = ${CFILES:.c=.o}
NAME = cub3D

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

all : ${NAME}



${NAME} : ${OFILES} ${LIBFT}
	$(CC) ${CFLAGS} $^ -o $(NAME)

${LIBFT} :
	@make -C $(LIBFT_DIR)
	@make bonus -C $(LIBFT_DIR)
	@echo "\033[0;32m[LIBFT COMPILED]\033[0m"

%.o: %.c
	$(CC) ${CFLAGS} -c $< -o $@
	# $(CC) ${CFLAGS} -Imlx -c $< -o $@

clean :
	${RM} ${OFILES}
	make clean -C $(LIBFT_DIR)

fclean : clean
	${RM} ${NAME}
	make fclean -C $(LIBFT_DIR)

re : fclean all

################# TODO remember to remove this ######################
run : all
	# valgrind  --leak-check=full  ./${NAME}
	./${NAME}

rerun : re run
#####################################################################