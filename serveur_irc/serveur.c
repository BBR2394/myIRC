/*
** serveur.c for  in /home/baptiste/Documents/tp-TCPIP/deb_irc/serveur_bis
** 
** Made by Bertrand-Rapello Baptiste
** Login   <bertra_l@epitech.net>
** 
** Started on  Wed Apr 23 17:30:31 2014 Bertrand-Rapello Baptiste
** Last update Thu Apr 24 17:17:54 2014 Bertrand-Rapello Baptiste
*/

#include        <unistd.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include        <dirent.h>
#include        <sys/types.h>
#include        <sys/socket.h>
#include        <netdb.h>
#include        <netinet/in.h>
#include        <arpa/inet.h>
#include        <sys/stat.h>
#include        "serveur.h"


int                     init_serveur(int ac, char **av, int port)
{
  int                   socket_fd;
  int                   rtr;
  struct protoent       *protoent;
  struct sockaddr_in    sin_serv;

  rtr = 0;
  protoent = getprotobyname("TCP");
  socket_fd = socket(AF_INET, SOCK_STREAM, protoent->p_proto);
  if (socket_fd == -1)
    return (-1);
  sin_serv.sin_family = AF_INET;
  sin_serv.sin_port = htons(port);
  sin_serv.sin_addr.s_addr = INADDR_ANY;
  rtr = bind(socket_fd, (struct sockaddr*)&sin_serv, sizeof(struct sockaddr));
  if (rtr == -1)
    return (-1);
  rtr = listen(socket_fd, 12);
  if (rtr == -1)
    return (-1);
  return (socket_fd);
}

int	init_info(t_irc *info)
{
  int	c;

  info->fd_max = FDMAX;
  if (info->fd_max > 1020)
    return (-1);
  c = 4;
  info->fd_type = malloc(info->fd_max * sizeof(char));
  if (info->fd_type == NULL)
    return (-1);
  info->fd_type[0] = 'y';
  info->fd_type[1] = 'y';
  info->fd_type[2] = 'y';
  info->fd_type[3] = 's';
  while (c < info->fd_max)
    info->fd_type[c++] = 'l';
  info->last_deconnection = 0;
  info->u_list = NULL;
  return (0);
}

int             main(int ac, char **av)
{
  int		rtr;
  t_irc		info;

  rtr = 0;
  if (ac <= 1)
    {
      printf("usage: ./serveur [port connection]\n");
      return (-1);
    }
  init_info(&info);
  if ((info.socket_fd = init_serveur(ac, av, atoi(av[1]))) == -1)
    {
      printf("erreur when you initialize the connection\n");
      close(info.socket_fd);
      return (-1);
    }
  else
    {
      printf("the server start corectly !\n");
      start(&info);
    }
  return (0);
}
