/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 12:06:30 by mrassokh          #+#    #+#             */
/*   Updated: 2018/03/20 12:06:32 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_parser.h"
#include "scope.h"

float		find_max_size(t_vector *max_size)
{
	if (max_size->x > max_size->y)
		return (max_size->x > max_size->z ? max_size->x : max_size->z);
	return (max_size->y > max_size->z ? max_size->y : max_size->z);
}

void		read_file(char *filename, t_file_reader *reader)
{
	if (!(reader->fp = fopen(filename, "r")))
		error(errno);
	fseek(reader->fp, 0, SEEK_END);
	reader->file_size = ftell(reader->fp);
	rewind(reader->fp);
	if (!(reader->raw_file = malloc((reader->file_size + 1) * (sizeof(char)))))
		error(errno);
	fread(reader->raw_file, sizeof(char), reader->file_size, reader->fp);
	reader->raw_file[reader->file_size] = '\0';
	fclose(reader->fp);
}

void		parse_obj_string(char *trim_str, t_obj_reader *reader)
{
	char	*token;

	token = strtok(trim_str, " ");
	if (!ft_strcmp(token, "v"))
		parse_vertex(trim_str + 2, reader);
	else if (!ft_strcmp(token, "vt"))
		parse_vertex_texture(trim_str + 3, reader);
	else if (!ft_strcmp(token, "vn"))
		parse_vertex_normal(trim_str + 3, reader);
	else if (!ft_strcmp(token, "f"))
		parse_faces(trim_str + 2, reader);
	else if (!ft_strcmp(token, "mtllib"))
		parse_mtl(trim_str + 7, &reader->mtl_reader);
}

int			parse_obj(char *filename, t_obj_reader *reader)
{
	int			i;
	char		*trim_str;
	t_vector	vector_scale;

	read_file(filename, &reader->file_reader);
	reader->split_file = ft_strsplit(reader->file_reader.raw_file, '\n');
	i = 0;
	while (reader->split_file[i++])
	{
		trim_str = ft_strtrim(reader->split_file[i - 1]);
		if (trim_str[0] != '#')
			parse_obj_string(trim_str, reader);
		free(trim_str);
		free(reader->split_file[i - 1]);
	}
	vector_product_float(&reader->first_view.center,
		1 / ((float)reader->v_counter));
	vector_set(&vector_scale, fabs(reader->first_view.center.x),
		fabs(reader->first_view.center.y), fabs(reader->first_view.center.z));
	vectors_minus(&reader->first_view.max_size, &reader->first_view.max_size,
		&vector_scale);
	reader->first_view.scale_mult =
				fmin(1.0, 1 / (find_max_size(&reader->first_view.max_size)));
	free(reader->split_file);
	return (1);
}
