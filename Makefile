NAME = minitalk
CLI = client
SERV = server
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes -I.
LIBFT = ./libft/libft.a

CLISRC =

SERVSRC =	server.c

SRCDIRS = $(dir $(CLISRC)) $(dir $(SERVSRC))
OBJDIR = ./obj
BINDIRS = $(addprefix $(OBJDIR)/, $(SRCDIRS))
CLIOBJS = $(addprefix $(OBJDIR)/, $(CLISRC:.c=.o))
SERVOBJS = $(addprefix $(OBJDIR)/, $(SERVSRC:.c=.o))

all: $(NAME)

$(NAME): $(CLI) $(SERV)

$(CLI): $(CLIOBJS) $(LIBFT)
	gcc -g $(CFLAGS) $^ $(INCLUDES) -o $@

$(SERV): $(SERVOBJS) $(LIBFT)
	gcc -g $(CFLAGS) $^ $(INCLUDES) -o $@

$(LIBFT):
	$(MAKE) bonus -C ./libft

$(OBJDIR)/%.o: %.c
	@mkdir -p $(BINDIRS)
	gcc -g $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) clean -C ./libft
	$(RM) -r $(OBJDIR)

fclean:
	$(MAKE) fclean -C ./libft
	$(RM) $(CLI) $(SERV)
	$(RM) -r $(OBJDIR)

re: fclean all

.PHONY: all clean fclean re
