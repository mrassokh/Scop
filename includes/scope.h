/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scope.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 09:05:12 by mrassokh          #+#    #+#             */
/*   Updated: 2018/04/19 09:05:14 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOPE_H
# define SCOPE_H
# define GLEW_STATIC
# include "GL/glew.h"
# include <SDL2/SDL.h>
# include "libft.h"
# include <stdlib.h>
# include <errno.h>
# include "obj_parser.h"

typedef struct			s_shaders
{
	GLint				success;
	GLchar				info_log[512];
	GLuint				vertex_shader;
	GLuint				fragment_shader;
	GLuint				shader_program;
	const GLchar		*vertex_shader_source;
	const GLchar		*fragment_shader_source;
	t_file_reader		shader_reader;
}						t_shaders;

typedef struct			s_ogl
{
	GLuint				vbo;
	GLuint				vao[2];
	GLuint				ebo;
	GLuint				texture;
}						t_ogl;

typedef struct			s_matrix
{
	GLint				projection_loc;
	GLint				translate_loc;
	GLint				scale_loc;
	GLint				rotate_loc;
	t_vector			v_translate;
	t_vector			v_scale;
	t_vector			v_rotate;
	float				scale[16];
	float				rotate[16];
	float				translate[16];
	float				*projection;
}						t_matrix;

enum					e_color_flag
{
	define,
	gradient,
	material
};

typedef struct			s_processing
{
	t_material			mat;
	enum e_color_flag	color_state;
	int					rot_flag;
	int					cycl;
	t_quat				x_rot;
	t_quat				y_rot;
	t_quat				z_rot;
	t_vector			axe_vector;
	t_quat				base_quat;
	GLint				light_pos_loc;
	GLint				diffuse_color_loc;
	GLint				frag_flags_loc;
}						t_processing;

typedef struct			s_programm
{
	SDL_Window			*window;
	SDL_GLContext		gl_context;
	GLfloat				*vertices;
	GLuint				*indices;
	int					gen_text;
	int					has_texture;
	int					has_normal;
	int					vert_size;
	int					has_shading;
	int					indices_size;
	t_vector			light_color;
	t_vector			light_pos;
	t_vector			camera_pos;
	t_ogl				ogl;
	t_matrix			matr;
	t_shaders			shaders;
}						t_programm;

t_bmp_image				*image_bmp_load(char *filename);
void					error(int errnum);
void					event_handler(int *cycl, enum e_color_flag *color_state,
											int *rot_flag, t_programm *root);
void					ft_double_array_memdel(void ***pointer);
void					fill_buffers_by_prepared_data(t_programm *root);
void					instant_buffers(t_programm *root);
void					prepare_buffer_data(t_programm *root,
											t_obj_reader *reader);
GLchar					*get_shader_source(char *filename,
											t_file_reader *reader);
void					create_shader_program(t_shaders *shaders);
int						shaders_compile(t_shaders *shaders);
int						check_shader_compile(GLuint shader, t_shaders *shaders);

void					fill_vertices_buffer(GLfloat *vertices,
											t_obj_reader *reader);
void					fill_indices_buffer(GLuint *indices,
											t_obj_reader *reader);
float					*create_projection_matrix(float fop, float asp,
											float near, float far);
void					render(t_programm *root, t_obj_reader *reader,
											t_processing *proc);

void					fill_settings(t_obj_reader *reader, t_programm *root,
											t_processing *proc);
void					set_material(t_obj_reader *reader,
											t_material *mat);
void					load_texture(t_programm *root);
#endif
