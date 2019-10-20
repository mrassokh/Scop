/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_common_index.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:40:53 by mrassokh          #+#    #+#             */
/*   Updated: 2018/04/10 14:40:55 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scope.h"

void					fill_vertex_index(t_vertex_index *vertex,
													t_faces *face, int index)
{
	if (index < 0 || index > 2)
		return ;
	vertex->v_index = face->v_index[index];
	vertex->vt_index = face->vt_index[index];
	vertex->vn_index = face->vn_index[index];
}

t_vertex_normal			find_vn_coord(t_list *vn_list, int index)
{
	t_vertex_normal		vertex_normal_coord;
	t_list				*cursor;
	int					counter;

	cursor = vn_list;
	counter = 0;
	ft_bzero(&vertex_normal_coord, sizeof(t_vertex_normal));
	while (cursor)
	{
		if (counter++ == index)
		{
			vertex_normal_coord = *((t_vertex_normal *)cursor->content);
			break ;
		}
		cursor = cursor->next;
	}
	return (vertex_normal_coord);
}

t_vertex_texture		find_vt_coord(t_list *vt_list, int index)
{
	t_vertex_texture	vertex_texture_coord;
	t_list				*cursor;
	int					counter;

	cursor = vt_list;
	counter = 0;
	ft_bzero(&vertex_texture_coord, sizeof(t_vertex_texture));
	while (cursor)
	{
		if (counter++ == index)
		{
			vertex_texture_coord = *((t_vertex_texture *)cursor->content);
			break ;
		}
		cursor = cursor->next;
	}
	return (vertex_texture_coord);
}

t_vertex				find_v_coord(t_list *v_list, int index)
{
	t_vertex		vertex_coord;
	t_list			*cursor;
	int				counter;

	cursor = v_list;
	counter = 0;
	ft_bzero(&vertex_coord, sizeof(t_vertex));
	while (cursor)
	{
		if (counter++ == index)
		{
			vertex_coord = *((t_vertex *)cursor->content);
			break ;
		}
		cursor = cursor->next;
	}
	return (vertex_coord);
}

void					fill_common_index(t_vertex_common *vertex_common,
							t_vertex_index *vertex_index, t_obj_reader *reader)
{
	int		v_index;
	int		vt_index;
	int		vn_index;

	v_index = vertex_index->v_index - 1;
	vt_index = vertex_index->vt_index - 1;
	vn_index = vertex_index->vn_index - 1;
	if (v_index >= 0 || v_index < reader->v_counter)
		vertex_common->vertex_coord = find_v_coord(reader->v_list, v_index);
	if (vt_index >= 0 || vt_index < reader->vt_counter)
		vertex_common->texture_coord = find_vt_coord(reader->vt_list, vt_index);
	if (vn_index >= 0 || vn_index < reader->vn_counter)
		vertex_common->normal_coord = find_vn_coord(reader->vn_list, vn_index);
}
