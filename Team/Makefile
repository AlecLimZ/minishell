# NAME		=	minishell
# #GCC			=	gcc -Wall -Wextra -Werror -fsanitize=address -g3
# GCC			=	gcc -Wall -Wextra -Werror
# SRC			=	main.c
# SRC_DIR		= 	SRC/
# SRCS		=	$(addprefix $(SRC_DIR), $(SRC))

# PARSING		=	check_pipe.c expand.c expand_utils.c parser.c parser_redirect.c split_cmds.c remove_quote.c utils.c cleanup.c
# PARSING_DIR	=	SRC/parser/
# PARSINGS 	=	$(addprefix $(PARSING_DIR), $(PARSING))

# INBUILT		=	extra1.c extra2.c extra3.c ft_cdecho.c ft_export.c ft_inbuilts.c ft_path.c ft_unset.c
# INBUILT_DIR	=	SRC/inbuilt/
# INBUILTS	=	$(addprefix $(INBUILT_DIR), $(INBUILT))

# HEREDOC		=	ft_create.c ft_get_env.c ft_heredoc.c ft_env2.c ft_get_env2.c
# HEREDOC_DIR	=	SRC/heredoc/
# HEREDOCS	=	$(addprefix $(HEREDOC_DIR), $(HEREDOC))

# EXEC		=	exec.c redirect.c search_path.c set_args.c dup_utils.c
# EXEC_DIR	=	SRC/executor/
# EXECS		=	$(addprefix $(EXEC_DIR), $(EXEC))

# READLINE	=	-I /usr/local/opt/readline/include
# READLINE	=	-I /usr/local/opt/readline/include
# INC_DIR		=	-I INCLUDE
# INC_LIB		=	-I SRC/libft
# INCLUDE 	=	$(READLINE) $(INC_DIR) $(INC_LIB)

# OBJS_S		=	$(SRCS:%.c=%.o)
# OBJS_P		=	$(PARSINGS:%.c=%.o)
# OBJS_I		=	$(INBUILTS:%.c=%.o)
# OBJS_H		=	$(HEREDOCS:%.c=%.o)
# OBJS_E		=	$(EXECS:%.c=%.o)

# DEF			= 	"\033[0m"
# YELLOW		=	"\033[1;33m"
# GREEN		=	"\033[1;32m"
# RED			=	"\033[0;31m"
# CYAN		=	"\033[3;36m"

# LIBS		=	SRC/libft/libft.a /usr/local/opt/readline/lib/*.a -lncurses
# #LIBS		=	SRC/libft/libft.a -lreadline

# all:		$(NAME)

# $(NAME):	$(OBJS_S) $(OBJS_P) $(OBJS_I) $(OBJS_H) $(OBJS_E) $(LIBS)
# 			@echo $(GREEN)"\nObject files successfully created ✅"$(DEF)
# 			@echo $(GREEN)"\nLibft successfully created ✅"$(DEF)
# #			@$(GCC) $(OBJS_S) $(OBJS_P) $(OBJS_I) $(OBJS_H) $(OBJS_E) $(INCLUDE) $(LIBS) -o $(NAME)
# 			@$(GCC) $(LIBS) $(OBJS_S) $(OBJS_P) $(OBJS_I) $(OBJS_H) $(OBJS_E) $(INCLUDE) -o $(NAME)
# 			@echo $(GREEN)"\nMinishell program successfully created ✅"$(DEF)
# 			@mkdir -p OBJS
# 			@mv SRC/*.o OBJS
# 			@mv SRC/*/*.o OBJS
# 			@mv OBJS SRC

# $(LIBS):
# 			@echo $(YELLOW)
# 			@make bonus -C SRC/libft

# .c.o:
# 			@$(GCC) $(INCLUDE) -o $@ -c $<

# clean:
# 			@make fclean -C SRC/libft
# 			@rm -rf SRC/OBJS
# 			@echo $(RED)"Object files & object folder GONE ☠️"$(DEF)

