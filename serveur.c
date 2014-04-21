/*
** serveur.c for  in /home/baptiste/Documents/tp-TCPIP/tp-my_ftp
** 
** Made by Bertrand-Rapello Baptiste
** Login   <bertra_l@epitech.net>
** 
** Started on  Tue Apr  8 11:44:50 2014 Bertrand-Rapello Baptiste
** Last update Mon Apr 21 16:45:30 2014 Bertrand-Rapello Baptiste
*/

#include	<stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 2397

int	do_client(int fd1, int fd2)
{
  char	buff[512];
  int	len;

  len = read(fd1, buff, 511);
  if (len == -1)
    {
      printf("MERDE !! \n");
      return (-1);
    }
  write(fd2, buff, len);
}

int	main()
{
  int			socket_fd;
  int			rtr;
  char			*ip_client;
  int			fd_client;
  char			buf[10];
  int	c = 0;
  struct protoent	*protoent;
  struct sockaddr_in	serv_in;
  struct sockaddr_in	client_in;
  socklen_t		size;
  int	pid;
  int	fd1, fd2;
  fd_set	read_fds;

  size = sizeof(struct sockaddr_in);
  rtr = 0;
  protoent = getprotobyname("TCP");
  socket_fd = socket(AF_INET, SOCK_STREAM, protoent->p_proto);
  if (socket_fd == -1)
    printf("erreur création socket\n");

  serv_in.sin_family = AF_INET;
  serv_in.sin_port = htons(PORT);
  serv_in.sin_addr.s_addr = INADDR_ANY;
  rtr = bind(socket_fd, (struct sockaddr*)&serv_in, sizeof(struct sockaddr));
  if (rtr == -1)
    printf("erreur bind\n");

  rtr = listen(socket_fd, 12);
  if (rtr == -1)
    printf("erreurlisten\n");

  write(1, "ok3\n", 4);
  fd1 = accept(socket_fd, (struct sockaddr *)&client_in, &size);
  fd2 = accept(socket_fd, (struct sockaddr *)&client_in, &size);
  while (rtr != -1)
    {
      write(1, "ok2\n", 4);
      FD_ZERO(&read_fds);
      FD_SET(fd1, &read_fds);
      FD_SET(fd2, &read_fds);
      rtr = select(6, &read_fds, NULL, NULL, NULL);
      if (rtr != -1)
	{
	  write(1, "ok1\n", 4);
	  if (FD_ISSET(fd1, &read_fds))
	    do_client(fd1, fd2);
	  if (FD_ISSET(fd2, &read_fds))
	    do_client(fd2, fd1);
	}
      if (rtr == -1)
	{
	  printf("probleme \n");
	  sleep(1);
	}
      /*      
      fd_client = rtr;
      if (rtr == -1)
	printf("erreur  accept\n");
      ip_client = inet_ntoa(client_in.sin_addr);
      printf("ip du client %s le port de connection %d \n", ip_client, PORT);
      write(fd_client, "bonjour 1\n", 10);
      //write(socket_fd, "bonjour 2\n", 10);
      read(fd_client, buf, 10);
      write(1, buf, 10);
      */
    }
  close(fd1);
  close(fd2);
  close(socket_fd);
  return (0);
}
