PROJECT 	= Assembler
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
NAME		= asm
FILENAMES 	= sources/main.c sources/op.c \
			  sources/error.c sources/read_instructions.c sources/read_commands.c
HDR 		= -I./includes -I./libft/
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
