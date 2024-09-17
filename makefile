CC = cc
CFLAGS = -Werror -Wextra -Wall -O3 #-g3 #-fsanitize=address
MLX_FLAGS = -Lmlx -lmlx -lm -framework OpenGL -framework AppKit 
RM = rm -rf
GARBAGE_COLLECTOR = ./garbage_collector/heap_controller.c
UTILS_FILES =
RENDER_FILES =
PARSING_FILES =
ENV= 
CFILES = main.c ${RENDER_FILES} ${PARSING_FILES} ${UTILS_FILES} ${GARBAGE_COLLECTOR}
OFILES = ${CFILES:.c=.o}
NAME = cub3D

all : ${NAME}

${NAME} : ${OFILES}
	$(CC) ${CFLAGS} $(OFILES) ${MLX_FLAGS} -o $(NAME

%.o: %.c
	$(CC) ${CFLAGS} -Imlx -c $< -o $@

clean :
	${RM} ${OFILES}

fclean : clean
	${RM} ${NAME}

re : fclean all

################# TODO remember to remove this ######################
run : all
	valgrind  --leak-check=full  ./${NAME}

rerun : re run
#####################################################################