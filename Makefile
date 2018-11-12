# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/30 13:19:58 by vlevko            #+#    #+#              #
#    Updated: 2018/07/14 18:10:30 by vlevko           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = lem_in.c \
	srcs/exits.c \
	srcs/dels.c \
	srcs/del_path_arr.c \
	srcs/acts.c \
	srcs/help_usage.c \
	srcs/errs.c \
	srcs/nums.c \
	srcs/rooms.c \
	srcs/links.c \
	srcs/parse.c \
	srcs/store_link_map.c \
	srcs/checks.c \
	srcs/check_room.c \
	srcs/check_link.c \
	srcs/ext_main.c \
	srcs/ext_move.c \
	srcs/bfs.c \
	srcs/bfs_moves.c \
	srcs/bfs_ext_move.c \
	srcs/bfs_queue.c \
	srcs/bfs_ext_queue.c \
	srcs/bfs_paths.c \
	srcs/bfs_res.c \
	srcs/ext_bfs.c \
	srcs/move_path.c \
	srcs/moves.c

OBJ = $(SRC:.c=.o)

NAME = lem-in

CFLAGS = -Wall -Wextra -Werror

LPATH = libft/

LFLAGS = -L libft/ -lft

LNFLAGS = -lncurses

CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LPATH) --no-print-directory
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LFLAGS) $(LNFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LPATH) --no-print-directory
	@/bin/rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LPATH) --no-print-directory
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
