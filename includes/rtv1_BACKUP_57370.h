/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 17:59:10 by mguillon          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2016/02/16 15:25:26 by mgras            ###   ########.fr       */
=======
/*   Updated: 2016/02/16 15:15:01 by chuang           ###   ########.fr       */
>>>>>>> b82e6964b59101932a3ac51331e929a0fb0f13be
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "../libft/includes/libft.h"

# define SCREEN_W		1280
# define SCREEN_H		960

# define AMBIANT		0.4
# define MAX_VISION(h)		(3570 + sqrt((h)))
# define PI			3.14159265
# define RATIO		(PI / 180)

# define BUF_SIZE 10

typedef	struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef	struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef	enum {SPHERE, PLANE, CYLINDER, CONE} t_type;

typedef	struct	s_object
{
	void				*next;
	t_type				type;
	t_color				color;
	t_vector			pos;
	t_vector			dir;//cylinder cone
	t_vector			normal;//plan
	float				radius;//sphere cone cylindre
	float				height;//cone cylindre
	float				shine;//brillance
	float				reflect; // reflexion
	float				checkered;//dallage_carreaux
}						t_object;

typedef struct		s_light
{
	t_vector		pos;
	t_vector		dir;
	t_color			color;
	float			intensity;
	struct s_light	*next;
}					t_light;

typedef struct	s_scene
{
	void		*l_obj;
	t_light		*light;
}				t_scene;

typedef struct	s_cam
{
	t_vector	pos;
	t_vector	dir;
	t_vector	h;
	t_vector	d;
}				t_cam;

