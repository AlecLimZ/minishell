NAME			=	minishell
SRC_DIR			=	SRC
OBJ_DIR			=	SRC/OBJS
LDFLAGS			=	/usr/local/opt/readline/lib/*.a -lncurses
CPPFLAGS		=	-I/usr/local/opt/readline/include
INC_DIR			= 	-IINCLUDE
LIBPATH			=	SRC/libft
LIBFT			=	SRC/libft/libft.a
SRC				= 	*.c
OBJS			=	$(addprefix $(OBJ_DIR)/, $(SRC:%c=%o))
GCC				= 	gcc -Wall -Wextra -Werror -fsanitize=address

DEF				= "\033[0m"
YELLOW			= "\033[1;33m"
GREEN			= "\033[1;32m"
RED				= "\033[0;31m"
CYAN			= "\033[3;36m"

all:			$(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				@echo $(YELLOW)"\nCreating \"OBJS\" folder...⏳"$(DEF)
				@mkdir -p $(OBJ_DIR)
				@echo $(CYAN)
				@make bonus -C $(LIBPATH)
				@echo $(GREEN)"Successfully created ✅\n"$(DEF)
				@echo $(YELLOW)"Creating object files...⏳"$(DEF)
				@$(GCC) $(INC_DIR) $(CPPFLAGS) -I$(LIBPATH) -c $^
				@mv *.o $(OBJ_DIR)
				@echo $(GREEN)"Successfully created ✅\n"$(DEF)

$(NAME):		$(OBJS)
				@echo $(YELLOW)"Creating the minishell...⏳"$(DEF)
				@$(GCC) $(LDFLAGS) $(LIBFT) $^ -o $@
				@echo $(GREEN)"Successfully created ✅\n"$(DEF)

norm:
				@echo $(YELLOW)"⏳Checking norminette...⏳"$(CYAN)
				norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*.c
				norminette -R CheckDefine $(INC_DIR)/*.h

clean:
				@rm -rf $(OBJ_DIR)
				@make clean -C $(LIBPATH)
				@echo $(RED)"Object files & object folder GONE ☠️"$(DEF)

fclean:			clean
				@rm -rf $(NAME)
				@make fclean -C $(LIBPATH)
				@echo $(RED)"Executable file GONE ☠️"$(DEF)

re:				fclean all

.PHONY:			all clean fclean re
