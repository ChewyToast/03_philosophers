# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/03 11:48:41 by bruno             #+#    #+#              #
#    Updated: 2022/12/03 21:00:03 by bmoll-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

FILES	=	philo.c\
			utils.c\
			libft.c\
			parsing.c\
			simulation.c

SRC		=	$(addprefix $(SRC_DIR)/, $(FILES))

OBJS	=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

DEPS	=	$(addprefix $(DEPS_DIR)/, $(FILES:.c=.d))

MKF		=	Makefile

SRC_DIR	=	mandatory/src

OBJ_DIR		=	.obj

DEPS_DIR	=	.deps

UNAME		=	$(shell uname)

FLAGS		=	-Wall -Werror -Wextra

FLAGS_MMD	=	-Wall -Werror -Wextra -MMD -MP

GCC			:= gcc
ifeq ($(UNAME), Linux)
	GCC += -pthread
endif

all:
			@$(MAKE) $(NAME)

clean:
			@echo "Deleting files .o and .d"
			@rm -rf $(OBJ_DIR)
			@rm -rf $(DEPS_DIR)

fclean:
			@$(MAKE) clean
			@echo "Deleting philo"
			@rm -f $(NAME) $(NAME_BNS)

re:
			@$(MAKE) fclean
			@$(MAKE) all


$(NAME):	$(OBJ_DIR) $(DEPS_DIR) $(OBJS)
			@$(GCC) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(MKF)
			@echo "compiling: ->{$(notdir $<)}<-"
			$(GCC) $(FLAGS_MMD) -c $< -o $@
			@mv $(patsubst %.o, %.d, $@) $(DEPS_DIR)/

$(OBJ_DIR):
			@mkdir -p -m700 $(OBJ_DIR)

$(DEPS_DIR):
			@mkdir -p -m700 $(DEPS_DIR)

-include $(DEPS)

.PHONY:	all clean fclean re