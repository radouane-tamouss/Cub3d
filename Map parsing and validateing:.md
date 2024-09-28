Map parsing and validateing: 

- [ ] the map must be composed only of only 6 possible characters :
    => 0 for an empty space
    => 1 for a wall
    => N,S,E or W fot the player's start position and spawning orientation.
    => te map must be closed/surrounded by walls
    => Except for the map content,each type of element can be separated by one or more empty line(s).
    => Except for the map which always has the be the last, each type of element can be set in any order in the file.
    The map must be parsed as it looks in the file. Spaces are a valid part of the map and are up to you to handle. You must be able to parse any kind of map, as long as it respects the rules of the map.

These are examples of valid map files.

--------------------------------------------

NO ./path_to_the_notrh_texture
SO ./path_to_the_south_texture
WE ./path_to_the_WEST_texture
EA ./path_to_the_EAST_texture

F 220,100,0
C 225,30,0

            11111111111111111111111
            10000000001000000000001
            10110000001000000000001
            10000100000000000001001
11111111111110110100000000000000001
10000000000000100000000000100000001
10000000000000000000001111111111111
10000000000000000010010101
10001010101000000000011111
11000000000000000000000001111
11111111111111111110101011
1000111 111101 10100111111
1111111 111111 11111111111

--------------------------------------------

F 97,247,67
NO ./textures/amongus.xpm
SO ./textures/amongus.xpm
WE ./textrues/jib.xpm
EA ./textures/jib.xpm
C 235,115,115

  11111111111111111111111
 110000000000