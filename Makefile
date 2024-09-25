########################################################################################################################
#                                                       BUILS SRC                                                      #
########################################################################################################################

#-----------------------------------------------------|  EXPAND  |-----------------------------------------------------#
EXPAND_DIR	:=	expand/
EXPAND_SRC	:=	expand.c\
				expand_utils.c\
				getvar.c
SRC			+=	$(addprefix $(EXPAND_DIR), $(EXPAND_SRC))

#---------------------------------------------------|  LINE_CHECK  |---------------------------------------------------#
LINE_CHECK_DIR	:=	line_check/
LINE_CHECK_SRC	:=	line_check.c\
					line_check_utils.c
SRC			+=	$(addprefix $(LINE_CHECK_DIR), $(LINE_CHECK_SRC))

#------------------------------------------------|  LOCATE_REDIRECTION  |----------------------------------------------#
LOCATE_REDIRECTION_DIR:=	locate_redirections/
LOCATE_REDIRECTION_SRC:=	redirections.c\
							redirections_utils.c\
							manage_here_doc.c
SRC			+= 	$(addprefix $(LOCATE_REDIRECTION_DIR), $(LOCATE_REDIRECTION_SRC))

#----------------------------------------------------|  SPLITER  |-----------------------------------------------------#
SPLITER_DIR:=	spliter/
SPLITER_SRC:=	spliter.c\
				utils.c
SRC			+=	$(addprefix $(SPLITER_DIR), $(SPLITER_SRC))

#-----------------------------------------------------|  SFE  |--------------------------------------------------------#
SFE_DIR:=	spliter_for_expand/
SFE_SRC:=	split_expand.c\
			sfe_utils.c
SRC			+=	$(addprefix $(SFE_DIR), $(SFE_SRC))

#----------------------------------------------------|  EXEC  |--------------------------------------------------------#
EXEC_DIR:=	exec/
EXEC_SRC:=	exec_cmd.c\
			handle_process.c\
			exec_utils.c\
			free_exit.c\
			here_doc.c\
			expand_hdoc.c\
			handle_redirections.c
SRC		+=	$(addprefix $(EXEC_DIR), $(EXEC_SRC))

#----------------------------------------------------|  UTILS  |-------------------------------------------------------#
UTILS_DIR:=	utils/
UTILS_SRC:=	utils.c\
			init.c\
			list_utils.c\
			address_utils.c\
			token_utils.c
SRC		+=	$(addprefix $(UTILS_DIR), $(UTILS_SRC))
SRC		+=	parsing.c

#----------------------------------------------------|  PROMPT  |------------------------------------------------------#
PROMPT_DIR:=	prompt/
PROMPT_SRC:=	prompt.c\
				utils.c
SRC		+=	$(addprefix $(PROMPT_DIR), $(PROMPT_SRC))

#----------------------------------------------------|  SIGNAL  |------------------------------------------------------#
SIGNAL_DIR:=	signal/
SIGNAL_SRC:=	signal.c
SRC		+=	$(addprefix $(SIGNAL_DIR), $(SIGNAL_SRC))

#-----------------------------------------------------|	BUILTINS |-----------------------------------------------------#
BUILTINS_DIR:= builtins/
BUILTINS_SRC:= cd.c\
			   echo.c\
			   env.c\
			   exit.c\
			   export.c\
			   pwd.c\
			   unset.c
SRC			+= $(addprefix $(BUILTINS_DIR), $(BUILTINS_SRC))

########################################################################################################################
#                                                     --VARIABLE--                                                     #
########################################################################################################################

SRCS_D		:=	src/

HEAD		:=	minishell.h
HEAD_D		:=	./inc/
HEAD_A		:=	$(addprefix $(HEAD_D), $(HEAD))

LIB_A		:=	libft/libft.a
LIB_D		:= ./libft
LIB_H		:= ./libft/libft.h

OBJS_D		:=	.objs/
OBJS		:= $(addprefix $(OBJS_D),$(SRC:%.c=%.o))
DEPS		:= $(OBJS:%.o=%.d)

NAME		:=	minishell

MAPS		:=	--suppressions=valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --verbose --show-mismatched-frees=yes --read-var-info=yes

RM		:=	rm -rf
CC		:=	cc
CFLAGS	:= -Wall -Wextra -Werror -I$(HEAD_D) -I$(LIB_D)
CPPFLAGS := -MMD -MP

########################################################################################################################
#                                                      --RULES--                                                       #
########################################################################################################################

all			:	$(NAME)

$(NAME)		:	$(OBJS_D) $(OBJS) $(LIB_A)
				@echo "${I_MAG}'MINISHELL'\t: ${RED} Work In Progress ◌ ${RESET}"
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./libft -lft -lreadline
				@echo "${I_MAG}'MINISHELL'\t: ${GREEN} done ✅ ${RESET}\n"
				@echo "${I_BLUE} Welcome in the final edition of"
				@echo "	███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     ";
				@echo "	████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     ";
				@echo "	██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     ";
				@echo "	██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     ";
				@echo "	██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗";
				@echo "	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝";
				@echo "${RESET}";

$(LIB_A)	:	FORCE
				@echo "${I_MAG}'OBJECTS'\t: ${GREEN} done ✅ ${RESET}\n"
				@echo "${I_MAG}'LIB_FT'\t: ${RED} Work In Progress ◌ ${RESET}"
				make -C libft/
				@echo "${I_MAG}'LIB_FT'\t: ${GREEN} done ✅ ${RESET}\n"


$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD_A)  $(LIB_H)
				$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJS_D)	:
				@echo "${I_MAG}'OBJECTS'\t: ${RED} Work In Progress ◌ ${RESET}"
				mkdir -p $(OBJS_D)
				mkdir -p $(OBJS_D)$(EXPAND_DIR)
				mkdir -p $(OBJS_D)$(LINE_CHECK_DIR)
				mkdir -p $(OBJS_D)$(LOCATE_REDIRECTION_DIR)
				mkdir -p $(OBJS_D)$(SPLITER_DIR)
				mkdir -p $(OBJS_D)$(SFE_DIR)
				mkdir -p $(OBJS_D)$(UTILS_DIR)
				mkdir -p $(OBJS_D)$(EXEC_DIR)
				mkdir -p $(OBJS_D)$(BUILTINS_DIR)
				mkdir -p $(OBJS_D)$(PROMPT_DIR)
				mkdir -p $(OBJS_D)$(SIGNAL_DIR)



leaks		:	all
				valgrind $(MAPS) ./$(NAME)

clean		:
				@echo "${I_MAG}'OBJECTS'\t: ${RED} deleted ❌ ${RESET}"
				$(RM) $(OBJS) $(OBJS_D)
				make -C libft/ clean

fclean		:	clean
				@echo "${I_MAG}'MINISHELL'\t: ${RED} deleted ❌ ${RESET}\n"
				$(RM) $(NAME)
				make -C libft/ fclean

re			:	fclean all

FORCE :

.PHONY		:	all leaks clean fclean re

-include $(DEPS)

########################################################################################################################
#                                                      --COLOR--                                                       #
########################################################################################################################

RED		=	\033[0;31m
GREEN	=	\033[0;32m
RESET	=	\033[0m
I_MAG	=	\033[3;35m
I_BLUE	=	\033[3;34m

