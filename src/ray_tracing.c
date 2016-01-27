/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 17:01:28 by chuang            #+#    #+#             */
/*   Updated: 2016/01/27 16:40:13 by chuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>

#define DISTVUE		1.0
#define LONGV		1.05
#define LARGV		1.5

t_color		check_collision(t_env *e, t_vector ray)
{
	float		inter;
//	float		test;
	t_vector	normal;
//	void		*item;
//	t_sphere	sphere = {(t_vector){8, 1, 1}, 1, NULL};
	t_plane		plane = {(t_vector){9, 0, 0},(t_vector){ -1, 4, 0},(float) 0, NULL};

//APPEL DES LUMIERES	
/*
	inter = 20; //MAX_VISION(e->cam.pos.z);
	//TANT qu'il a des objets test
	while (e->obj)// ** TO DO
	{
		inter = inter_sphere(e->cam, ray, sphere);
		test = inter_plane(e->cam, ray, plane);
		if (inter < test)
		{
			inter = test;
			item = // **ITEM IN COLLISION WITH RAY
		}
	}*/
//	inter = inter_sphere(e->cam, ray, sphere);
	inter = inter_plane(e->cam, ray, plane);
	if (inter > 0.0f) //&& inter < (float)MAX_VISION(e->cam.pos.z))
	{
		normal = plane.normal; // call assigning normal function
//		normal = normal_sphere(sphere, ray, inter);
//		printf("%f, %f, %f\n", normal.x, normal.y, normal.z);
		return (diffuse_light(*e->lights, (t_color) {255,255,0}, normal, mult_vector(ray,inter)));
	}
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
	e->cam.h = (t_vector){0., 0., -1};
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
