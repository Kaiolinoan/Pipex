NAME = libft.a
CC = cc
CFLAGS = -Werror -Wall -Wextra -g
SRCS = $(wildcard **/*.c)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)

	@ar rcs $(NAME) $(OBJS)
	@echo 'Biblioteca criada'
	@echo 'Codigo compilado!'

%.o:%.c
	@$(CC) $(CFLAGS) -I. -c $< -o $@
 
clean:
	@find . -name '*.o' -delete
	@echo 'Objetos limpos!'

fclean: clean
	@rm -f $(NAME)
	@echo  'Biblioteca limpa!'

re: fclean all