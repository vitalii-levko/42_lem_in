/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 13:07:59 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/14 18:13:54 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static int	valid_args(int ac, char **av, t_node **farm)
{
	if (ac == 1)
	{
		*farm = create_top_node(0, 0, 0, 0);
		if (!(*farm))
			exit(p_err(5, "Memory allocation failed", NULL, NULL));
		return (1);
	}
	if (check_opt(ac, av[1]))
	{
		save_opt(av[1], farm);
		return (1);
	}
	return (0);
}

static int	set_fd(t_node **farm)
{
	int			fd;

	if (farm && *farm && (*farm)->end)
	{
		fd = open("Lem_in.log", O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0755);
		if (fd == -1)
			return (p_err(1, "Cannot access the log file", "Lem_in.log", farm));
		else
			(*farm)->end = fd;
	}
	return (0);
}

static void	exit_main(t_node **farm, t_map **map, t_tree **path, t_node **res)
{
	if (farm && *farm)
		del_farm(farm);
	if (map && *map)
		del_map(map);
	if (path && *path)
	{
		del_path(path);
		free(*path);
		*path = NULL;
	}
	if (res && *res)
		del_res(res);
}

static int	args_exception(int ac, char **av)
{
	int			fd;
	int			ret;

	if (ac == 2 && !ft_strcmp("--help", av[1]))
	{
		fd = open("man/Lem_in.man", O_RDONLY);
		if (fd == -1)
			return (p_err(1, "Cannot access the man file", NULL, NULL));
		ret = p_help(0, 0, fd, '\0');
		close(fd);
		return (ret);
	}
	return (p_usage());
}

int			main(int ac, char **av)
{
	t_node		*farm;
	t_tree		*path;
	t_node		*res;
	t_map		*map;

	farm = NULL;
	if (valid_args(ac, av, &farm))
	{
		if (set_fd(&farm))
			return (exit_check(&farm, 1));
		map = NULL;
		res = NULL;
		path = NULL;
		if (parse_map(&farm, NULL, &map))
			return (exit_parse(&map, 2, &farm, NULL));
		if (bfs(&farm, &path, &res, NULL))
			return (exit_search(&farm, &map, &path, &res));
		print_map(&map, &farm);
		move_ants(&res, NULL, &farm, 1);
		exit_main(&farm, &map, &path, &res);
		return (0);
	}
	return (args_exception(ac, av));
}
