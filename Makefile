
CC		= cc
CFLAGS	= -Wall -Werror -Wextra 
LFLAGS = -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit
NAME	= cub3D
OSRC		= main.c get_next_line.c get_next_line_utils.c creating_win_tex.c creating_win_tex2.c \
			init_mapgame.c init_player.c moving.c raycasting.c raycasting2.c raycasting3.c render_walls.c render_walls2.c \
			color.c cube_init_free.c error.c file_validation.c helpers.c helpers2.c mapcheck.c parse_map.c parsing.c set_options.c

OBJ		= $(addprefix objs/, $(OSRC:.c=.o))
LIB		= libft/libft.a

all: $(LIB) $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) $(LFLAGS) $(LIB) -o $(NAME)

$(LIB):
	$(MAKE) -C libft

objs/%.o: %.c $(LIB)
	mkdir -p objs
	$(CC) $(CFLAGS)  -MMD -c $< -o $@

objs/%.o: get_next_line/%.c $(LIB)
	mkdir -p objs
	$(CC) $(CFLAGS) -MMD -c $< -o $@

objs/%.o: srcs/%.c $(LIB)
	mkdir -p objs
	$(CC) $(CFLAGS) -MMD -c $< -o $@

objs/%.o: parsing/%.c $(LIB)
	mkdir -p objs
	$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	rm -rf objs
	$(MAKE) -C libft fclean

fclean: clean
	rm -f $(NAME) 

re: fclean all

-include $(OBJ:.o=.d)