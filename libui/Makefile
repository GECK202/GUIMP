# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/23 17:12:18 by vkaron            #+#    #+#              #
#    Updated: 2020/09/14 14:18:55 by vkaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

FLAGS = -Wall -Wextra -Werror

C_FILES = 	lgui.c
 
O_FILES = $(C_FILES:.c=.o)

H_DIR = -I ./ \
		-I ../libft \
		-I ../Frameworks/SDL2.framework/Headers\
		-I ../Frameworks/SDL2_image.framework/Headers\
		-I ../Frameworks/SDL2_ttf.framework/Headers\
		-I ../Frameworks/SDL2_mixer.framework/Headers\
		-F ../Frameworks/

NAME = libui.a

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	ECHO_FLAG = -ne
endif
ifeq ($(UNAME_S),Darwin)
	ECHO_FLAG = -n
endif

all: $(NAME)

$(NAME): $(O_FILES)
	@ar rc $(NAME) $(O_FILES)

%.o: %.c libui.h
	@gcc	$(FLAGS)  -c $< $(H_DIR)
	@echo $(ECHO_FLAG) '='

clean:
	rm -f $(O_FILES)

fclean : clean
	rm -f $(NAME)

re: fclean all
