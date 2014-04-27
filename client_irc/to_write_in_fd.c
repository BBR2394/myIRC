/*
** to_write_in_fd.c for  in /home/baptiste/Documents/tp-TCPIP/my_ftp/client
** 
** Made by Bertrand-Rapello Baptiste
** Login   <bertra_l@epitech.net>
** 
** Started on  Tue Apr  8 18:05:47 2014 Bertrand-Rapello Baptiste
** Last update Sun Apr 27 16:21:43 2014 Koszyczek Laurent
*/

void	my_putchar_fd(char c, int fd)
{
  write(fd, &c, 1);
}

void	my_putstr_fd(char *str, int fd)
{
  int	c;

  c = 0;
  while (str[c] != '\0')
    my_putchar_fd(str[c++], fd);
}
