/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:16:21 by gkitoko           #+#    #+#             */
/*   Updated: 2022/05/24 18:01:18 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		endgame(data, data->v_map);
	if (keysym == 119 || keysym == 65362)
		move(data, data->v_map, keysym);
	if (keysym == 115 || keysym == 65364)
		move(data, data->v_map, keysym);
	if (keysym == 97 || keysym == 65361)
		move(data, data->v_map, keysym);
	if (keysym == 100 || keysym == 65363)
		move(data, data->v_map, keysym);
	return (0);
}

int	render(t_data *data)
{
	if (data->v_win_ptr != NULL)
		displayer(data, data->v_map);
	else if (data->v_win_ptr == NULL)
		endgame(data, data->v_map);
	return (0);
}

int	destroy_window(t_data *data)
{
	free_double_str(data->v_map->v_map);
	mlx_destroy_image(data->v_mlx_ptr, data->v_locked.v_img);
	mlx_destroy_image(data->v_mlx_ptr, data->v_unlocked.v_img);
	mlx_destroy_image(data->v_mlx_ptr, data->v_floor.v_img);
	mlx_destroy_image(data->v_mlx_ptr, data->v_wall.v_img);
	mlx_destroy_image(data->v_mlx_ptr, data->v_player.v_img);
	mlx_destroy_image(data->v_mlx_ptr, data->v_collect.v_img);
	mlx_clear_window(data->v_mlx_ptr, data->v_win_ptr);
	mlx_destroy_window(data->v_mlx_ptr, data->v_win_ptr);
	mlx_destroy_display(data->v_mlx_ptr);
	free(data->v_mlx_ptr);
	data->v_mlx_ptr = NULL;
	exit(0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_map	map;

	map.v_game.v_move = 0;
	map.v_game.v_collect = 0;
	map.v_game.v_collect_nb = 0;
	checker(ac, av);
	data.v_mlx_ptr = mlx_init();
	if (data.v_mlx_ptr == NULL)
		quit(&data);
	init_window(&data, av, &map);
	init_img(&data);
	mlx_loop_hook(data.v_mlx_ptr, &render, &data);
	mlx_hook(data.v_win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.v_win_ptr, 17, KeyPressMask, &destroy_window, (void *)&data);
	mlx_loop(data.v_mlx_ptr);
}
