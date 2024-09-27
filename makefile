CC = cc
CFLAGS =  #-Werror -Wextra -Wall  #-g3 #-fsanitize=address
MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -O3
RM = rm -rf
GARBAGE_COLLECTOR = ./garbage_collector/heap_controller.c
UTILS_FILES =  utils/exiter.c utils/ft_strlen.c utils/print_err.c 
RENDER_FILES = rendering/put_pixel.c rendering/background.c
PARSING_FILES =
CFILES = main.c ${RENDER_FILES} ${PARSING_FILES} ${UTILS_FILES} ${GARBAGE_COLLECTOR}
OFILES = ${CFILES:.c=.o}
NAME = cub3D

all : ${NAME}

${NAME} : ${OFILES}
	$(CC) ${CFLAGS} $(OFILES) ${MLX_FLAGS} -o $(NAME)

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