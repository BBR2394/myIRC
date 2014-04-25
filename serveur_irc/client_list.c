/*
** client_list.c for  in /home/baptiste/Documents/tp-TCPIP/deb_irc/serveur_irc
** 
** Made by Bertrand-Rapello Baptiste
** Login   <bertra_l@epitech.net>
** 
** Started on  Thu Apr 24 22:36:49 2014 Bertrand-Rapello Baptiste
** Last update Fri Apr 25 15:30:06 2014 Bertrand-Rapello Baptiste
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

int	show_list(t_usr **list)
{
  t_usr	*cpy;

  printf("le shox list \n");
  cpy = *list;
  while (cpy != NULL)
    {
      printf("utilisateur : %s\n", cpy->nick);
      cpy = cpy->next;
    }
}

int	add_link(t_usr **list, int fd)
{
  t_usr	*cpy;

  printf("je crée la liste ...\n");
  cpy = malloc(sizeof(t_usr));
  if (cpy != NULL)
    return (-1);
  cpy->fd = fd;
  cpy->id_chan = 0;
  //cpy->nick = strdup("unknpown");
  cpy->nick = malloc(9*sizeof(char));
  cpy->nick[0] = 'a';
  cpy->nick[1] = 'z';
  cpy->nick[2] = '\0';
  //cpy->nick[0] = '\0';
  //cpy->nick = strcat(cpy->nick, "unknown");
  cpy->chan_name = NULL;
  cpy->next = *list;
  *list = cpy;
  printf("le nom : %s\n", cpy->nick);
  return (0);
}
