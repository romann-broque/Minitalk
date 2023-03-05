# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 13:20:37 by rbroque           #+#    #+#              #
#    Updated: 2023/03/05 21:46:36 by rbroque          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############
#### ENV ####
#############

SHELL = /usr/bin/bash

##############
#### NAME ####
##############

NAME = client

##############
#### SRCS ####
##############

PATH_SRCS += srcs/

# srcs/

MAIN += main.c

vpath %.c $(PATH_SRCS)

##############
#### OBJS ####
##############

PATH_OBJS = objs
OBJS_MAND = $(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))
OBJS_MAIN := $(patsubst %.c, $(PATH_OBJS)/%.o, $(MAIN))

#############
#### LIB ####
#############

LIB_FOLDER = libft/
LIBFT = $(LIB_FOLDER)/libft.a

###################
#### INCLUDES #####
###################

INCLUDES_LIB += $(LIB_FOLDER)/includes/
INCLUDES_LOCAL += includes/
INCLUDES += -I $(INCLUDES_LIB)
INCLUDES += -I $(INCLUDES_LOCAL)

#################
#### HEADERS ####
#################

HEADERS += minitalk.h

vpath %.h $(INCLUDES)

##################
#### MAKEFILE ####
##################

MAKEFILE = Makefile

#####################
#### COMPILATION ####
#####################

CC = cc

CFLAGS += -Wall
CFLAGS += -Wextra

ifneq ($(noerror), 1)
	CFLAGS += -Werror
endif

ifeq ($(everything), true)
	CFLAGS += -Weverything
endif

ifeq ($(debug), true)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
endif

#################
#### DISPLAY ####
#################

RED='\033[0;31m'
GREEN='\033[1;32m'
ORANGE='\033[0;33m'
YELLOW='\033[1;33m'
BLUE='\033[1;36m'
NC='\033[0m' # No Color

ifndef ECHO
T := $(words $(SRCS) $(MAIN))
T_BONUS := $(words $(SRCS_BONUS) $(BONUS_MAIN))
N := x
N_BONUS := x
C = $(words $N)$(eval N := x $N)
C_BONUS = $(words $(N_BONUS))$(eval N_BONUS := x $(N_BONUS))
ECHOC = echo -ne "\r\033[2K"
ECHO = $(ECHOC) $(ORANGE) "[`expr $C '*' 100 / $T`%]"
ECHO_BONUS = $(ECHOC) $(ORANGE) "[`expr $(C_BONUS) '*' 100 / $(T_BONUS)`%]"
endif

###############
#### RULES ####
###############

all: $(LIBFT) $(NAME)

# LIBFT

$(LIBFT):
	echo -e $(BLUE) "\n====> Building libft.a <===="$(NC)"\n"
	$(MAKE) -sC $(LIB_FOLDER)
	echo -e $(BLUE) "\n====> Building $(NAME) <===="$(NC)"\n"

# MINITALK

$(NAME): $(OBJS_MAND) $(OBJS_MAIN)
	$(CC) $(CFLAGS) $(OBJS_MAND) $(OBJS_MAIN) -o $(NAME) $(INCLUDES) $(LIBFT)
	$(ECHOC) $(GREEN) "--> $(NAME) COMPILED !"$(NC)"\n\n"

$(OBJS_MAIN): $(PATH_OBJS)/%.o: %.c $(HEADERS) $(MAKEFILE)
	$(ECHO) $(ORANGE) "Compiling $<"
	mkdir -p $(PATH_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) -O3

$(OBJS_MAND): $(PATH_OBJS)/%.o: %.c $(HEADERS) $(MAKEFILE)
	$(ECHO) $(ORANGE) "Compiling $<"
	mkdir -p $(PATH_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) -O3

run:
	$(MAKE) -s
	./$(NAME)

norm:
	norminette $(PATH_SRCS) $(INCLUDES_LOCAL) $(LIB_FOLDER)

clean:
	$(RM) -R $(PATH_OBJS)
	$(MAKE) -sC $(LIB_FOLDER) clean > /dev/null
	$(ECHOC) $(GREEN) "--> .o files deleted !"$(NC)"\n"

fclean: clean
	$(ECHOC) $(YELLOW) "Cleaning up $(NAME)..." $(NC)
	$(MAKE) -sC $(LIB_FOLDER) fclean > /dev/null
	$(RM) $(NAME)
	$(ECHOC) $(GREEN) "--> $(NAME) deleted !"$(NC)"\n"

re: fclean
	echo -e $(YELLOW) "\nRebuilding..." $(NC)
	$(MAKE) -s

.PHONY: all clean fclean re run
.SILENT: $(NAME) $(LIBFT) $(OBJS_MAND) $(OBJS_MAIN) run clean fclean re
