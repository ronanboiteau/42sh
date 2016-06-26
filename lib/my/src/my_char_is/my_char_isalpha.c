#include "my.h"

int		my_char_isalpha(const char letter)
{
  return ((letter >= 'A' && letter <= 'Z') ||
	  (letter >= 'a' && letter <= 'z') ||
	  (letter >= '0' && letter <= '9'));
}
