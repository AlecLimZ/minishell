NAME			=	minishell
SRC_DIR			=	SRC
OBJ_DIR			=	SRC/OBJS
INC_DIR			= 	INCLUDE
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
				@echo $(GREEN)"Successfully created ✅\n"$(DEF)
				@echo $(YELLOW)"Creating object files...⏳"$(DEF)
				@$(GCC) -I$(INC_DIR) -c $< -o $@
				@echo $(GREEN)"Successfully created ✅\n"$(DEF)

$(NAME):		$(OBJS)
				@echo $(YELLOW)"Creating the minishell...⏳"$(DEF)
				@$(GCC) $^ -o $@
				@echo $(GREEN)"Successfully created ✅\n"$(DEF)

norm:
				@echo $(YELLOW)"⏳Checking norminette...⏳"$(CYAN)
				norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*.c
				norminette -R CheckDefine $(INC_DIR)/*.h

clean:
				@rm -rf $(OBJ_DIR)
				@echo $(RED)"Object files & object folder GONE ☠️"$(DEF)

fclean:			clean
				@rm -rf $(NAME)
				@echo $(RED)"Executable file GONE ☠️"$(DEF)

re:				fclean all

.PHONY:			all clean fclean re
