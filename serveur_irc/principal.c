/*
** principal.c for  in /home/baptiste/Documents/tp-TCPIP/deb_irc/serveur_bis
** 
** Made by Bertrand-Rapello Baptiste
** Login   <bertra_l@epitech.net>
** 
** Started on  Thu Apr 24 13:55:18 2014 Bertrand-Rapello Baptiste
** Last update Sun Apr 27 16:29:07 2014 Koszyczek Laurent
*/

#include		<unistd.h>
#include		<stdio.h>
#include		<stdlib.h>
#include		<string.h>
#include		<dirent.h>
#include		<sys/types.h>
#include		<sys/socket.h>
#include		<netdb.h>
#include		<netinet/in.h>
#include		<arpa/inet.h>
#include		<sys/stat.h>
#include		"serveur.h"

void			set_fdset(t_irc *info, fd_set  *fd_read)
{
  int			c;

  c = 0;
  while (c < info->fd_max)
    {
      if (info->fd_type[c] == 'c' || info->fd_type[c] == 's')
        {
          FD_SET(c, fd_read);
        }
      c++;
    }
}

void			check_isset(t_irc *info, fd_set  *fd_read)
{
  int			c;

  c = 0;
  while (c < info->fd_max)
    {
      if (FD_ISSET(c, fd_read))
        {
          if (info->fd_type[c] == 'c')
	    client_read(c, info);
          else if (info->fd_type[c] == 's')
	    new_client(c, info);
        }
      c++;
    }
}

int			start(t_irc *info)
{
  struct timeval	tv;
  int			rtr;
  fd_set		fd_read;

  tv.tv_sec = 10;
  tv.tv_usec = 0;
  FD_ZERO(&fd_read);
  while (1)
    {
      set_fdset(info, &fd_read);
      rtr = select(info->fd_max, &fd_read, NULL, NULL, &tv);
      tv.tv_sec = 10;
      if (rtr == -1)
        {
          printf("there was an error\n");
          close (info->socket_fd);
          return (-1);
        }
      check_isset(info, &fd_read);
      if (info->last_deconnection == 1)
        FD_ZERO(&fd_read);
    }
}
