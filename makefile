CC = cc
RM = rm -rf
GET_NEXT_LINE_FILES = lib/lib_utils.c lib/get_next_line.c lib/get_next_line_utils.c
CFLAGS =  -O3 -flto -g3 #-Werror -Wextra -Wall#-fsanitize=address  
# MLX_FLAGS = -Imlx-linux -lXext -lX11 -lm -lz -O3 mlx-linux/libmlx.a
MLX_FLAGS = -I/usr/include -L/usr/lib -lXext -lX11 -lm -lz -O3 -lmlx

GARBAGE_COLLECTOR = ./garbage_collector/heap_controller.c ./garbage_collector/safer_func.c
BONUS_GARBAGE_COLLECTOR = Bonus/garbage_collector/heap_controller_bonus.c Bonus/garbage_collector/safer_func_bonus.c

UTILS_FILES =  utils/exiter.c utils/print_err.c 
BONUS_UTILS_FILES =  Bonus/utils/exiter_bonus.c Bonus/utils/print_err_bonus.c 


RENDER_FILES = rendering/background.c\
rendering/color.c\
rendering/event_handling.c\
rendering/event_handling_utils.c\
rendering/ft_math.c\
rendering/key_movments.c\
rendering/movement.c\
rendering/put_pixel.c\
rendering/ray.c\
rendering/rotation.c\
rendering/vector.c\
rendering/walls.c\

BONUS_RENDER_FILES = \
Bonus/rendering/animate_sprite_utils_bonus.c\
Bonus/rendering/background_bonus.c\
Bonus/rendering/color_bonus.c\
Bonus/rendering/event_handling_bonus.c\
Bonus/rendering/event_handling_utils_bonus.c\
Bonus/rendering/ft_math_bonus.c\
Bonus/rendering/handle_door_bonus.c\
Bonus/rendering/key_movments_bonus.c\
Bonus/rendering/minimap_bonus.c\
Bonus/rendering/mouse_movements_bonus.c\
Bonus/rendering/movement_bonus.c\
Bonus/rendering/put_pixel_bonus.c\
Bonus/rendering/ray_bonus.c\
Bonus/rendering/rendering_sprites_bonus.c\
Bonus/rendering/render_shapes_bonus.c\
Bonus/rendering/rotation_bonus.c\
Bonus/rendering/sprite_movements_bonus.c\
Bonus/rendering/vector_bonus.c\
Bonus/rendering/walls_bonus.c\
Bonus/rendering/door_bonus.c\
Bonus/rendering/transparent_bonus.c\
Bonus/rendering/animations/gun_reloading_bonus.c\
Bonus/rendering/animations/gun_bonus.c\
Bonus/rendering/animations/scope_bonus.c

INIT =\
init/init_data.c\
init/init_textures.c
BONUS_INIT =\
Bonus/init/load_scope_frames_bonus.c\
Bonus/init/load_gun_frames_bonus.c\
Bonus/init/init_textures_bonus.c\
Bonus/init/init_scope_bonus.c\
Bonus/init/init_gun_bonus.c\
Bonus/init/init_enemy_bonus.c\
Bonus/init/init_data_bonus.c\
Bonus/init/init_door_bonus.c\
Bonus/init/init_enemy_bonus.c

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
Bonus/parsing/check_file_bonus.c\
Bonus/parsing/check_map_bonus.c\
Bonus/parsing/check_map_utils_bonus.c\
Bonus/parsing/check_player_bonus.c\
Bonus/parsing/init_sprites_bonus.c\
Bonus/parsing/map_utils2_bonus.c\
Bonus/parsing/map_utils_bonus.c\
Bonus/parsing/other_functions_bonus.c\
Bonus/parsing/parse_colors_bonus.c\
Bonus/parsing/parse_textures_and_color_infos_bonus.c\
Bonus/parsing/parse_textures_bonus.c

CFILES = main.c ${INIT} ${RENDER_FILES} ${PARSING_FILES} ${UTILS_FILES} ${GARBAGE_COLLECTOR} ${GET_NEXT_LINE_FILES} ft_split_charset.c
BONUS_CFILES = Bonus/main_bonus.c ${BONUS_INIT} ${BONUS_RENDER_FILES} ${BONUS_PARSING_FILES} ${BONUS_UTILS_FILES} ${BONUS_GARBAGE_COLLECTOR} ${GET_NEXT_LINE_FILES} ft_split_charset.c
OFILES = ${CFILES:.c=.o}
BONUS_OFILES = ${BONUS_CFILES:.c=.o}
NAME = cub3D
BONUS_NAME = cub3D_bonus

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
