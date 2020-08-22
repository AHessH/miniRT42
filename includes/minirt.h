/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:48:01 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/22 15:25:53 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx_int.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define SPHERE 1
# define PLANE 2
# define SQUARE 3
# define CYLINDER 4
# define TRIANGLE 5
# define DISK 6

# define BMP_NAME "new_image.bmp"
# define BMP_FILE_HEADER 14
# define BMP_INFO_HEADER 40

typedef struct		s_data {
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct		s_mlx {
	void			*mlx;
	void			*win;
	void			*params;
}					t_mlx;

typedef struct		s_color {
	double			r;
	double			g;
	double			b;
}					t_color;

typedef struct		s_vec
{
	float			x;
	float			y;
	float			z;
}					t_vec;

typedef struct		s_ray
{
	t_vec			orig;
	t_vec			dir;
}					t_ray;

typedef struct		s_amb {
	float			ambl_ratio;
	t_color			color;
	t_color			k_color;
}					t_amb;

typedef struct		s_cam {
	int				serial;
	t_vec			coord;
	t_vec			normal;
	float			fov;
	float			k_fov;
	t_vec			up;
	t_vec			right;
	void			*prev;
	void			*next;
}					t_cam;

typedef struct		s_elem {
	int				id;
	double			ratio;
	double			diam;
	double			height;
	double			cache;
	t_vec			point;
	t_color			color;
	t_vec			orient;
	t_vec			point2;
	t_vec			point3;
	t_vec			cache_vec1;
	t_vec			cache_vec2;
	t_vec			dir;
}					t_elem;

typedef struct		s_list {
	t_elem			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_garbage {
	double			a;
	double			b;
	double			c;
	double			discr;
	double			t1;
	double			t2;
	t_vec			sub;
	t_vec			cross;
}					t_garbage;

typedef struct		s_scene {
	t_data			*img;
	t_mlx			*mlx;
	int				save;
	int				rx;
	int				ry;
	t_color			color;
	float			t;
	float			k;
	float			sh;
	t_ray			ray;
	t_vec			vec_p;
	t_garbage		s;
	t_amb			*amb;
	int				count_cam;
	t_cam			*cam;
	int				count_light;
	t_elem			*obj;
	t_list			*light_list;
	t_list			*obj_list;
}					t_scene;

void				rendering(t_mlx *mlx, t_data *img, t_scene *scene);
void				win_control(t_scene *scene);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
void				error_exit(char *error, t_scene *scene);
int					get_next_line(int fd, char **line);
char				*ft_strjoin(char*s1, char*s2);
char				*ft_strdup(char *str);
char				*ft_strchr(char *str, char c);
size_t				ft_strlen(char *str);
char				**ft_split(char const *s, char c);
t_scene				*read_scene_from_file(int ac, char **av);
void				parse_scene(t_scene *scene, char **line);
int					ft_atoi(const char *str);
double				ft_atof(char *str);
int					ft_isdigit(int ch);
int					ft_is_number(char *line);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_calloc(size_t num, size_t size);
void				*ft_memset(void *buf, int ch, size_t count);
char				*ft_strrchr(const char *str, int ch);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_list				*ft_lstnew(void *content);
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_perror(void);
void				free_mass_str(char **mass);
void				free_all_scene(t_scene *scene);
void				parse_res(t_scene *scene, char **line);
void				parse_amb(t_scene *scene, char **line);
void				parse_cams(t_scene *scene, char **line);
void				init_new_sphere(t_scene *scene, char **temp);
void				init_new_plane(t_scene *scene, char **temp);
void				init_new_square(t_scene *scene, char **line);
void				init_new_cylinder(t_scene *scene, char **line);
void				init_new_triangle(t_scene *scene, char **line);
void				check_scene_errors(char **line, t_scene *scene);
int					check_colors(char *line, t_scene *scene);
void				check_param_deep_scene_errors(char **line, t_scene *scene);
void				check_shape_errors(char **tmp, t_scene *scene);
int					count_of_params(char **line);
int					param_is_pos_float(char *line);
int					is_mass_of_float(char *line, t_scene *scene);
int					param_is_float(char *line);
t_vec				v_norm(t_vec v);
float				v_dot(t_vec v1, t_vec v2);
t_vec				v_mult(t_vec v, float m);
t_vec				v_sub(t_vec v1, t_vec v2);
t_vec				v_add(t_vec v1, t_vec v2);
t_vec				v_cross(t_vec v1, t_vec v2);
float				v_len(t_vec v);
t_vec				v_proj(t_vec v1, t_vec v2);
void				check_color(t_color *color);
int					color_to_int(t_color *color);
t_color				color_mult(t_color color1, t_color color2);
t_color				color_add(t_color color1, t_color color2);
t_color				color_intens(float intens, t_color color);
void				check_normal(t_vec *vec, t_scene *scene);
t_color				set_color(char **temp_cols);
void				sp_intersect(t_scene *scene, t_elem *sphere, t_vec orig,
								t_vec dir);
void				identify_obj(t_scene *scene, t_elem *obj, t_vec orig,
								t_vec dir);
t_color				get_color(t_scene *scene, t_vec p, t_vec n, t_color color);
float				light_intersect(t_scene *scene, double dot, t_vec p,
								t_elem *light);
t_vec				get_light_vec(t_elem *light, t_vec p);
int					plane_side(t_scene *scene, t_elem *light, t_vec p, t_vec n);
void				pl_intersect(t_scene *scene, t_elem *plane, t_vec orig,
								t_vec dir);
float				get_plane_t(t_elem *plane, t_vec orig, t_vec dir);
int					calc_shadows(t_scene *scene, t_vec orig, t_vec dir,
								t_elem *light);
t_vec				get_normal(t_scene *scene, t_vec p);
t_elem				*elem_cpy(t_elem *elem);
void				sq_intersect(t_scene *scene, t_elem *square, t_vec orig,
								t_vec dir);
void				tr_intersect(t_scene *scene, t_elem *triangle, t_vec orig,
								t_vec dir);
void				cy_intersect(t_scene *scene, t_elem *clndr, t_vec orig,
								t_vec dir);
int					init_disk_cy(t_scene *scene, t_elem *clndr, double t,
								int done);
void				disk_intersect(t_scene *scene, t_elem *disk, t_vec orig,
								t_vec dir);
int					discriminant(t_garbage *s);
t_vec				get_clndr_normal(t_elem *clndr, t_vec p);
void				save_bmp(t_scene *scene, char *file_name);

#endif
