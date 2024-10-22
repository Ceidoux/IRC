NAME 		:= ircserv

# Compiler, Linker and Flags
CXX			:= c++
CXXFLAGS	+= -Wall -Werror -Wextra
CXXFLAGS	+= -MMD -MP
CXXFLAGS	+= -std=c++98
LDFLAGS		+= -std=c++98

# Directories
SRCSDIR 	:= srcs
OBJSDIR 	:= build
OBJSSUBDIR	:= $(subst $(SRCSDIR), $(OBJSDIR), $(shell find $(SRCSDIR) -type d))
INCSDIR 	:= incs

# Sources
SRCS		:=	main.cpp \
				Client.cpp \
				Channel.cpp \
				writeRPL.cpp \
				Server.cpp \
				serverCreate.cpp \
				serverCommands/commands.cpp \
				serverCommands/join.cpp \
				serverCommands/kick.cpp \
				serverCommands/nick.cpp \
				serverCommands/part.cpp \
				serverCommands/ping.cpp \
				serverCommands/privmsg.cpp \
				serverCommands/quit.cpp \
				serverCommands/topic.cpp \
				serverCommands/invite.cpp \
				serverCommands/mode.cpp \
				
# Objects
OBJS 		:= $(addprefix $(OBJSDIR)/, $(SRCS:.cpp=.o))

# Dependencies
DEPS		:= $(OBJS:.o=.d)

# Rules
.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(OBJSDIR)/%.o: $(SRCSDIR)/%.cpp | $(OBJSSUBDIR)
	$(CXX) $(CXXFLAGS) -I$(INCSDIR) -c $< -o $@

$(OBJSSUBDIR):
	mkdir -p $@

.PHONY: clean
clean: 
	rm -rf $(OBJSDIR)

.PHONY: fclean
fclean: clean
	-rm -f $(NAME)

.PHONY: re
re: fclean all

-include $(DEPS)