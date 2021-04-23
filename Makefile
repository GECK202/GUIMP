# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/23 17:12:18 by vkaron            #+#    #+#              #
#    Updated: 2020/09/15 12:32:20 by jthuy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re, libr

PROGRAM_NAME = guimp

FLAGS =	-Wall -Wextra -Werror -g

FILES =		main player init music service_stuff act_sdl
			
S_DIR =		src

O_DIR =		obj

H_DIR =		include

O_FILES =	$(addprefix $(O_DIR)/, $(addsuffix .o, $(FILES)))

H_FILE =	$(H_DIR)/guimp.h

LIBS = 		-Llibft -lft \
			-lm \
			-lpthread

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	H_FIND =-I libft \
			-I $(H_DIR) \
			-I $(shell sdl2-config --prefix)/include/SDL2

	FRAME =	-lSDL2 \
			-lSDL2_mixer \
			-lSDL2_image \
			-lSDL2_ttf
			
	ECHO_FLAG = -ne
endif
ifeq ($(UNAME_S),Darwin)
	H_FIND =-I libft \
			-I include \
			-I Frameworks/SDL2.framework/Headers\
			-I Frameworks/SDL2_image.framework/Headers\
			-I Frameworks/SDL2_ttf.framework/Headers\
			-I Frameworks/SDL2_mixer.framework/Headers\
			-F Frameworks/

	FRAME =	-F ./Frameworks/ \
			-framework SDL2 \
			-framework SDL2_image \
			-framework SDL2_ttf \
			-framework SDL2_mixer \
			-rpath Frameworks/
			
	ECHO_FLAG = -n
endif	

all: libr $(PROGRAM_NAME)

libr:
	@make -C libft/ all

$(PROGRAM_NAME): $(O_FILES)
	@gcc $(FLAGS) -o $@ $^ $(LIBS) $(FRAME)
	$(info  )
	$(info # MAKE COMPLETE #)

$(O_DIR)/%.o: $(S_DIR)/%.c $(H_FILE)
	@mkdir -p $(O_DIR)
	@gcc $(FLAGS) -c $< -o $@ $(H_FIND)
	@echo $(ECHO_FLAG) '='

clean:
	make -C libft/ clean
	rm -rf $(O_DIR)

fclean : clean
	make -C libft/ fclean
	rm -f $(PROGRAM_NAME)

re: fclean all
