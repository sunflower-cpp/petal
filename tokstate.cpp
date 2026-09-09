#include "tokstate.hpp"

namespace sf
{
namespace petal
{
bool
_is_valid_operator (char c)
{
  const char *vops = "~!%^&*()-+=[]{}\\|:,.<>/";
  const int vl = strlen (vops);

  // avoiding strnstr/strstr
  size_t i = 0;
  while (vops[i] != '\0')
    {
      if (vops[i] == c)
        return true;
      i++;
    }

  return false;
}

void
_make_op (char *r, char f, char *b)
{
  r[0] = r[1] = r[2] = r[3] = '\0';

  char g = *b;
  char h = g ? *(b + 1) : '\0';
  char i = h ? *(b + 2) : '\0';

  switch (f)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '&':
    case '|':
    case '%':
    case '!':
    case '=':
      {
        r[0] = f;

        if (g == '=')
          r[1] = g;
      }
      break;

    case '>':
    case '<':
      {
        r[0] = f;

        if (g == f)
          {
            r[1] = g;

            if (h == '=')
              r[2] = h;
          }
        else if (g == '=')
          r[1] = g;
      }

    case ':':
    case '{':
    case '}':
    case '[':
    case ']':
    case '(':
    case ')':
    case '\\':
    case ',':
    case '.':
      {
        r[0] = f;
      }

    default:
      break;
    }
}

token_t *
toksm_t::_next_tok ()
{
  token_t *r = nullptr;

  char c = *rp++;

  if (c == '\0')
    {
      r = static_cast<token_t *> (new tok_eof ());
      return r;
    }

  if (c == '\'' || c == '"')
    {
      const char qt = c;
      sf_string_t vl;

      while (*rp != '\0' && *rp != qt)
        {
          if (*rp == '\\' && *(rp + 1) != '\0')
            {
              ++rp;

              switch (*rp)
                {
                case 'n':
                  vl += '\n';
                  break;
                case 't':
                  vl += '\t';
                  break;
                default:
                  vl += *rp;
                  break;
                }
            }
          else
            {
              vl += *rp;
            }

          ++rp;
        }

      if (*rp == qt)
        ++rp;

      r = static_cast<token_t *> (new tok_string (vl));
      goto end;
    }

  else if (c >= '0' && c <= '9')
    {
      char num[32];
      size_t nl = 0;

      bool saw_dot = false;

    l1:;
      do
        {
          num[nl++] = c;
          c = *rp++;
        }
      while (c != '\0' && c >= '0' && c <= '9' && nl < 32);

      if (nl < 32)
        num[nl] = '\0';
      else
        num[31] = '\0';

      if (c == '.')
        {
          if (!saw_dot)
            {
              saw_dot = true;
              goto l1;
            }
        }

      // std::cout << double (atof (num)) << '\n';
      if (!saw_dot)
        r = static_cast<token_t *> (new tok_int (atoi (num)));
      else
        r = static_cast<token_t *> (new tok_float (atof (num)));

      --rp;
      goto end;
    }

  else if (isalpha (c) || c == '_')
    {
      char idt[64];
      size_t inl = 0;

      do
        {
          idt[inl++] = c;
          c = *rp++;
        }
      while (c != '\0' && (isalnum (c) || c == '_') && inl < 64);

      if (inl >= 64)
        inl = 63;

      idt[inl] = '\0';

      r = static_cast<token_t *> (new tok_identifier (idt));
      --rp;

      goto end;
    }
  else if (_is_valid_operator (c))
    {
      char op[4];

      _make_op (op, c, rp);
      r = static_cast<token_t *> (new tok_operator (op));

      rp += strlen (op) - 1;
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

    case ' ':
    case '\t':
      {
        int n = 1;

        if (c == '\t')
          n = 3;

        if (toks.size ())
          {
            if (toks.back ()->get_type () == SfTokenType::TOKEN_SPACE)
              {
                static_cast<tok_space *> (toks.back ())->get_v () += n;
                return _next_tok ();
              }
            else
              {
                if ((*rp == ' ' || *rp == '\t')
                    && toks.back ()->get_type () == SfTokenType::TOKEN_NEWLINE)
                  {
                    if (*rp == ' ')
                      r = static_cast<token_t *> (new tok_space (n + 1));
                    else if (*rp == '\t')
                      r = static_cast<token_t *> (new tok_space (n + 3));
                    rp++;
                  }
                else
                  {
                    return _next_tok ();
                  }
              }
          }
        else
          {
            if (*rp == ' ' || *rp == '\t')
              {
                if (*rp == ' ')
                  n++;
                else
                  n += 3;
                r = static_cast<token_t *> (new tok_space (n));
                rp++;
              }
            else
              {
                return _next_tok ();
              }
          }
      }
      break;

    default:
      break;
    }

end:
  return r;
}

token_t::~token_t () {}
} // namespace petal
} // namespace sf
