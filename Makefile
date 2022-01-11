# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 14:24:46 by gkgpteam          #+#    #+#              #
#    Updated: 2022/01/11 11:33:41 by gphilipp         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# <!-- pre='srcs/' path='./' match='*.c' exclude='main.c' pos='1' template='		{0} \' -->
SRC	  = main.c \
		dep/ft_strlen.c \
		list.c \
		app.c \
		minishell.c \


# <!-- pre='includes/' path='./' match='*.h' exclude='minishell.h' pos='1' template='		{0} \' -->
HDEP  = minishell.h \
		list.h \


HDEPS = $(addprefix $(HEAD), $(HDEP))

SRCS  = $(addprefix $(PRE), $(SRC))

OBJS  = $(SRCS:.c=.o)

PRE	  = ./srcs/

HEAD  = ./includes/

NAME  = minishell

CC    = gcc

CFLAGS = -Wall -Wextra -Werror

COMPILEFLAGS = -L$(LIBLIST) -llist

all: libs $(NAME)

%.o: %.c $(HDEPS)
	$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

LIBLIST = vendor/liblist/

libs: $(LIBLIST)liblist.a

list: $(LIBLIST)liblist.a

$(LIBLIST)liblist.a:
	make -C $(LIBLIST)

libs_clean:
	make -C $(LIBLIST) clean

libs_fclean: libs_clean
	make -C $(LIBLIST) fclean

maps:
	curl https://projects.intra.42.fr/uploads/document/document/6530/maps.zip > maps.zip
	tar -xf maps.zip
	chmod -x test_maps/*.fdf
	rm maps.zip

$(NAME): $(OBJS) $(HDEPS)
	$(CC) $(CFLAGS) -o $(NAME) $(COMPILEFLAGS) $(OBJS)

$(NAME)_debug: $(SRCS) $(HDEPS)
	$(CC) $(CFLAGS) -g -o $(NAME)_debug -I $(HEAD) $(COMPILEFLAGS) $(SRCS)

$(NAME)_sanitize: $(SRCS) $(HDEPS)
	$(CC) $(CFLAGS) -fsanitize=address -g -o $(NAME)_sanitize -I $(HEAD) $(COMPILEFLAGS) $(SRCS)

debug: $(NAME)_debug

sanitize: $(NAME)_sanitize

dclean: fclean
	rm -f *.out
	rm -rf *.dSYM
	rm -f $(NAME)_debug
	rm -f $(NAME)_sanitize
	find . -iname "*.o" -exec rm -i {} ";"

clean:
ifndef BONUS
		make -s BONUS=1 clean;
endif
	rm -f $(OBJS)

fclean: libs_fclean clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean dclean fclean debug sanitize libs list libs_clean libs_fclean re
