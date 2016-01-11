/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 17:59:10 by mguillon          #+#    #+#             */
/*   Updated: 2016/01/11 18:56:49 by chuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
#include <mlx.h>
#include <math.h>
#include "libft.h"

typedef struct		t_env
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				sizeline;
	int				endian;
}					s_env;

typedef	struct		t_vectorr
{
	float			x;
	float			y;
	float			z;
}					s_vector;

typedef struct 		t_sphere
{
	s_vector		pos;
	int				rayon;
}					s_sphere;

typedef struct 		t_cone
{
	t_vector		pos;
	int				rayon;	
	int				hauteur;
}					s_cone;

typedef struct 		t_cylindre
{
	int				origin_x;
	int				origin_y;
	int				origin_z;
	int				rayon;	
	int				hauteur;
}					s_cylindre;

typedef	struct		t_plan
{
	int				origin_x;
	int				origin_y;
	int				origin_z;
	s_vecteur		v_plan;
}					s_plan;

void	new_image(t_env *e);
int		main(int argc, char **argv);
int		key_hook(int keycode, t_env *e);
