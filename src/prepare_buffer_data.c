/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_buffer_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 18:56:36 by mrassokh          #+#    #+#             */
/*   Updated: 2018/04/17 18:56:41 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scope.h"

void		fill_normal_and_default_color(GLfloat *vertices, int counter,
																int has_normal)
{
	t_vector	normal;

	if (!has_normal)
	{
		vector_set(&normal, vertices[counter], vertices[counter + 1],
													vertices[counter + 2]);
		vector_product_float(&normal, 1 / vector_abs(&normal));
		vertices[counter + 5] = normal.x;
		vertices[counter + 6] = normal.y;
		vertices[counter + 7] = normal.z;
	}
	vertices[counter + 8] = (counter % 10) / 10.0f;
	vertices[counter + 9] = (counter % 10) / 10.0f;
	vertices[counter + 10] = (counter % 10) / 10.0f;
}

void		fill_vertices_buffer(GLfloat *vertices, t_obj_reader *reader)
{
	t_list				*vertex_common_list;
	t_vertex_common		*content;
	int					counter;

	counter = 0;
	vertex_common_list = reader->vertex_common;
	while (vertex_common_list && counter < reader->vertex_common_counter * 11)
	{
		content = (t_vertex_common *)vertex_common_list->content;
		vertices[counter] = (content->vertex_coord.x
				- reader->first_view.center.x) * reader->first_view.scale_mult;
		vertices[counter + 1] = (content->vertex_coord.y
				- reader->first_view.center.y) * reader->first_view.scale_mult;
		vertices[counter + 2] = (content->vertex_coord.z
				- reader->first_view.center.z) * reader->first_view.scale_mult;
		vertices[counter + 3] = content->texture_coord.u;
		vertices[counter + 4] = content->texture_coord.v;
		vertices[counter + 5] = content->normal_coord.x;
		vertices[counter + 6] = content->normal_coord.y;
		vertices[counter + 7] = content->normal_coord.z;
		fill_normal_and_default_color(vertices, counter, reader->has_normal);
		counter += 11;
		vertex_common_list = vertex_common_list->next;
	}
}

void		fill_indices_buffer(GLuint *indices, t_obj_reader *reader)
{
	t_list			*vertex_index_list;
	t_vertex_index	*content;
	int				counter;

	vertex_index_list = reader->vertex_index;
	counter = 0;
	while (vertex_index_list && counter < reader->vertex_index_counter)
	{
		content = (t_vertex_index *)vertex_index_list->content;
		if (content->final_index >= 0)
		{
			if (!content->first_entry_flag)
				indices[counter++] = indices[content->final_index
												- content->first_entry_offset];
			else
				indices[counter++] = content->final_index;
		}
		vertex_index_list = vertex_index_list->next;
	}
}

void		prepare_buffer_data(t_programm *root, t_obj_reader *reader)
{
	fill_index_list(reader);
	root->vert_size = reader->vertex_common_counter * 11 * sizeof(GLfloat);
	root->indices_size = reader->vertex_index_counter * sizeof(GLuint);
	root->vertices = (GLfloat *)malloc(root->vert_size);
	root->indices = (GLuint *)malloc(root->indices_size);
	fill_vertices_buffer(root->vertices, reader);
	fill_indices_buffer(root->indices, reader);
}
