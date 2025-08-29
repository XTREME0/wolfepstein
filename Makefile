
CC		= cc
CFLAGS	= #-fsanitize=address 
LFLAGS = -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit
RM		= @rm -f

NAME	= cub3D
HEADER = cub.h

SRC		= srcs/main.c srcs/raycasting.c srcs/moving.c
		

OBJ		= $(SRC:.c=.o)

all: $(NAME) clean

NAME = cub3D
HEADER = cub.h

all: $(NAME)

bruh:
	cc $(CFLAGS) $(LFLAGS) libft/libft.a get_next_line/*.c parsing/*.c srcs/*.c main.c -g -o cub3D 

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ) $(OBJ:.o=.d)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(OBJ:.o=.d)