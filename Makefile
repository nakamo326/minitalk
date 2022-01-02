NAME = minitalk
CLI = client
SERV = server
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g
INCLUDES = -I./includes -I.
LIBFT = ./libft/libft.a

CLISRC = client.c

SERVSRC = server.c

SRCFILE = $(CLISRC) $(SERVSRC)

SRCDIRS = $(dir $(CLISRC)) $(dir $(SERVSRC))
OBJDIR = ./obj
CLIOBJS = $(addprefix $(OBJDIR)/, $(CLISRC:.c=.o))
SERVOBJS = $(addprefix $(OBJDIR)/, $(SERVSRC:.c=.o))
DEPS = $(addprefix $(OBJDIR)/, $(SRCFILE:.c=.d))

all: $(NAME)

-include $(DEPS)

$(NAME): $(CLI) $(SERV)

$(CLI): $(CLIOBJS) $(LIBFT)
	gcc $(CFLAGS) $(INCLUDES) $^ -o $@

$(SERV): $(SERVOBJS) $(LIBFT)
	gcc $(CFLAGS) $(INCLUDES) $^ -o $@

$(LIBFT):
	$(MAKE) -C ./libft

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)/$(*D)
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) clean -C ./libft
	$(RM) -r $(OBJDIR)

fclean:
	$(MAKE) fclean -C ./libft
	$(RM) -r $(OBJDIR)
	$(RM) $(CLI) $(SERV)

re: fclean all

.PHONY: all clean fclean re
