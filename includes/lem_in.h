/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 12:58:45 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/14 18:08:47 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <ncurses.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <string.h>
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/ft_printf.h"

typedef struct s_node	t_node;

typedef struct			s_list
{
	struct s_list		*next;
	t_node				*node;
}						t_list;

struct					s_node
{
	long long int		total;
	long long int		top;
	long long int		res;
	long long int		count;
	int					x;
	int					y;
	int					start;
	int					end;
	long long int		weight;
	long long int		ant;
	int					visited;
	long long int		id;
	char				*name;
	t_list				*rooms;
	t_node				*next;
};

typedef struct s_tree	t_tree;

typedef struct			s_step
{
	struct s_step		*next;
	t_tree				*unit;
}						t_step;

struct					s_tree
{
	t_node				*node;
	t_tree				*parent;
	t_step				*steps;
};

typedef struct			s_map
{
	char				*str;
	struct s_map		*next;
}						t_map;

typedef struct			s_act
{
	long long int		nb;
	char				*room;
	struct s_act		*next;
}						t_act;

int						exit_check(t_node **farm, int nb);

int						exit_parse(t_map **map, int nb, t_node **farm, \
						char **str);

int						exit_search(t_node **farm, t_map **map, t_tree **path, \
						t_node **res);

char					**exit_room(char ***arr, int *e);

void					del_queue(t_list **queue);

void					del_farm(t_node **farm);

void					del_map(t_map **map);

void					del_res(t_node **res);

void					del_arr(char ***arr);

void					del_path(t_tree **path);

void					insert_act(t_act **act, long long int nb, char *room, \
						t_node **farm);

void					print_act(t_act **act, t_act *curr, t_node **farm);

int						p_usage(void);

int						p_help(size_t i, size_t j, int fd, char c);

int						p_err(int ret, char *str, char *orig, t_node **farm);

void					malloc_err(int ret, char *orig, t_node **farm);

int						save_number_of_ants(int ret, char **str, t_map **map, \
						t_node **farm);

int						save_the_rooms(t_node **farm, char **str, int cmd, \
						t_map **map);

int						parse_link(t_node **farm, char **str);

int						parse_map(t_node **farm, char *str, t_map **map);

void					store_link(t_node **farm, char **arr);

void					store_map(t_map **map, char *str, t_node **farm);

int						if_connects(t_node **farm, t_node *curr, char **arr, \
						char **str);

int						is_comment(char *str);

int						is_command(char *str, int *cmd);

int						check_farm(t_node **farm, t_node *curr, int start, \
						int end);

char					**check_if_room(char *str, int cmd, t_node **farm, \
						int *e);

int						arr_len(char **arr);

int						is_num(char *str, char *orig, t_node **farm, int cs);

int						is_int(char *str, t_node **farm, int cs, \
						long long int val);

void					print_map(t_map **map, t_node **farm);

t_node					*create_top_node(long long int total, char e, char d, \
						char s);

int						check_opt(int ac, char *str);

void					save_opt(char *str, t_node **farm);

t_node					*get_parent(t_node **res, long long int id);

void					inspect_top(t_node **res, t_list *inner, t_act **act, \
						t_node **farm);

void					try_move_path(t_node **res, t_node **curr, \
						t_act **act, t_node **farm);

void					move_path(t_node **res, t_node *curr, t_act **act, \
						t_node **farm);

void					move_ants(t_node **res, t_act *act, t_node **farm, \
						long long int n);

void					try_move_it_move_it(t_tree **unit, t_list **queue, \
						t_node **farm);

void					try_move_it(t_tree **unit, t_list **queue, \
						t_node **farm);

int						bfs(t_node **farm, t_tree **path, t_node **res, \
						t_list *queue);

void					mark_top(t_node **res, t_tree **path);

t_tree					*get_new_start(t_node **farm, t_tree **path, \
						t_list **q, t_node **res);

t_tree					*move_start(t_tree **path, t_list **queue, \
						t_node **res, t_node **farm);

int						visit_queue(t_node **farm, t_list **queue, \
						t_tree **unit, t_node **res);

void					push_queue(t_list **queue, t_node **node, \
						t_node **farm);

int						is_paired(t_list **queue, t_list *rooms);

t_tree					*create_unit(t_node **node, t_tree **parent);

void					append_step(t_tree **unit, t_node **node, \
						t_node **farm);

void					end_point(t_tree **unit, t_node **node, t_node **res, \
						t_node **farm);

t_node					*create_node(char *name, long long int x, \
						long long int y, int cmd);

void					reset_it(t_node **farm);

#endif
