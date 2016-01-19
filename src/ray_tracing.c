/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 17:01:28 by chuang            #+#    #+#             */
/*   Updated: 2016/01/19 20:28:55 by chuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"
#include <math.h>

#define DISTVUE		1.0
#define LONGV		0.375
#define LARGV		0.5

#include <stdio.h>

t_color		check_collision(t_env *e, t_vector ray)
{
	float	inter;

	(void)e;
	inter = inter_sphere(e->cam, ray,
						(t_sphere){(t_vector){10.,0.,0.}, 1, NULL});

	if (inter > 0.0f)
		return ((t_color) {255,255,0});
	return ((t_color){0,0,0});
}

t_vector	ft_posHGV(t_env *e)
{
	t_vector posHGV;

	posHGV = mult_vector(e->cam.dir, DISTVUE);
	posHGV = sub_vector(posHGV, mult_vector(e->cam.h, LONGV / 2));
	posHGV = add_vector(posHGV, mult_vector(e->cam.d, LARGV / 2));
	return (posHGV);
}


t_vector	pixel_x_vector(t_env *e, t_vector posHGV, int x)
{
	t_vector	d;
	t_vector	v;

	d = mult_vector(e->cam.d, ((float)(LARGV / (float)SCREEN_W) * (float)x));
	v = sub_vector(mult_vector(posHGV, DISTVUE), d);
	return (v);
}

t_vector	pixel_y_vector(t_env *e, t_vector v_per_x, int y)
{
	t_vector	v;
	t_vector	h;
	
	h = mult_vector(e->cam.h, ((float)(LONGV / (float)SCREEN_H) * (float)y));
	v = add_vector(v_per_x, h);
	return (v);
}


void		ft_render(t_env *e)
{
	t_vector	ray;
	t_vector	posHGV;
	t_vector	v_line_x;
	int			x;
	int			y;
	int			addr;

	e->cam.pos = (t_vector){0.,0.,0.};
	e->cam.h = (t_vector){0., 0., 1};
	e->cam.dir = (t_vector){1., 0., 0.};
	e->cam.d = cross_vector(e->cam.dir, e->cam.h);
	posHGV = ft_posHGV(e);
	x = 1;
	while (x < SCREEN_W)
	{
		v_line_x = pixel_x_vector(e, posHGV, x);
		y = 1;
		while (y < SCREEN_H)
		{
			ray = pixel_y_vector(e, v_line_x, y);
			ray = unit_vector(ray);
			addr = y * e->mlx_init.img.sizeline + x * e->mlx_init.img.opp;
			put_pixel_to_img(e, addr, check_collision(e, ray));
			y++;
		}
		x++;
	}
}
