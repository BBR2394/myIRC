/*
** manage_client.c for  in /home/baptiste/Documents/tp-TCPIP/deb_irc/serveur_bis
** 
** Made by Bertrand-Rapello Baptiste
** Login   <bertra_l@epitech.net>
** 
** Started on  Thu Apr 24 13:57:46 2014 Bertrand-Rapello Baptiste
** Last update Thu Apr 24 13:58:59 2014 Bertrand-Rapello Baptiste
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

void    write_on_the_rest(int fd, char *buf, int len, int max)
{
  int   c;
  char  fdbis;


  c = 4;
  fdbis = (char)fd + 48;
  while (c < max)
    {
      if (c != fd)
        {
          write(c, "perso ", 6);
          my_putchar_fd(fdbis, c);
          write(c, " say :", 6);
          write(c, buf, len);
        }
      c++;
    }
}

void    client_read(int fd, t_irc *info)
{
  int r;
  char buf[4096];

  r = read(fd, buf, 4096);
  if (r > 0)
    {
      buf[r] = '\0';
      printf("%d: %s\n", fd, buf);
      write_on_the_rest(fd, buf, r, info->fd_max);
    }
  else
    {
      printf("%d: Connection closed\n", fd);
      close(fd);
      info->last_deconnection = 1;
      info->fd_type[fd] = 'l';
    }
}

int     new_client(int fd, t_irc *info)
{
  int   new_fd;
  struct sockaddr_in client_sin;
  socklen_t             size;

  size = sizeof(struct sockaddr_in);
  new_fd = accept(fd, (struct sockaddr *)&client_sin, &size);
  info->fd_type[new_fd] = 'c';
}
