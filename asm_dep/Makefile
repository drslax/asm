PROJECT 	= Assembler
CC			= gcc
FLAGS		= -Wall -Wextra -Werror -g
NAME		= asm
FILENAMES 	= *.c 
HDR 		= -I./includes -I./libft/
LIBFT		= libft/libft.a

all: $(NAME)

$(NAME):
	@make -C ./libft
	@$(CC) $(FLAGS) -o $(NAME) $(FILENAMES) $(HDR) $(LIBFT)

clean:
	@make clean -C ./libft
	@echo "Cleaning $(PROJECT) objects."

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)
	@echo "deleted."

re: fclean all
