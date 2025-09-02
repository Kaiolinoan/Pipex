NAME = pipex
BONUS_NAME = pipex_bonus
CC = cc
CFLAGS = -Werror -Wall -Wextra -g3 -I. -I.. 
SRC_FOLDER = src
BONUS_FOLDER = bonus
OBJ_FOLDER = obj
SRCS_FILES = $(addprefix $(SRC_FOLDER)/, $(addsuffix .c, main utils children path split_quotes))
BONUS_FILES = $(addprefix $(BONUS_FOLDER)/, $(addsuffix .c, main_bonus utils_bonus children_bonus path_bonus split_quotes_bonus start_bonus))
OBJS = $(patsubst $(SRC_FOLDER)/%.c, $(OBJ_FOLDER)/%.o, $(SRCS_FILES))
BONUS_OBJS = $(patsubst $(BONUS_FOLDER)/%.c, $(OBJ_FOLDER)/%.o, $(BONUS_FILES))

all: $(OBJ_FOLDER) $(NAME)

$(NAME): $(OBJS)
	@make -s -C Libft
	@cp ./Libft/libft.a .
	@$(CC) $(CFLAGS) $(OBJS) libft.a -o $(NAME)
	@echo 'Biblioteca criada'
	@echo 'Codigo compilado!'

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_FOLDER)/%.o: $(BONUS_FOLDER)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_FOLDER):
	@mkdir -p $@

bonus: $(BONUS_NAME) 

$(BONUS_NAME): $(BONUS_OBJS) 
	@$(CC) $(CFLAGS) $(BONUS_OBJS) libft.a -o $(BONUS_NAME)
	@echo 'Bonus criado'

clean:
	@rm -rf $(OBJ_FOLDER)
	@make clean -s -C Libft 
	@echo 'Objetos limpos!'

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@rm -f libft.a
	@make fclean -s -C Libft 
	@echo  'Biblioteca limpa!'

re: fclean all