/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 17:01:28 by chuang            #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"
#include <math.h>

#define DISTVUE		1.0
#define LONGV		(LARGV * SCREEN_H / SCREEN_W)
#define LARGV		1.5

float	intersection(t_object *tmp, t_vector ray, t_vector pos)
{
	if (tmp->type == SPHERE)
			return (inter_sphere(pos, ray, *tmp));
		else if (tmp->type == PLANE)
			return (inter_plane(pos, ray, *tmp));
		else if (tmp->type == CONE)
			return (inter_cone(pos, ray, *tmp));
		else if (tmp->type == CYLINDER)
			return (inter_cylinder(pos, ray, *tmp));
	return (0.f);
}

t_color		check_collision(t_env *e, t_vector ray, t_vector pos)
{
	float		inter;
	float		test;
	t_object	*tmp;
	t_object	*item;

	tmp = e->scene->l_obj;
	inter = 150.f;
	while (tmp)
	{
		test = intersection(tmp, ray, pos);
		if (test > 0.0001f && test < inter)
		{
			inter = test;
			item = tmp;
		}
		tmp = tmp->next;
	}
	if (inter > 0.0001f && inter < 150.f)
	{
		return (ft_light(&(*e->lights), *item, mult_vector(ray, inter), e));
	}
	return ((t_color){0, 0, 0});
}

t_vector	ft_pos_hgv(t_env *e)
{
	t_vector pos_hgv;

	pos_hgv = mult_vector(e->cam.dir, DISTVUE);
	pos_hgv = sub_vector(pos_hgv, mult_vector(e->cam.h, LONGV / 2));
	pos_hgv = add_vector(pos_hgv, mult_vector(e->cam.d, LARGV / 2));
	//pos_hgv = add_vector(pos_hgv, e->cam.pos);
	return (pos_hgv);
}

t_vector	pixel_x_vector(t_env *e, t_vector pos_hgv, int x)
{
	t_vector	d;
	t_vector	v;

	d = mult_vector(e->cam.d, ((float)(LARGV / (float)SCREEN_W) * (float)x));
	v = sub_vector(mult_vector(pos_hgv, DISTVUE), d);
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
	t_vector	pos_hgv;
	t_vector	v_line_x;
	int			x;
	int			y;
	int			addr;
	t_env		e_load;

	e->cam.h = unit_vector((t_vector){0., 0., -1});
	e->cam.d = cross_vector(e->cam.dir, e->cam.h);
	pos_hgv = ft_pos_hgv(e);
	x = 1;
	new_img_in_old_env(&e_load, e);
	while (x < SCREEN_W)
	{
		v_line_x = pixel_x_vector(e, pos_hgv, x);
		y = 1;
		ft_loading_bar(x , &e_load);
		while (y < SCREEN_H)
		{
			ray = pixel_y_vector(e, v_line_x, y);
			ray = unit_vector(ray);
			addr = y * e->mlx_init.img.sizeline + x * e->mlx_init.img.opp;
			put_pixel_to_img(e, addr, check_collision(e, ray, e->cam.pos));
			y++;
		}
		x++;
	}
}
