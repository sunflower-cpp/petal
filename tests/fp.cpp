#include "petal.hpp"

int
main (int argc, char const *argv[])
{
  sf::petal::filereaderview_t ft ("../../tests/test.sf");

  std::string s = ft.read_all ();

  std::cout << "Size: " << s.size () << '\n' << s << '\n';
  return 0;
}