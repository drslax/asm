PROJECT 	= Assembler
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
NAME		= asm
FILENAMES 	= main.c\
			  add.c
HDR 		= -I /asm.h
LIBFT		= libft/libft.a

all: $(NAME)

$(NAME):
	@make -C ./libft
	@$(CC) -o $(NAME) $(FILENAMES) $(HDR) $(LIBFT)

clean:
	@make clean -C ./libft
	@echo "Cleaning $(PROJECT) objects."

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)
	@echo "deleted."

re: fclean all
