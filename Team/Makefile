NAME		=	minishell
GCC			=	gcc -Wall -Wextra -Werror 
#  -fsanitize=address -g3
SRC			=	main.c
SRC_DIR		= 	SRC/
SRCS		=	$(addprefix $(SRC_DIR), $(SRC))

PARSING		=	check_pipe.c expand.c expand_utils.c parser.c parser_redirect.c split_cmds.c remove_quote.c utils.c cleanup.c
PARSING_DIR	=	SRC/parser/
PARSINGS 	=	$(addprefix $(PARSING_DIR), $(PARSING))

INBUILT		=	extra1.c extra2.c extra3.c ft_cdecho.c ft_export.c ft_inbuilts.c ft_path.c ft_unset.c extra4.c ft_exit.c
INBUILT_DIR	=	SRC/inbuilt/
INBUILTS	=	$(addprefix $(INBUILT_DIR), $(INBUILT))

HEREDOC		=	ft_create.c ft_get_env.c ft_heredoc.c ft_env2.c ft_get_env2.c
HEREDOC_DIR	=	SRC/heredoc/
HEREDOCS	=	$(addprefix $(HEREDOC_DIR), $(HEREDOC))

EXEC		=	exec.c redirect.c search_path.c set_args.c dup_utils.c exit_status.c
EXEC_DIR	=	SRC/executor/
EXECS		=	$(addprefix $(EXEC_DIR), $(EXEC))

READLINE	=	-I /usr/local/opt/readline/include
READLINE	=	-I /usr/local/opt/readline/include
INC_DIR		=	-I INCLUDE
INC_LIB		=	-I SRC/libft
INCLUDE 	=	$(READLINE) $(INC_DIR) $(INC_LIB)

OBJS_S		=	$(SRCS:%.c=%.o)
OBJS_P		=	$(PARSINGS:%.c=%.o)
OBJS_I		=	$(INBUILTS:%.c=%.o)
OBJS_H		=	$(HEREDOCS:%.c=%.o)
OBJS_E		=	$(EXECS:%.c=%.o)
OBJS		= 	$(OBJS_S) $(OBJS_P) $(OBJS_I) $(OBJS_H) $(OBJS_E)

DEF			= 	"\033[0m"
YELLOW		=	"\033[1;33m"
GREEN		=	"\033[1;32m"
RED			=	"\033[0;31m"
CYAN		=	"\033[3;36m"

LIBS		=	SRC/libft/libft.a 
READ_LIB	= /usr/local/opt/readline/lib/*.a -lncurses
#LIBS		=	SRC/libft/libft.a -lreadline

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBS)
			@echo $(GREEN)"\nObject files successfully created ✅"$(DEF)
			@echo $(GREEN)"\nLibft successfully created ✅"$(DEF)
#			@$(GCC) $(OBJS_S) $(OBJS_P) $(OBJS_I) $(OBJS_H) $(OBJS_E) $(INCLUDE) $(LIBS) -o $(NAME)
			@$(GCC) $(LIBS) $(OBJS) $(INCLUDE) -o $(NAME) $(READ_LIB)
			@echo $(GREEN)"\nMinishell program successfully created ✅"$(DEF)


$(LIBS):
			@echo $(YELLOW)
			@make -C SRC/libft

.c.o:
			@$(GCC) $(INCLUDE) -o $@ -c $<

clean:
			@make fclean -C SRC/libft
			@rm $(OBJS)
			@echo $(RED)"Object files & object folder GONE ☠️"$(DEF)

fclean: 	clean
			@rm -rf $(NAME)
			@echo $(RED)"Executable file GONE ☠️"$(DEF)

re: 		fclean all

.PHONY: 	clean fclean all re