# fclean: 	clean
# 			@rm -rf $(NAME)
# 			@echo $(RED)"Executable file GONE ☠️"$(DEF)

# re: 		fclean all

# .PHONY: 	clean fclean all re

NAME	= minishell
incs	= -I includes -I libft -I readline-7.0/include
objs	= SRC/main.o \
		  SRC/executor/dup_utils.o \
		  SRC/executor/exec.o \
		  SRC/executor/exit_status.o \
		  SRC/executor/redirect.o \
		  SRC/executor/search_path.o \
		  SRC/executor/set_args.o \
		  SRC/heredoc/ft_create.o \
		  SRC/heredoc/ft_env2.o \
		  SRC/heredoc/ft_get_env.o \
		  SRC/heredoc/ft_get_env2.o \
		  SRC/heredoc/ft_heredoc.o \
		  SRC/inbuilt/extra1.o \
		  SRC/inbuilt/extra2.o \
		  SRC/inbuilt/extra3.o \
		  SRC/inbuilt/ft_cdecho.o \
		  SRC/inbuilt/ft_export.o \
		  SRC/inbuilt/ft_inbuilts.o \
		  SRC/inbuilt/ft_path.o \
		  SRC/inbuilt/ft_unset.o \
		  SRC/parser/check_pipe.o \
		  SRC/parser/cleanup.o \
		  SRC/parser/expand_utils.o \
		  SRC/parser/expand.o \
		  SRC/parser/parser_redirect.o \
		  SRC/parser/parser.o \
		  SRC/parser/remove_quote.o \
		  SRC/parser/split_cmds.o \
		  SRC/parser/utils.o

libft	= SRC/libft/libft.a
# LDLIBS = /usr/local/opt/readline/lib/*.a -lncurses
LDLIBS	= readline-7.0/lib/*.a -lncurses
LDFLAGS = -fsanitize=address -g3
CFLAGS	= -Wall -Wextra -Werror $(LDFLAGS) $(incs)


all: $(NAME)

$(NAME): $(objs) $(libft)
	$(LINK.o) $^ $(LDLIBS) -o $@

clean:
	rm -f $(objs)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(libft):
	make -C libft

$(objs): |readline-7.0

readline-7.0:
	curl -LO https://ftp.gnu.org/gnu/readline/readline-7.0.tar.gz
	# curl -LO https://ftp.gnu.org/gnu/readline/readline-6.0.tar.gz
	@echo "750d437185286f40a369e1e4f4764eda932b9459b5ec9a731628393dd3d32334  readline-7.0.tar.gz" | shasum -c
	@tar xzf readline-7.0.tar.gz
	@echo Compiling libreadline...  \
	&& cd $@ \
	&& ./configure --prefix=$$(pwd) &>/dev/null \
	&& make &>/dev/null \
	&& make install &>/dev/null
	@rm readline-7.0.tar.gz

.PHONY: all clean fclean re h b x v test

norm:
	norminette libft
	norminette src
	norminette includes

h help:
	@echo 'make x => remove AddressSanitizer to work with leaks'
	@echo 'make b => compare bash'
	@echo 'make v => valgrind test'
	@echo 'make t => test result'

b:
	PS1='[$$?]$$(pwd)> ' bash

x: $(NAME)
	make re LDFLAGS="-g3"
	cp minishell x

v: x
	valgrind --leak-check=full --show-leak-kinds=all \
	--track-origins=yes --trace-children=yes ./minishell
	# --suppressions=readline.supp \
	# --gen-suppressions=all --log-file=minimalraw.log \
	# leaks -q -atExit -- ./minishell -c 'echo $$?'
	# valgrind --leak-check=yes ./minishell -c 'echo $$?'

t:
	less -r minishell_test.out
	less -r minishell_tester.out

test: x
	git clone https://github.com/thallard/minishell_tester.git test
	cd test && bash test.sh --valgrind
