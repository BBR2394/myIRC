##
## Makefile for my_ftp in /run/media/bertra_l/fdb1a855-94cb-48d6-8a46-4dba824ee9c8/home/baptiste/rendu/PSU_2013_myftp
## 
## Made by Bertrand-Rapello Baptiste
## Login   <bertra_l@epitech.net>
## 
## Started on  Sun Apr 13 21:59:18 2014 Bertrand-Rapello Baptiste
## Last update Sun Apr 27 16:31:03 2014 Koszyczek Laurent
##

CC	=	gcc

NAME_SV	=	serveur 

NAME_CL	=	client

SRC_CL	=	client_irc/main_client.c	\
		client_irc/to_write_in_fd.c

SRC_SV	=	serveur_irc/serveur.c		\
		serveur_irc/principal.c		\
		serveur_irc/manage_client.c	\
		serveur_irc/to_write_in_fd.c

FLAG	=	-W -Wall

OBJ_SV	=	$(SRC_SV:.c=.o)

OBJ_CL	=	$(SRC_CL:.c=.o)

all:		$(NAME_SV) $(NAME_CL)

$(NAME_SV):	$(OBJ_SV)
		$(CC) -o $(NAME_SV) $(SRC_SV)

$(NAME_CL):	$(OBJ_CL)
		$(CC) -o $(NAME_CL) $(SRC_CL)


clean:
		rm -f $(OBJ_SV)
		rm -f $(OBJ_CL)

fclean: 	clean
		rm -f $(NAME_SV)
		rm -f $(NAME_CL)

re: 		fclean all
