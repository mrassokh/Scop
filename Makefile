# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrassokh <mrassokh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/12 09:31:31 by mrassokh          #+#    #+#              #
#    Updated: 2017/06/03 14:38:10 by mrassokh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	scop

#[----------------------------------HEADERS-----------------------------------]#

HEADERS_PATH =	./includes/

INC =-I$(HEADERS_PATH)

#[---------------------------------LIBRARIES----------------------------------]#

LIBPATH = ./libs/

LIBFT = -lft
LIBGLEW = -lGLEW
LIBSDL = -lSDL2

LIBSDLIM = -lSDL2_image

LIBVECTORPATH = $(LIBPATH)libvector

LIBFTPATH = $(LIBPATH)libft
LIBFTINC = $(LIBFTPATH)/includes

LIBGLEWPATH = $(LIBPATH)glew/lib/
LIBGLEWINC = $(LIBPATH)glew/include


LIBS = $(LIBFT) $(LIBGLEW)
LIBSINC = -I$(LIBFTINC) -I$(LIBGLEWINC)
LIBSDIR = -L$(LIBPATH) -L$(LIBGLEWPATH)
LIBRIRIES = $(LIBS) $(LIBSINC) $(LIBSDIR)

#[--------------------------------COMPILATION---------------------------------]#

CC = gcc
FLAGS	= -Wall -Wextra -Werror
FRMPATH = -F /Library/Frameworks
FRAMEWORKS =  $(FRMPATH) -framework OpenGL -framework SDL2

#[----------------------------------SOURCES-----------------------------------]#

SRC_PATH 	= ./src/

ROOT = scope.c

FUNCTIONS = load_bmp_image.c obj_parser.c parse_obj_functions.c parse_face.c \
 			mtl_reader.c  mtl_parser_functions.c  \
			fill_common_index.c fill_index_list.c buffer_instant_and_fill.c \
			fill_settings.c prepare_buffer_data.c \
			event_handler.c error.c\
			create_projection_matrix.c  render.c shaders.c


SRC = $(ROOT) $(FUNCTIONS)
OBJ_DIR = ./obj/
OBJ = $(addprefix $(OBJ_DIR),$(SRC:.c=.o))


#[-----------------------------------COLORS-----------------------------------]\
#

GREEN                   =       \033[32m
RESET                   =       \033[39m
YELLOW                  =       \033[33m
RED                     =       \033[31m


#[------------------------------------MAKE------------------------------------]\
#
.PHONY: make_libs
.PHONY: cc_libft

vpath %.c $(SRC_PATH)
vpath %.h $(HEADERS_PATH)

all: $(NAME)

$(NAME): make_libs $(OBJ)
	@echo "\033[0;32mCompile program ...\033[0m"
	@ $(CC) $(FLAGS) -o $(NAME) $(OBJ) $(INC) $(LIBRIRIES) $(FRAMEWORKS) -g
	@ echo "$(GREEN)[$(NAME)]$(RESET)"

$(OBJ_DIR)%.o: %.c
	@echo "\033[0;32mCreating object file\033[0m \033[31m$@\033[0m"
	@ $(CC) $(FLAGS) -c $< -o $@  $(INC) $(LIBSINC) $(FRMPATH) -g
	@ printf ' $(GREEN)[add]$(RESET) $<\n'

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean: clean_libs
	@ rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@ echo "$(YELLOW)[clean]$(RESET)"

fclean: clean
	@ rm -f $(NAME) $(NAMELIB)
	@ echo "$(RED)[fclean]$(RESET)"

re: fclean all

make_libs: cc_libft cc_libglew

cc_libft:
	@cd $(LIBFTPATH);\
	make;\
	make clean;\
	mv libft.a ../;

cc_libglew:
	@echo  "\x1b[32mlibglew   compiles...\x1b[0m"
	@cd $(LIBPATH)glew/;\
	make glew.lib.static;\

clean_libs:
	@ rm -f $(LIBPATH)libft.a
	@ make -C $(LIBPATH)glew/ distclean
	@ echo "$(RED)[libft fclean]$(RESET)"
