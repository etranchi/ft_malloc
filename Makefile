MALLOC		= 	libft_malloc
SRCS		= 	src/malloc.c src/free.c src/realloc.c src/show_alloc.c
OBJS		= 	$(patsubst srcs/%.c,objs/%.o,$(SRCS))
CC			= 	gcc
CFLAGS		= 	-Wall -Wextra -Werror
INC			= 	-I./include/
PRINTF		= 	lib/ft_printf/libftprintf.a

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		= 	$(MALLOC)_$(HOSTTYPE).so

CG = \033[92m
CY = \033[93m
CE = \033[0m

all: $(NAME)	

$(NAME): $(OBJS)
	@make -C ./lib/ft_printf all
	$(CC) -shared -o $(NAME) $^ $(PRINTF)
	ln -sn $(NAME) $(MALLOC).so
	@ echo "\n\033[92m---> ft_malloc program created ✓\033[0m";

objs/%.o: srcs/%.c
	@ mkdir -p objs
	@ $(CC) $(INC) -c $< -o $@
	@ echo "\033[K$(CY)[RT] :$(CE) $(CG)Compiling $<$(CE) \033[1A";

clean:		
	@ /bin/rm -rf objs/
	@ make -C ./lib/ft_printf clean
	@ echo "\033[1;33m---> All .o files cleared\033[0m \033[92m✓\033[0m";

fclean: clean
	@ /bin/rm -f $(NAME)
	@ /bin/rm -f libft_malloc_$(HOSTTYPE).so
	@ /bin/rm -f libft_malloc.so
	@ echo "\n\033[1;33m---> Everything cleared\033[2;00m \033[92m✓\033[0m";
			
re: fclean all

.PHONY: all, clean, fclean, re