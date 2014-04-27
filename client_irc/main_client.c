/*
** client.c for $ in /home/baptiste/Documents/tp-TCPIP/tp-my_ftp
** 
** Made by Bertrand-Rapello Baptiste
** Login   <bertra_l@epitech.net>
** 
** Started on  Tue Apr  8 14:10:30 2014 Bertrand-Rapello Baptiste
** Last update Sun Apr 27 16:21:29 2014 Koszyczek Laurent
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netdb.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>

int	reset_buf(char *str, int len)
{
  int	c;

  c = 0;
  while (c < len)
    str[c++] = '\0';
}

int	do_action(int fd, fd_set *fd_read, char *line)
{
  int	rtr;

  rtr = 0;
  if (FD_ISSET(0, fd_read))
    {
      rtr = read(0, line, 511);
      write(fd, line, rtr);
    }
  else if (FD_ISSET(3, fd_read))
    {
      line[0] = '\0';
      rtr = read(fd, line, 511);
      if (rtr == -1)
	{
	  printf("the serve has quit  ...\n");
	  return (-1);
	}
      my_putstr_fd(line, 1);
    }
}

int		start_prompt(int fd_serv)
{
  size_t		len;
  fd_set		fd_read;
  struct timeval	tv;
  char  *line;
  int	rtr;

  rtr = 0;
  line = malloc(512*sizeof(char));
  if (line == NULL)
    return (-1);
  tv.tv_sec = 10;
  tv.tv_usec = 0;
  FD_ZERO(&fd_read);
  while (rtr != -1)
    {
      FD_SET(0, &fd_read);
      FD_SET(fd_serv, &fd_read);
      rtr = select(4, &fd_read, NULL, NULL, &tv);
      tv.tv_sec = 10;
      if (do_action(fd_serv, &fd_read, line) == -1)
	return (-1);
      reset_buf(line, 512);
    }
}

int			init_client(char **av, struct sockaddr_in *addr_in)
{
  struct protoent	*protoent;
  int			socket_fd;

  protoent = getprotobyname("TCP");
  socket_fd = socket(AF_INET, SOCK_STREAM, protoent->p_proto);
  if (socket_fd == -1)
    {
      printf("probleme with the socket.\n");
      return (-1);
    }
  addr_in->sin_family = AF_INET;
  addr_in->sin_port = htons(atoi(av[2]));
  addr_in->sin_addr.s_addr = inet_addr(av[1]);
  return (socket_fd);
}

int			main(int ac, char **av)
{
  int			socket_fd;
  struct protoent	*protoent;
  struct sockaddr_in	addr_in;

  if (ac <= 2)
    {
      printf("usage: ./client [IP's Server] [port's connection]\n");
      return (0);
    }
  if ((socket_fd = init_client(av, &addr_in)) == -1)
    return (-1);
  if (connect(socket_fd, (const struct sockaddr *)&addr_in,
		sizeof(struct sockaddr)) == -1)
    {
      printf("connection failed ...\n");
      close(socket_fd);
      return (-1);
    }
  else
    printf("connection etablished !!\n");
  start_prompt(socket_fd);
  close(socket_fd);
  return (0);
}
