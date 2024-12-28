CC = cc
RM = rm -rf
GET_NEXT_LINE_FILES = lib/lib_utils.c lib/get_next_line.c lib/get_next_line_utils.c
CFLAGS =  -O3 -flto -g3 #-Werror -Wextra -Wall#-fsanitize=address  
# MLX_FLAGS = -Imlx-linux -lXext -lX11 -lm -lz -O3 mlx-linux/libmlx.a
MLX_FLAGS = -I/usr/include -L/usr/lib -lXext -lX11 -lm -lz -O3 -lmlx

GARBAGE_COLLECTOR = ./garbage_collector/heap_controller.c ./garbage_collector/safer_func.c
BONUS_GARBAGE_COLLECTOR = Bonus/garbage_collector/heap_controller.c Bonus/garbage_collector/safer_func.c

UTILS_FILES =  utils/exiter.c utils/print_err.c 
BONUS_UTILS_FILES =  Bonus/utils/exiter.c Bonus/utils/print_err.c 


RENDER_FILES = rendering/background.c\
rendering/color.c\
rendering/event_handling.c\
rendering/event_handling_utils.c\
rendering/ft_math.c\
rendering/key_movments.c\
rendering/mouse_movements.c\
rendering/movement.c\
rendering/put_pixel.c\
rendering/ray.c\
rendering/rotation.c\
rendering/vector.c\
rendering/walls.c\

BONUS_RENDER_FILES = \
Bonus/rendering/animate_sprite_utils.c\
Bonus/rendering/background.c\
Bonus/rendering/color.c\
Bonus/rendering/event_handling.c\
Bonus/rendering/event_handling_utils.c\
Bonus/rendering/ft_math.c\
Bonus/rendering/handle_door.c\
Bonus/rendering/key_movments.c\
Bonus/rendering/minimap.c\
Bonus/rendering/mouse_movements.c\
Bonus/rendering/movement.c\
Bonus/rendering/put_pixel.c\
Bonus/rendering/ray.c\
Bonus/rendering/rendering_sprites.c\
Bonus/rendering/render_shapes.c\
Bonus/rendering/rotation.c\
Bonus/rendering/sprite_movements.c\
Bonus/rendering/vector.c\
Bonus/rendering/walls.c\
Bonus/rendering/door.c\
Bonus/rendering/transparent.c\
Bonus/rendering/animations/gun_reloading.c\
Bonus/rendering/animations/gun.c\
Bonus/rendering/animations/scope.c

INIT =\
init/init_data.c\
init/init_textures.c
BONUS_INIT =\
Bonus/init/load_scope_frames.c\
Bonus/init/load_gun_frames.c\
Bonus/init/init_textures.c\
Bonus/init/init_scope.c\
Bonus/init/init_gun.c\
Bonus/init/init_enemy.c\
Bonus/init/init_data.c\
Bonus/init/init_door.c\
Bonus/init/init_enemy.c

PARSING_FILES = \
parsing/check_file.c\
parsing/check_map.c\
parsing/check_map_utils.c\
parsing/check_player.c\
parsing/map_utils2.c\
parsing/map_utils.c\
parsing/other_functions.c\
parsing/parse_colors.c\
parsing/parse_textures_and_color_infos.c\
parsing/parse_textures.c
BONUS_PARSING_FILES =\
Bonus/parsing/check_file.c\
Bonus/parsing/check_map.c\
Bonus/parsing/check_map_utils.c\
Bonus/parsing/check_player.c\
Bonus/parsing/init_sprites.c\
Bonus/parsing/map_utils2.c\
Bonus/parsing/map_utils.c\
Bonus/parsing/other_functions.c\
Bonus/parsing/parse_colors.c\
Bonus/parsing/parse_textures_and_color_infos.c\
Bonus/parsing/parse_textures.c\

CFILES = main.c ${INIT} ${RENDER_FILES} ${PARSING_FILES} ${UTILS_FILES} ${GARBAGE_COLLECTOR} ${GET_NEXT_LINE_FILES} ft_split_charset.c
BONUS_CFILES = Bonus/main.c ${BONUS_INIT} ${BONUS_RENDER_FILES} ${BONUS_PARSING_FILES} ${BONUS_UTILS_FILES} ${BONUS_GARBAGE_COLLECTOR} ${GET_NEXT_LINE_FILES} ft_split_charset.c
OFILES = ${CFILES:.c=.o}
BONUS_OFILES = ${BONUS_CFILES:.c=.o}
BONUS_TEXTURES = door_frames dying_zombie gun3shoot movin_walk_gun3.slow reloading_gun3 running_gun3 spider weapon zombie zoom_shoot_gun3 
NAME = cub3D
BONUS_NAME = cub3d_bonus

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

all : ${NAME}
bonus : ${BONUS_NAME}


${NAME} : ${OFILES} ${LIBFT}
	$(CC) ${CFLAGS}  $^ -o $(NAME) ${MLX_FLAGS}

${BONUS_NAME} : ${BONUS_OFILES} ${LIBFT}
	@find textures -type f -name "*.gz" -exec gunzip {} +
	$(CC) ${CFLAGS}  $^ -o $(BONUS_NAME) ${MLX_FLAGS}

${LIBFT} :
	@make -C $(LIBFT_DIR)
	@make bonus -C $(LIBFT_DIR)

%.o: %.c
	$(CC) ${CFLAGS} -Imlx -c $< -o $@ -O3


clean :
	${RM} ${OFILES} $(BONUS_OFILES)
	@make clean -C $(LIBFT_DIR)

fclean : clean
	${RM} ${NAME} $(BONUS_NAME)
	@make fclean -C $(LIBFT_DIR)



re : fclean all

################# TODO remember to remove this ######################
f : bonus
	./$(BONUS_NAME) Bonus/ll.cub


# valgrind  --leak-check=full --show-leak-kinds=all  ./${NAME} ll.cub
#####################################################################
