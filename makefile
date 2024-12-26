CC = cc
RM = rm -rf
GET_NEXT_LINE_FILES = lib/lib_utils.c lib/get_next_line.c lib/get_next_line_utils.c
CFLAGS =  -O3 -flto -g3 #-fsanitize=address #-Werror -Wextra -Wall 
MLX_FLAGS = -Imlx-linux -lXext -lX11 -lm -lz -O3 mlx-linux/libmlx.a
GARBAGE_COLLECTOR = ./garbage_collector/heap_controller.c ./garbage_collector/safer_func.c
UTILS_FILES =  utils/exiter.c utils/print_err.c 
RENDER_FILES = rendering/animate_sprite_utils.c\
rendering/background.c\
rendering/color.c\
rendering/event_handling.c\
rendering/event_handling_utils.c\
rendering/ft_math.c\
rendering/handle_door.c\
rendering/key_movments.c\
rendering/minimap.c\
rendering/mouse_movements.c\
rendering/movement.c\
rendering/put_pixel.c\
rendering/ray.c\
rendering/rendering_sprites.c\
rendering/render_shapes.c\
rendering/rotation.c\
rendering/sprite_movements.c\
rendering/vector.c\
rendering/walls.c
PARSING_FILES = parsing/check_file.c  parsing/check_map.c  parsing/check_map_utils.c parsing/check_player.c  parsing/init_sprites.c\
	parsing/map_utils2.c  parsing/map_utils.c  parsing/other_functions.c  parsing/parse_colors.c  parsing/parse_textures_and_color_infos.c  parsing/parse_textures.c
CFILES = main.c ${RENDER_FILES} ${PARSING_FILES} ${UTILS_FILES} ${GARBAGE_COLLECTOR} ${GET_NEXT_LINE_FILES} ft_split_charset.c
OFILES = ${CFILES:.c=.o}
NAME = cub3D

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

all : ${NAME}




${NAME} : ${OFILES} ${LIBFT}
	#$(CC) ${CFLAGS} $^ -o $(NAME) $(MLX_MAC_FLAGS)
	# ${NAME} : ${OFILES} ${LIBFT}
	$(CC) ${CFLAGS}  $^ -o $(NAME) ${MLX_FLAGS}

${LIBFT} :
	@make re -C mlx-linux
	@make -C $(LIBFT_DIR)
	@make bonus -C $(LIBFT_DIR)
	@echo "\033[0;32m[LIBFT COMPILED]\033[0m"

%.o: %.c
	$(CC) ${CFLAGS} -Imlx -c $< -o $@ -O3


clean :
	${RM} ${OFILES}
	make clean -C $(LIBFT_DIR)

fclean : clean
	${RM} ${NAME}
	make fclean -C $(LIBFT_DIR)

re : fclean all

################# TODO remember to remove this ######################
f : all
	./cub3D ll.cub


	 # valgrind  --leak-check=full --show-leak-kinds=all  ./${NAME} ll.cub

rerun : re run


debugg: $(NAME)
	gdb --args --args ./cub3d ll.cub

#####################################################################
