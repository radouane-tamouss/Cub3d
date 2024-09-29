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

NO ./path_to_the_north texture
SO ./path_to_the_south texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
С 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111

--------------------------------------------
I wont talk much about the texture and colors here.
Unlike so_long, the rules of the map are laxed and allowing more creative freedom. The map will may not be rectangular in shape and may have many weird edges/curves and corners. However, the map can still be parsed as a 2d
character array and treated like normal strings with different lengths each row.
Comment

As such, I came up with a few map validation rules. Assume that we are scanning the map from top to bottom, left to right :

Ignore all leading whitespaces.
If the current row is the 0th row or the final row, only accept '1's and ' 's.
else, The first and final character should always be a '1'.
In the case of any non leading whitespaces, the only acceptable characters adjacent to the space are '1's or ' 's.
If strlen(curr_row) > strlen(row_on_top) && current col > strlen(row_on_top), current character should be '1'
If strlen(curr_row) > strlen(row_on_bottom) && current col > strlen(row_on_bottom), current character should be '1'
Those rules should pass all the map requirements given.