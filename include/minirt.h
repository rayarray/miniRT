/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:02:44 by rleskine          #+#    #+#             */
/*   Updated: 2023/11/18 17:53:15 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define TITLE "miniRT"
# define WIDTH	512
# define HEIGHT	512
# include "scene.h"
# include "MLX42.h"

struct s_minirt
{
	struct s_scene	*scene;
	mlx_t			*mlx;
	mlx_image_t		*image;
};

#endif