/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_bmp_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:07:42 by mrassokh          #+#    #+#             */
/*   Updated: 2018/03/18 18:07:45 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scope.h"

int				open_and_read_bmp(char *filename, t_bmp_reader *reader)
{
	reader->f = fopen(filename, "rb");
	if (!reader->f)
	{
		fprintf(stderr, "Could not open %s\n", filename);
		return (0);
	}
	if (fread(reader->tag, 1, 2, reader->f) != 2)
	{
		fprintf(stderr, "Error reading image tag for %s\n", filename);
		return (0);
	}
	if (reader->tag[0] != 'B' || reader->tag[1] != 'M')
	{
		fprintf(stderr, "%s is not a valid WIN32 bitmap file\n", filename);
		return (0);
	}
	if (fread(reader->header, 1, IMAGE_BMP_HEAD - 2, reader->f)
													!= IMAGE_BMP_HEAD - 2)
	{
		fprintf(stderr, "Error reading image header for %s\n", filename);
		return (0);
	}
	return (1);
}

int				check_header(char *filename, t_bmp_reader *reader)
{
	reader->w = *((int*)&reader->header[IMAGE_BMP_FILE_HEADER_SIZE - 2 + 4]);
	reader->h = *((int*)&reader->header[IMAGE_BMP_FILE_HEADER_SIZE
																- 2 + 4 + 4]);
	reader->bpp = *((unsigned short*)&reader->header[IMAGE_BMP_FILE_HEADER_SIZE
					- 2 + 4 + 4 + 4 + 2]);
	reader->bypp = reader->bpp / 8;
	if (reader->bpp != 24 && reader->bpp != 32)
	{
		fprintf(stderr, "%s is not a 24 or 32 bit bitmap (%dBPP)\n", filename,
																reader->bpp);
		return (0);
	}
	if (reader->w % 8 != 0 || reader->h % 8 != 0)
	{
		fprintf(stderr, "%s doesn't have width or height a multiple of 8\n",
																	filename);
		return (0);
	}
	return (1);
}

void			fill_color_data(t_bmp_reader *reader)
{
	reader->y = 0;
	while (reader->y < reader->h)
	{
		reader->x = 0;
		while (reader->x < reader->w)
		{
			reader->ptr = &reader->data[(reader->x * reader->bypp)
									+ (reader->y * reader->w * reader->bypp)];
			reader->col = &reader->im->data[reader->x + reader->y * reader->w];
			reader->col->red = reader->ptr[0];
			reader->col->green = reader->ptr[1];
			reader->col->blue = reader->ptr[2];
			if (reader->bpp == 32)
				reader->col->alpha = reader->ptr[3];
			else
				reader->col->alpha = 0xFF;
			reader->x++;
		}
		reader->y++;
	}
}

void			allocate_image(t_bmp_reader *reader)
{
	if (!(reader->im = (t_bmp_image*)malloc(sizeof(t_bmp_image))))
		error(errno);
	reader->im->width = reader->w;
	reader->im->height = reader->h;
	if (!(reader->im->data = (t_color*)malloc(sizeof(t_color)
													* reader->w * reader->h)))
		error(errno);
	if (!(reader->data = (unsigned char*)malloc(sizeof(char) * reader->bypp
													* reader->w * reader->h)))
		error(errno);
}

t_bmp_image		*image_bmp_load(char *filename)
{
	t_bmp_reader	reader;
	size_t			test;

	if (!open_and_read_bmp(filename, &reader) ||
										!check_header(filename, &reader))
	{
		fclose(reader.f);
		return (NULL);
	}
	allocate_image(&reader);
	test = fread(reader.data, reader.bypp, reader.w * reader.h, reader.f);
	if (test != (size_t)reader.w * reader.h)
	{
		fprintf(stderr, "Error reading image data for %s\n", filename);
		fclose(reader.f);
		return (0);
	}
	fclose(reader.f);
	fill_color_data(&reader);
	free(reader.data);
	return (reader.im);
}
