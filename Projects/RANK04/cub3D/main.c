/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:25:18 by dcaetano          #+#    #+#             */
/*   Updated: 2023/12/10 14:24:20 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = (t_cub *)malloc(sizeof(t_cub));
	if (!cub)
		return (1);
	cub_check_input(cub, argc, argv);
	cub_check_file_content(cub->config.data.filename, cub);
	cub_set_config(cub, cub->config.data.data, -1);
	cub_exit(cub);
	return (0);
}
