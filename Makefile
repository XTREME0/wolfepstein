CC		= cc
CFLAGS	= -Wall -Werror -Wextra -fsanitize=address 
RM		= @rm -f

NAME	= cub3D
HEADER = cub3d.h

SRC		= main.c parsing/parsing.c parsing/file_validation.c get_next_line/*.c
		

OBJ		= $(SRC:.c=.o)

all: $(NAME) clean


%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD

bruh:
	cc libft/libft.a main.c get_next_line/*.c parsing/*.c -g -o cub3D

get_next_line/%.o: get_next_line/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

clean:
	$(RM) $(OBJ) $(OBJ:.o=.d)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(OBJ:.o=.d)
