/*
** principal.c for  in /home/baptiste/Documents/tp-TCPIP/deb_irc/serveur_bis
** 
** Made by Bertrand-Rapello Baptiste
** Login   <bertra_l@epitech.net>
** 
** Started on  Thu Apr 24 13:55:18 2014 Bertrand-Rapello Baptiste
** Last update Thu Apr 24 13:57:22 2014 Bertrand-Rapello Baptiste
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

void    set_fdset(t_irc *info, fd_set  *fd_read)
{
  int   c;

  printf("set fdset\n");
  c = 0;
  while (c < info->fd_max)
    {
      //printf("dans fd set le fd ext = %d\n", c);
      if (info->fd_type[c] == 'c' || info->fd_type[c] == 's')
        {
          //printf("dans fd set le fd ext = %d\n", c);
          FD_SET(c, fd_read);
        }
      //write(1, "b", 1);
      c++;
    }
  printf("\nfin fd_set\n");
}

void    check_isset(t_irc *info, fd_set  *fd_read)
{
  int   c;

  printf("check iset\n");
  c = 0;
  while (c < info->fd_max)
    {
      if (FD_ISSET(c, fd_read))
        {
          printf("le c est egale a %d %c   !!\n", c, info->fd_type[c]);
          if (info->fd_type[c] == 'c')
            {
              printf(" je suis rentrée ici\n");
              //client -> communique avec les autres
              client_read(c, info);
            }
          else if (info->fd_type[c] == 's')
            {
              //serveur -> new client
              new_client(c, info);
            }
        }
      c++;
    }
}

int     start(t_irc *info)
{
  struct timeval tv;
  int   rtr;
  fd_set        fd_read;

  tv.tv_sec = 10;
  tv.tv_usec = 0;
  FD_ZERO(&fd_read);
  while (1)
    {
      printf("ATTENTION LE TAB %s \n", info->fd_type);
      set_fdset(info, &fd_read);
      rtr = select(info->fd_max, &fd_read, NULL, NULL, &tv);
      tv.tv_sec = 10;
      if (rtr == -1)
        {
          printf("il y a eu une erreur \n");
          //close (info->socket_fd);
          //return (-1);
        }
      printf("fin select \n");
      check_isset(info, &fd_read);
      if (info->last_deconnection == 1)
        FD_ZERO(&fd_read);
    }
}
