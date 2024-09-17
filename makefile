CC = cc
CFLAGS = -Werror -Wextra -Wall #-g3 #-fsanitize=address
RM = rm -rf
GARBAGE_COLLECTOR =
UTILS_FILES =
EXEC_FILES =
PARSING_FILES =
ENV= 
CFILES = main.c  ${PARSING_FILES} ${UTILS_FILES} ${GARBAGE_MAKER} ${ENV} ${EXEC_FILES}
OFILES = ${CFILES:.c=.o}
NAME = cub3D

all : ${NAME}

${NAME} : ${OFILES}
	${CC} ${CFLAGS} ${OFILES} -lreadline -o ${NAME}

%.o: %.c
	${CC} -c ${CFLAGS} $< -o $@

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