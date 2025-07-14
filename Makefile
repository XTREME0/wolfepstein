CC		= cc
CFLAGS	= -Wall -Werror -Wextra -fsanitize=address 
RM		= @rm -f

NAME	= cub3D
HEADER = cub3d.h

SRC		= main.c parsing/parsing.c parsing/file_validation.c
		

OBJ		= $(SRC:.c=.o)

all: $(NAME) clean


%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

clean:
	$(RM) $(OBJ) $(OBJ:.o=.d)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(OBJ:.o=.d)
