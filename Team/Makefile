NAME			=	minishell
SRCS			=	SRC/*.c \
					SRC/parser/*.c \
					SRC/executor/*.c \
					SRC/inbuilt/*.c \
					SRC/heredoc/*.c
OBJ_DIR			=	SRC/OBJS
OBJS			=	$(SRCS:.c=.o)
READLINE		=	-I /usr/local/opt/readline/include
INC_DIR			= 	-I INCLUDE
LIBPATH			=	-I SRC/libft
HEADERS			=	$(READLINE) $(INC_DIR) $(LIBPATH)
LIBFT			=	SRC/libft/libft.a
LDFLAGS			=	/usr/local/opt/readline/lib/*.a -lncurses
LIBS			=	$(LIBFT) $(LDFLAGS)
GCC				= 	gcc -Wall -Wextra -Werror $(HEADERS)
DEF				=	"\033[0m"
YELLOW			=	"\033[1;33m"
GREEN			=	"\033[1;32m"
RED				=	"\033[0;31m"
CYAN			=	"\033[3;36m"

all:			$(NAME)

$(NAME):		$(OBJS)
				@echo $(YELLOW)"\nCreating \"OBJS\" folder...⏳"$(DEF)
				@mkdir -p $(OBJ_DIR)
				@echo $(CYAN)
				make bonus -C SRC/libft
				@echo $(GREEN)"Successfully created ✅\n"$(DEF)
				@echo $(YELLOW)"CMoving object files...⏳"$(DEF)
				@mv *.o $(OBJ_DIR)
				@echo $(GREEN)"Object files are now in directory OBJS ✅\n"$(DEF)
				@echo $(YELLOW)"Creating the minishell...⏳"$(DEF)
				@$(GCC) $(LIBS) $(OBJ_DIR)/*.o -o $(NAME)
				@echo $(GREEN)"Minishell successfully created ✅\n"$(DEF)

$(OBJS):		$(SRCS)
				@$(GCC) -c $(SRCS)

norm:
				@echo $(YELLOW)"⏳Checking norminette...⏳"$(CYAN)
				norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*.c
				norminette -R CheckDefine $(INC_DIR)/*.h

clean:
				@make fclean -C SRC/libft
				@rm -rf $(OBJ_DIR)
				@echo $(RED)"Object files & object folder GONE ☠️"$(DEF)

fclean:			clean
				@rm -rf $(NAME)
				@echo $(RED)"Executable file GONE ☠️"$(DEF)

re:				fclean all

.PHONY:			all clean fclean re
