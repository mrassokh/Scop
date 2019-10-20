/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_loader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 08:41:29 by mrassokh          #+#    #+#             */
/*   Updated: 2018/04/19 08:41:32 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_LOADER_H
# define BMP_LOADER_H

# define IMAGE_BMP_FILE_HEADER_SIZE  14
# define IMAGE_BMP_INFO_HEADER_SIZE  40
# define IMAGE_BMP_HEAD IMAGE_BMP_FILE_HEADER_SIZE + IMAGE_BMP_INFO_HEADER_SIZE

/*
**	Color
*/
typedef struct			s_color
{
	unsigned char		blue;
	unsigned char		green;
	unsigned char		red;
	unsigned char		alpha;
}						t_color;

/*
**	Image
*/
typedef struct			s_bmp_image
{
	int					width;
	int					height;
	t_color				*data;
}						t_bmp_image;

/*
**	variables for reading
*/
typedef struct			s_bmp_reader
{
	FILE				*f;
	int					w;
	int					h;
	int					x;
	int					y;
	int					bypp;
	unsigned short		bpp;
	char				tag[2];
	t_bmp_image			*im;
	unsigned char		*data;
	unsigned char		*ptr;
	unsigned char		header[IMAGE_BMP_HEAD - 2];
	t_color				*col;
}						t_bmp_reader;

#endif
