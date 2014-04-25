/*
** serveur.h for  in /home/baptiste/Documents/tp-TCPIP/deb_irc/serveur_bis
** 
** Made by Bertrand-Rapello Baptiste
** Login   <bertra_l@epitech.net>
** 
** Started on  Wed Apr 23 17:32:05 2014 Bertrand-Rapello Baptiste
** Last update Fri Apr 25 20:25:41 2014 Bertrand-Rapello Baptiste
*/

#ifndef SERVEUR_H_
# define SERVEUR_H_

# define FDMAX 10
# define DEFAULT_PORT 2394

typedef struct	s_usr
{
  char	*nick;
  char	*chan_name;
  int	id_chan;
  int	fd;
  struct s_usr	*next;
}		t_usr;

typedef struct	s_irc
{
  int	socket_fd;
  int	fd_max;
  char	*fd_type;
  int	last_deconnection;
  struct s_usr	**u_list;
}		t_irc;

#endif
