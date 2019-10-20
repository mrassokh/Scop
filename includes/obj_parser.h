/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 11:12:08 by mrassokh          #+#    #+#             */
/*   Updated: 2018/03/20 11:12:18 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_PARSER_H
# define OBJ_PARSER_H
# include <stdio.h>
# include "libft.h"
# include "vector.h"
# include "bmp_loader.h"

/*
**	Vertex
*/
typedef struct			s_vertex
{
	float				x;
	float				y;
	float				z;
}						t_vertex;

/*
**	Vertex_Texture
*/
typedef struct			s_vertex_texture
{
	float				u;
	float				v;
}						t_vertex_texture;

/*
**	Vertex_Normal
*/
typedef struct			s_vertex_normal
{
	float				x;
	float				y;
	float				z;
}						t_vertex_normal;

/*
**	Faces
*/
typedef struct			s_faces
{
	int					v_index[4];
	int					vt_index[4];
	int					vn_index[4];
}						t_faces;

/*
**	Vertex index
*/
typedef struct			s_vertex_index
{
	int					v_index;
	int					vt_index;
	int					vn_index;
	int					id;
	int					final_index;
	int					first_entry_offset;
	int					first_entry_flag;
}						t_vertex_index;

/*
**	Vertex final data
*/
typedef struct			s_vertex_common
{
	t_vertex			vertex_coord;
	t_vertex_texture	texture_coord;
	t_vertex_normal		normal_coord;
	int					id;
}						t_vertex_common;
/*
**	Max size and center
*/
typedef struct			s_scale_center
{
	t_vector			max_size;
	float				scale_mult;
	t_vector			center;
}						t_scale_center;
/*
**	Material_Properties
*/
typedef struct			s_material
{
	float				ambient[3];
	float				diffuse[3];
	float				specular_refl[3];
	int					illum;
	float				trans;
	float				dissolve;
	float				ns;
	char				*name;
}						t_material;

/*
**	FILE_READER
*/
typedef struct			s_file_reader
{
	FILE				*fp;
	int					file_size;
	char				*raw_file;
}						t_file_reader;

/*
**	MTL_READER
*/
typedef struct			s_mtl_reader
{
	char				*mtl_file_name;
	t_file_reader		file_reader;
	char				**split_file_to_material;
	char				**split_material_to_properties;
	t_list				*materials;
}						t_mtl_reader;

/*
**	OBJ_READER
*/
typedef struct			s_obj_reader
{
	t_list				*f_list;
	t_list				*vn_list;
	t_list				*vt_list;
	t_list				*v_list;
	t_list				*vertex_index;
	t_list				*vertex_common;
	int					v_counter;
	int					vt_counter;
	int					vn_counter;
	int					f_counter;
	int					index_counter;
	int					vertex_index_counter;
	int					vertex_index_offset;
	int					vertex_common_counter;
	int					has_texture;
	int					has_normal;
	t_file_reader		file_reader;
	t_mtl_reader		mtl_reader;
	char				**split_file;
	int					read;
	t_scale_center		first_view;
}						t_obj_reader;

int						parse_obj(char *filename, t_obj_reader *reader);
void					read_file(char *filename, t_file_reader *file_reader);
void					parse_vertex(char *str, t_obj_reader *reader);
void					parse_vertex_texture(char *str, t_obj_reader *reader);
void					parse_vertex_normal(char *str, t_obj_reader *reader);
void					parse_faces(char *str, t_obj_reader *reader);
void					process_face(char **face_vertexes,
										t_obj_reader *reader);

void					process_face_vertex(t_faces *f, char **face_vertexes,
										int index, t_obj_reader *reader);
void					scan_vertex_data(char *vertex_data_index,
										int *store_place, int row_number);
void					process_double_face(char **face_vertexes,
										t_obj_reader *reader);
void					fill_faces(t_faces *face, t_obj_reader *reader,
										int counter_up);

void					fill_index_list(t_obj_reader *reader);
void					append_common_vertex(t_vertex_index *vertex_index,
										t_obj_reader *reader);
void					append_vertex_index(t_vertex_index *vertex_index,
						t_obj_reader *reader, int final_index,
						int append_entry_offset);

int						find_match(t_vertex_index *vertex_index,
									t_list *vertex_index_list);
void					fill_common_index(t_vertex_common *vertex_common,
							t_vertex_index *vertex_index, t_obj_reader *reader);

t_vertex				find_v_coord(t_list *v_list, int index);
t_vertex_texture		find_vt_coord(t_list *vt_list, int index);
t_vertex_normal			find_vn_coord(t_list *vn_list, int index);
void					fill_vertex_index(t_vertex_index *vertex,
						t_faces *face, int index);

int						parse_mtl(char *filename, t_mtl_reader *reader);
char					**ft_str_strsplit(char const *s, char const *incl);
char					**ft_strsplit_with_empty(char const *s, char c);

void					parse_ambient(char *str, t_material *material);
void					parse_diffuse(char *str, t_material *material);
void					parse_specular(char *str, t_material *material);
void					parse_refr(char *str, t_material *material);
void					parse_illum(char *str, t_material *material);

float					find_max_size(t_vector *max_size);

#endif
