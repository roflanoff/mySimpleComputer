#include <include/myReadKey.h>
#define switcher(a, b, c) c ? a | b : a &(~b)

int
rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
  // атрибут echo принимает 0 или 1
  // 0- отключено 1- включено
  if (echo != 1 && echo != 0)
    return -1;
  // атрибут regime принимает 0 или 1
  // 0- неканонический 1- канонический
  if (regime != 1 && regime != 0)
    return -1;
  // атрибут sigint принимает 0 или 1
  // 0- отключено 1- включено
  if (sigint != 1 && sigint != 0)
    return -1;
  struct termios new_term = TERM;

  new_term.c_lflag = switcher (new_term.c_lflag, ICANON,
                               regime); // канонический / неканонический режим
  new_term.c_lflag
      = switcher (new_term.c_lflag, ECHO,
                  echo); // включение / отключение вывода введенных символов
  new_term.c_lflag = switcher (
      new_term.c_lflag, ISIG,
      sigint); // включение / отключение прерывания по нажатию ctrl+c

  new_term.c_lflag &= ~ICANON; // канонический / неканонический режим
  new_term.c_cc[VMIN]
      = vmin; // Минимальное количество символов для неканонического ввода
  new_term.c_cc[VTIME]
      = vtime; // Время ожидания в децисекундах для неканонического ввода

  int result = tcsetattr (STDIN_FILENO, TCSAFLUSH, &new_term);
  return result;
}
