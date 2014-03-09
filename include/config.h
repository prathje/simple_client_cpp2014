#ifndef CONFIG_H
#define CONFIG_H

//SHAPES AND COLORS
#define SHAPE_NONE  -1
#define SHAPE_ACORN 0
#define SHAPE_BELL 1
#define SHAPE_CLUBS 2
#define SHAPE_DIAMOND 3
#define SHAPE_HEART 4
#define SHAPE_SPADES 5
#define NUM_SHAPES 6
#define COLOR_NONE -1
#define COLOR_BLUE 0
#define COLOR_GREEN 1
#define COLOR_MAGENTA 2
#define COLOR_ORANGE 3
#define COLOR_VIOLET 4
#define COLOR_YELLOW 5
#define NUM_COLORS 6


//MOVES
#define MOVE_PLACE_FIRST 0
#define MOVE_PLACE 1
#define MOVE_EXCHANGE 2

#define MODE_COLOR 1
#define MODE_SHAPE 2
//ERRORS
#define ERROR_NONE 0
#define ERROR_UNSPECIFIC 1


//main
#define FIELD_WIDTH 16
#define FIELD_HEIGHT 16
#define FIELDINDEX_HIDDEN -4
#define FIELDINDEX_OPEN -3
#define FIELDINDEX_HAND_RED -2
#define FIELDINDEX_HAND_BLUE -1


//NETWORK
#define STATE_REQUESTING 0
#define STATE_JOINING 1
#define STATE_JOINED 2
#define STATE_WAITING 3
#define STATE_MOVING 4
#define STATE_END 5
#define STATE_LEAVE 6
#define STATE_ERROR 7


//FIELD
#define POSITION_BAG 0
#define POSITION_OPEN 1
#define POSITION_RED 2
#define POSITION_BLUE 3
#define POSITION_FIELD 4



#endif
