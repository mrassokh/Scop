/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_index_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:33:58 by mrassokh          #+#    #+#             */
/*   Updated: 2018/04/10 14:34:01 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scope.h"

void	append_to_buffer_prepare_list(t_vertex_index *vertex_index,
										t_obj_reader *reader, int final_index)
{
	if (final_index != -1)
	{
		append_vertex_index(vertex_index, reader, final_index, 0);
		reader->vertex_index_offset++;
	}
	else
	{
		append_vertex_index(vertex_index, reader,
			reader->vertex_common_counter, 1);
		append_common_vertex(vertex_index, reader);
	}
}

void	append_vertex_index(t_vertex_index *vertex_index, t_obj_reader *reader,
							int final_index, int append_entry_offset)
{
	t_list		*new_vertex_index;

	vertex_index->id = reader->vertex_index_counter++;
	if (append_entry_offset)
	{
		vertex_index->first_entry_offset = reader->vertex_index_offset;
		vertex_index->first_entry_flag = 1;
	}
	vertex_index->final_index = final_index;
	new_vertex_index = ft_lstnew(vertex_index, sizeof(t_vertex_index));
	ft_lstpushback(&reader->vertex_index, new_vertex_index);
}

void	append_common_vertex(t_vertex_index *vertex_index, t_obj_reader *reader)
{
	t_list			*new_vertex_common;
	t_vertex_common	vertex_common;

	ft_bzero(&vertex_common, sizeof(t_vertex_common));
	vertex_common.id = reader->vertex_common_counter++;
	fill_common_index(&vertex_common, vertex_index, reader);
	new_vertex_common = ft_lstnew(&vertex_common, sizeof(t_vertex_common));
	ft_lstpushback(&reader->vertex_common, new_vertex_common);
}

int		find_match(t_vertex_index *vertex_index, t_list *vertex_index_list)
{
	t_list			*vi_list;
	t_vertex_index	*content;

	vi_list = vertex_index_list;
	if (!vi_list)
		return (-1);
	while (vi_list)
	{
		content = (t_vertex_index *)vi_list->content;
		if (vertex_index->v_index == content->v_index
			&& vertex_index->vt_index == content->vt_index
			&& vertex_index->vn_index == content->vn_index)
			return (content->id);
		vi_list = vi_list->next;
	}
	return (-1);
}

void	fill_index_list(t_obj_reader *reader)
{
	t_vertex_index	vertex_index;
	int				final_index;
	t_list			*f_list;
	int				f_counter;
	int				v_counter;

	f_list = reader->f_list;
	f_counter = 0;
	while (f_list && f_counter < reader->index_counter)
	{
		v_counter = 0;
		while (v_counter++ < 3)
		{
			ft_bzero(&vertex_index, sizeof(t_vertex_index));
			fill_vertex_index(&vertex_index, ((t_faces *)f_list->content),
				v_counter - 1);
			final_index = find_match(&vertex_index, reader->vertex_index);
			append_to_buffer_prepare_list(&vertex_index, reader, final_index);
			f_counter++;
		}
		f_list = f_list->next;
	}
}
