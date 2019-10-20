/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:56:02 by mrassokh          #+#    #+#             */
/*   Updated: 2018/03/20 13:56:04 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_parser.h"
#include "scope.h"

void			rewrite_max_size(t_vertex *vertex, t_vector *max_size)
{
	if (fabs(vertex->x) > fabs(max_size->x))
		max_size->x = fabs(vertex->x);
	if (fabs(vertex->y) > fabs(max_size->y))
		max_size->y = fabs(vertex->y);
	if (fabs(vertex->z) > fabs(max_size->z))
		max_size->z = fabs(vertex->z);
}

void			parse_vertex(char *str, t_obj_reader *reader)
{
	t_vertex	vertex;
	t_list		*new_vertex;
	int			matches;
	t_vector	vertex_coord;

	matches = sscanf(str, "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
	if (matches < 3)
		printf("Warning: vertex incomplete in %d row\n", reader->v_counter + 1);
	rewrite_max_size(&vertex, &reader->first_view.max_size);
	vector_set(&vertex_coord, vertex.x, vertex.y, vertex.z);
	vectors_add(&reader->first_view.center, &reader->first_view.center,
				&vertex_coord);
	new_vertex = ft_lstnew(&vertex, sizeof(vertex));
	ft_lstpushback(&reader->v_list, new_vertex);
	reader->v_counter++;
}

void			parse_vertex_texture(char *str, t_obj_reader *reader)
{
	t_vertex_texture	vertex;
	t_list				*new_vertex_texture;
	int					matches;

	matches = sscanf(str, "%f %f", &vertex.u, &vertex.v);
	if (matches < 2)
		printf("Warning: texture vertex incomplete in %d row\n",
				reader->vt_counter + 1);
	new_vertex_texture = ft_lstnew(&vertex, sizeof(vertex));
	ft_lstpushback(&reader->vt_list, new_vertex_texture);
	reader->vt_counter++;
}

void			parse_vertex_normal(char *str, t_obj_reader *reader)
{
	t_vertex_normal		vertex;
	t_list				*new_vertex_normal;
	int					matches;

	matches = sscanf(str, "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
	if (matches < 3)
		printf("Warning: normal vertex incomplete in %d row\n",
				reader->vn_counter + 1);
	new_vertex_normal = ft_lstnew(&vertex, sizeof(vertex));
	ft_lstpushback(&reader->vn_list, new_vertex_normal);
	reader->vn_counter++;
}

void			parse_faces(char *str, t_obj_reader *reader)
{
	int			vertex_count;
	char		**face_vertexes;

	face_vertexes = ft_strsplit(str, ' ');
	vertex_count = 0;
	while (face_vertexes[vertex_count])
		vertex_count++;
	if (vertex_count == 3)
		process_face(face_vertexes, reader);
	else if (vertex_count == 4)
		process_double_face(face_vertexes, reader);
	else
		printf("Warning: wrong face format: %d row \n", reader->f_counter + 1);
	ft_double_array_memdel((void ***)&face_vertexes);
}
