#include "petal.hpp"

#define TEST(X) test##X ()

void TEST (1)
{
  sf::petal::filereaderview_t ft ("../../tests/test.sf");

  std::string s = ft.read_all ();

  std::cout << "Size: " << s.size () << '\n' << s << '\n';

  using namespace sf;
  petal::toksm_t t (s);

  t.init ();

  std::cout << t.get_toks ().size () << '\n';
  for (auto &&i : t.get_toks ())
    {
      i->print ();
    }
}

void TEST (2) {}

int
main (int argc, char const *argv[])
{
  TEST (1);
  return 0;
}