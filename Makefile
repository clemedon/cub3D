# @author   clemedon (Clément Vidon)
####################################### BEG_5 ####

NAME        := cub3D

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# LIBS        libraries to be used
# LIBS_TARGET libraries to be built
#
# INCS        header file locations
#
# SRC_DIR     source directory
# SRCS        source files
#
# BUILD_DIR   build directory
# OBJS        object files
# DEPS        dependency files
#
# CC          compiler
# CFLAGS      compiler flags
# CPPFLAGS    preprocessor flags
# LDFLAGS     linker flags
# LDLIBS      libraries name

############## MACOS ##############
ifeq ($(shell uname -s), Darwin)
	LIBS        := ft mlx m
	LIBS_TARGET := \
				   lib/libft/libft.a \
				   lib/minilibx-darwin/libmlx.a
	INCS      := /opt/X11/include
	CFLAGS    := -D OSTYPE=darwin
	LDLIBS    := -framework OpenGL -framework AppKit
endif

############## LINUX ##############
ifeq ($(shell uname -s), Linux)
	LIBS        := ft mlx m X11 Xext
	LIBS_TARGET := \
				   lib/libft/libft.a \
				   lib/minilibx-linux/libmlx.a
	CFLAGS    := -D OSTYPE=linux
endif

INCS        := $(INCS) include $(dir $(LIBS_TARGET))
INCS        := $(INCS) $(addsuffix include,$(dir $(LIBS_TARGET)))

SRC_DIR     := src
SRCS        := \
			   utils/utils.c \
			   utils/strutils.c \
			   minimap.c \
			   projection.c \
			   rays_utils.c \
			   rays_hit.c \
			   rays.c \
			   player.c \
			   event.c \
			   draw.c \
			   draw_utils.c \
			   init/init_rays.c \
			   init/init_player.c \
			   init/init_texture.c \
			   init/init_mlx.c \
			   init/init_cub_attr.c \
			   init/init_cub_map.c \
			   init/init_cub.c \
			   init/init.c \
			   check_cub/check_map_2.c \
			   check_cub/check_map.c \
			   check_cub/check_tex.c \
			   check_cub/check_col.c \
			   check_cub/check_cub.c \
			   load.c \
			   main.c

SRCS        := $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR   := .build
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

CC          := clang
CFLAGS      := $(CFLAGS)   -Wall -Wextra -Werror
CPPFLAGS    := $(CPPFLAGS) $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS     := $(LDFLAGS)  $(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS      := $(LDLIBS)   $(addprefix -l,$(LIBS))

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove
# MAKE      quietly make
# DIR_DUP   duplicate directory tree
# ERR_MUTE  filter errors
# VALGRIND  valgrind command

RM          := rm -f
MAKE        := $(MAKE) --jobs --silent --no-print-directory
DIR_DUP     = mkdir -p $(@D)
VALGRIND    := valgrind -q  --dsymutil=yes --leak-check=yes --show-leak-kinds=all --track-fds=yes
ERR_MUTE	:= 2>/dev/null

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# $(NAME)   link .o -> archive
# $(LIBS)   build libraries
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal
# update    update the repo to its most recent version

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	$(info CREATED $@)

$(LIBS_TARGET):
	$(MAKE) -C $(@D) $(ERR_MUTE)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

-include $(DEPS)

clean:
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

update:
	git stash
	git pull
	git submodule update --init
	git stash pop

#----------------------------#
#   DIFFERENT CFLAGS BUILD   #
#----------------------------#
# asan      address sanitizer
# ansi      ansi c89 compliance
# every     all warnings

asan: CFLAGS    += -O0 -g3 -fsanitize=address,undefined,integer -fno-optimize-sibling-calls
asan: LDFLAGS   += -g3 -fsanitize=address,undefined,integer
asan: all

ansi: CFLAGS    += -W -pedantic -std=c89
ansi: all

every: CFLAGS   += -Weverything
every: all

#----------------------------#
#   TESTS                    #
#----------------------------#
# runv          run with valgrind
# run           vanilla run
# malloc_test   gh/ft_mallocator TODO broken

run-%: $(NAME)
	-./$(NAME) $*

vrun-%: CFLAGS  += -g3
vrun-%: $(NAME)
	-$(VALGRIND) ./$(NAME) $*

malloc_test: $(OBJS)
	clang -Wall -Wextra -Werror -g -fsanitize=undefined -rdynamic -o $@ $(OBJS) \
		-Ltest/ft_mallocator -lmallocator

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: clean fclean re malloc_test
.SILENT:

####################################### END_5 ####
