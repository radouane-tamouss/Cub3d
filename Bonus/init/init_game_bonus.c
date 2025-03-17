void init_game(t_game *game)
{
    game->north.path = NULL;
    game->south.path = NULL;
    game->west.path = NULL;
    game->east.path = NULL;
    game->floor.path = NULL;
    game->floor.color = NULL;
    game->floor.r = 0;
    game->floor.g = 0;
    game->floor.b = 0;
    game->ceiling.path = NULL;
    game->ceiling.color = NULL;
    game->ceiling.r = 0;
    game->ceiling.g = 0;
    game->ceiling.b = 0;
    game->map = NULL;
    game->map_height = 0;
    game->map_width = 0;
} 