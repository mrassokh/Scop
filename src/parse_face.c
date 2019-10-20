/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_face.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 10:44:18 by mrassokh          #+#    #+#             */
/*   Updated: 2018/04/08 10:44:45 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_parser.h"
#include "scope.h"

void			fill_faces(t_faces *face, t_obj_reader *reader, int counter_up)
{
	t_list		*new_faces;

	new_faces = ft_lstnew(face, sizeof(*face));
	ft_lstpushback(&reader->f_list, new_faces);
	reader->f_counter++;
	reader->index_counter += counter_up;
}

void			scan_vertex_data(char *vertex_data_index,
								int *store_place, int row_number)
{
	int match;

	match = sscanf(vertex_data_index, "%d", store_place);
	if (match != 1 || *store_place < 0)
	{
		printf("Warning: wrong face index format in row %d\n", row_number);
		*store_place = 0;
	}
}

void			process_face_vertex(t_faces *f, char **face_vertexes, int index,
														t_obj_reader *reader)
{
	char		**vertex_data;
	int			i;
	int			row;

	row = reader->f_counter + 1;
	if (index < 0 || index > 2)
		return ;
	i = 0;
	vertex_data = ft_strsplit_with_empty(face_vertexes[index], '/');
	while (i < 3 && vertex_data[i++])
	{
		if (ft_strlen(vertex_data[i - 1]))
		{
			if (i - 1 == 0)
				scan_vertex_data(vertex_data[i - 1], &f->v_index[index], row);
			else if (i - 1 == 1)
				scan_vertex_data(vertex_data[i - 1], &f->vt_index[index], row);
			else if (i - 1 == 2)
			{
				scan_vertex_data(vertex_data[i - 1], &f->vn_index[index], row);
				reader->has_normal++;
			}
		}
	}
	ft_double_array_memdel((void ***)&vertex_data);
}

void			process_face(char **face_vertexes, t_obj_reader *reader)
{
	t_faces		face;

	ft_bzero(&face, sizeof(t_faces));
	process_face_vertex(&face, face_vertexes, 0, reader);
	process_face_vertex(&face, face_vertexes, 1, reader);
	process_face_vertex(&face, face_vertexes, 2, reader);
	fill_faces(&face, reader, 3);
}

void			process_double_face(char **face_vertexes, t_obj_reader *reader)
{
	char		**double_face_vertexes;

	double_face_vertexes = (char**)malloc(sizeof(char*) * 4);
	double_face_vertexes[0] = ft_strdup(face_vertexes[0]);
	double_face_vertexes[1] = ft_strdup(face_vertexes[1]);
	double_face_vertexes[2] = ft_strdup(face_vertexes[2]);
	double_face_vertexes[3] = NULL;
	process_face(double_face_vertexes, reader);
	ft_double_array_memdel((void ***)&double_face_vertexes);
	double_face_vertexes = (char**)malloc(sizeof(char*) * 4);
	double_face_vertexes[0] = ft_strdup(face_vertexes[2]);
	double_face_vertexes[1] = ft_strdup(face_vertexes[3]);
	double_face_vertexes[2] = ft_strdup(face_vertexes[0]);
	double_face_vertexes[3] = NULL;
	process_face(double_face_vertexes, reader);
	ft_double_array_memdel((void ***)&double_face_vertexes);
}
