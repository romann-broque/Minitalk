# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 13:20:37 by rbroque           #+#    #+#              #
#    Updated: 2023/03/07 14:52:02 by rbroque          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############
#### ENV ####
#############

SHELL = /usr/bin/bash

###############
#### TITLE ####
###############

TITLE = minitalk

##############
#### NAME ####
##############

NAME_SERVER = server
NAME_CLIENT = client

##############
#### SRCS ####
##############

PATH_SRCS += srcs/

# srcs/

MAIN_SERVER += server.c
MAIN_CLIENT += client.c
SRCS += send_signal.c

vpath %.c $(PATH_SRCS)

##############
#### OBJS ####
##############

PATH_OBJS = objs
OBJS_MAND = $(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))
OBJS_MAIN_SERVER := $(patsubst %.c, $(PATH_OBJS)/%.o, $(MAIN_SERVER))
OBJS_MAIN_CLIENT := $(patsubst %.c, $(PATH_OBJS)/%.o, $(MAIN_CLIENT))

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
T := $(words $(SRCS) $(MAIN_CLIENT) $(MAIN_SERVER))
N := x
C = $(words $N)$(eval N := x $N)
ECHOC = echo -ne "\r\033[2K"
ECHO = $(ECHOC) $(ORANGE) "[`expr $C '*' 100 / $T`%]"
endif

###############
#### RULES ####
###############

all: $(LIBFT) $(NAME_SERVER) $(NAME_CLIENT)

# LIBFT

$(LIBFT):
	echo -e $(BLUE) "\n====> Building libft.a <===="$(NC)"\n"
	$(MAKE) -sC $(LIB_FOLDER)
	echo -e $(BLUE) "\n====> Building $(TITLE) <===="$(NC)"\n"

# MINITALK

$(NAME_SERVER): $(OBJS_MAND) $(OBJS_MAIN_SERVER)
	$(CC) $(CFLAGS) $(OBJS_MAND) $(OBJS_MAIN_SERVER) -o $(NAME_SERVER) $(INCLUDES) $(LIBFT)
	$(ECHOC) $(GREEN) "--> $(NAME_SERVER) COMPILED !"$(NC)"\n\n"

$(NAME_CLIENT): $(OBJS_MAND) $(OBJS_MAIN_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_MAND) $(OBJS_MAIN_CLIENT) -o $(NAME_CLIENT) $(INCLUDES) $(LIBFT)
	$(ECHOC) $(GREEN) "--> $(NAME_CLIENT) COMPILED !"$(NC)"\n\n"

$(OBJS_MAIN_SERVER): $(PATH_OBJS)/%.o: %.c $(HEADERS) $(MAKEFILE)
	$(ECHO) $(ORANGE) "Compiling $<"
	mkdir -p $(PATH_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) -O3

$(OBJS_MAIN_CLIENT): $(PATH_OBJS)/%.o: %.c $(HEADERS) $(MAKEFILE)
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
	$(ECHOC) $(YELLOW) "Cleaning up $(TITLE)..." $(NC)
	$(MAKE) -sC $(LIB_FOLDER) fclean > /dev/null
	$(RM) $(NAME_SERVER)
	$(RM) $(NAME_CLIENT)
	$(ECHOC) $(GREEN) "--> $(NAME_SERVER) deleted !"$(NC)"\n"
	$(ECHOC) $(GREEN) "--> $(NAME_CLIENT) deleted !"$(NC)"\n"

re: fclean
	echo -e $(YELLOW) "\nRebuilding..." $(NC)
	$(MAKE) -s

.PHONY: all clean fclean re run
.SILENT: $(NAME_SERVER) $(NAME_CLIENT) $(LIBFT) $(OBJS_MAND) $(OBJS_MAIN_SERVER) $(OBJS_MAIN_CLIENT) run clean fclean re