typedef struct	s_img
{
	void		*img_ptr;
	char		*img_data;
	int			bpp;
	int			opp;
	int			sizeline;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct	s_mlx_init
{
	t_img		img;
	void		*mlx;
	void		*win;
}				t_mlx_init;

typedef struct	s_env
{
	t_mlx_init	mlx_init;
	t_scene		*scene;
	t_light		*lights;
	t_cam		cam;
}				t_env;

typedef struct		s_node
{
	int							beg;
	char						type;
	struct				 	s_node	*next;
}									t_node;

typedef struct 		s_parse
{
	char 						*name;
	t_node					*nodes;
	t_object				*obj;
}									t_parse;

/*
**	main.c
*/
void			ft_initialize(t_env *e);

/*
**	initialization.c
*/
void			ft_exit(char *str, int n);
void			quit_and_free(t_env *e);
void			init_env(t_env *e, char *av);
int				expose_hook(t_env *e);
void			init_and_draw(t_env *e, char *av);
void			init_obj(t_object *node);
void			init_scene(t_env *e);
void			new_img_in_old_env(t_env *e, t_env *old);

/*
**	premade_objects.c
*/
void			set_list_obj(t_env *e);

/*
**	ray_tracing.c
*/
void			ft_render(t_env *e);

/*
**	hook_functions.c
*/
int				expose_hook(t_env *e);
int				key_press_hook(int keycode, t_env *e);

/*
**	graphics_tools.c
*/
void			put_pixel_to_img(t_env *e, int addr, t_color color);
void			set_color_from_img(t_color *color, char *data, int addr);
void			set_color_from_rgb(t_color *color, int r, int g, int b);
void			get_true_color_value(t_color *color);
void			blend_color(t_color *c, t_color c1, t_color c2, double percent);

/*
**	----------> USER INPUT SYSTEM <-----
*/
/*
**	create_scene.c
*/
void			create_scene(t_env *e);

/*
**	add_shape.c
*/
void			input_sphere(t_env *e);
void			input_plane(t_env *e);
void			input_cylinder(t_env *e);
void			input_cone(t_env *e);

/*
**	assign_color.c
*/
void			color(t_color *color);
void			color_choice(t_color *color);

/*
**	create_object.c
*/
t_object		*create_object(t_env *e);

/*
**	infos_shapes.c
*/
void			radius(t_object *node);
void			height(t_object *node);
void			constant(t_object *node);
//int			count_objects(t_env *e);

/*
**	input_normal.c
*/
void			assign_normal(t_object *node, char *str);//static ?
void			normal(t_object *node);

/*
**	input_vectors_clean.c
*/
char			**remove_spaces(char *str, int i, char **clean);//static ?
void			separators(char *str);//static ?
char			*no_more_spaces(char *str);

/*
**	input_verification.c
*/
int				is_slashes_and_digits(char *str);//static ?
int				is_vector(char *str);//static ?
int				correct_input(char *str);

/*
**	input_position.c
*/
char			*cut_pos(char *str, int i);
int				check_values(char *str, int min, int max);
void			assign_pos(t_object *node, char *str);
void			position(t_object *node);

/*
**	----------> GEOMETRY <-----
*/
/*
**	trigo.c
*/
float			d_cos(float angle);
float			d_sin(float angle);
float			d_acos(float value);

/*
**>----------> INTERSECTION <-----
*/

/*
**	sphere.c
*/
t_object		set_sphere(t_vector pos,float radius);
float			inter_sphere(t_vector cam_pos, t_vector ray, t_object sphere);
t_vector		normal_sphere(t_vector cam, t_object obj, t_vector ray);

/*
**	plane.c
*/
t_object		set_plane(t_vector pos, t_vector normal);
float			inter_plane(t_vector cam_pos, t_vector ray, t_object plane);
t_vector		normal_plane(t_object obj, t_vector ray);

/*
**	cylinder.c
*/
t_object		set_cylinder(t_vector pos, t_vector dir, float radius,float height);
float			inter_cylinder(t_vector cam_pos, t_vector ray, t_object cylinder);
t_vector		normal_cylinder( t_vector cam, t_object obj, t_vector ray);

/*
**	cone.c
*/
t_object		set_cone(t_vector pos, t_vector dir, float radius,float height);
float			inter_cone(t_vector cam_pos, t_vector ray, t_object obj);
t_vector		normal_cone(t_vector cam, t_object obj, t_vector ray);

/*
**>----------> LIGHTS <-----
*/

/*
**	light.c
*/
float			diffuse_light(t_light light, t_object item, t_vector inter_ray, t_env *e);
t_vector		calc_normal(t_vector pos, t_object item, t_vector inter_ray);
float			specular_light(t_light light, t_object item, t_vector inter_ray, t_env *e);
t_color			ft_light (t_light *lights, t_object item, t_vector inter_ray, t_env *e);
void			init_lights(t_env *e);

/*
**	reflection_light.c
*/
t_color			reflection(t_light light, t_object item, t_vector inter_ray, t_env *e);

/*
**	ray_tracing.c
*/
t_color			check_collision(t_env *e, t_vector ray, t_vector pos);

/*
**	vector.c
*/
t_vector		set_vector(t_vector v, float x, float y, float z);
float			dotpro_vector(t_vector a, t_vector b);
float			norm_vector(t_vector v);
t_vector		unit_vector(t_vector v);
float			sq_vector(t_vector a);

/*
**	vector2.c
*/
t_vector		add_vector(t_vector v, t_vector u);
t_vector		sub_vector(t_vector v, t_vector u);
t_vector		cross_vector(t_vector v, t_vector u);
t_vector		mult_vector(t_vector a, float m);

/*
**>----------> COLOR AND TEXTURE <-----
*/

/*
**	texture.c
*/
t_color			checkered_floor(t_vector coord);

/*
**	color.c
*/
t_color			add_color(t_color a, t_color b);
t_color			mult_color(t_color color, float coef);

/*
**>----------> PARSER <-----
*/

/*
**	parser
*/
void				open_file(char *file, t_parse *parse, t_env *e);
float				ft_atof(char *number);
void				assign_color(t_color *color, char *str);
t_object		*create_object();
void				assign_normal(t_object *node, char *str);
void				assign_pos(t_object *node, char *str);
int					check_values(char *str, int min, int max);
char				*cut_pos(char *str, int i);
void				separators(char *str);
char				*no_more_spaces(char *str);
char				**remove_spaces(char *str, int i, char **clean);
int					correct_input(char *str);
int					is_vector(char *str);
int					is_slashes_and_digits(char *str);
void				init_obj(t_object *node);
t_vector		set_vector(t_vector v, float x, float y, float z);
void				print_nodes(t_node *nodes);
void				print_result(t_parse *parse);
char				*recup_name(t_node *node, char *get, char c);
int					get_size(char *get, int i, char c);
void				set_object_type(char *name, t_object *obj);
void				set_object_param(char *value, char *data, t_object *obj);
void				error_in_parse(char *str);
void				get_instr(char *get, t_parse *parse, t_env *e);

/*
**	ft_loading_bar.c
*/
void				ft_print_line(t_env *ev, t_color c, t_vector s, t_vector e);
void				ft_gen_loading_border(t_env *e);
void				ft_fill_loading_border(t_env *e, int x);
int					ft_loading_bar(int x, t_env *e);

#endif