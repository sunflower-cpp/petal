#include "tokstate.hpp"

namespace sf
{
namespace petal
{
token_t *
toksm_t::_next_tok ()
{
  token_t *r = nullptr;

  char c = *rp++;

  if (c >= '0' && c <= '9')
    {
      char num[32];
      size_t nl = 0;

      num[nl++] = c;
      bool saw_dot = false;

    l1:;
      do
        {
          num[nl++] = c;
        }
      while (c >= '0' && c <= '9');

      if (c == '.')
        {
          if (!saw_dot)
            {
              saw_dot = true;
              goto l1;
            }
        }

      --rp;
      goto end;
    }

  switch (c)
    {
    case '\n':
      {
        r = static_cast<token_t *> (new tok_newline ());
        goto end;
      }
      break;

    default:
      break;
    }

end:
  return r;
}
} // namespace petal
} // namespace sf
