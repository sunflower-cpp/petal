#include "tok2ast.hpp"

namespace sf
{
namespace petal
{
stmt_t *
astsm_t::_next_stmt ()
{
  token_t *&t = this->t.get_toks ()[c];
  stmt_t *res = nullptr;

#if __SF_ENV_TYPE == __sf_env_type_debug
  bool _suppress_nptr_warning = false;
#endif

  switch (t->get_type ())
    {
    case SfTokenType::TOKEN_OPERATOR:
      {
        tok_operator *top = static_cast<tok_operator *> (t);
        const sf_string_t &tv = top->get_v ();

        if (tv == "=")
          {
            int cc = c - 1;
            int gb = 0;

            while (cc >= 0)
              {
                token_t *&d = this->t.get_toks ()[cc];

                if (d->get_type () == SfTokenType::TOKEN_OPERATOR)
                  {
                    tok_operator *tod = static_cast<tok_operator *> (d);
                    const sf_string_t &dv = tod->get_v ();

                    if (dv == "(" || dv == "{" || dv == "[")
                      gb++;
                    else if (dv == ")" || dv == "}" || dv == "]")
                      gb--;
                  }
                else if (d->get_type () == SfTokenType::TOKEN_NEWLINE && !gb)
                  break;

                if (!cc)
                  break;
                --cc;
              }

            expr_t *name = _gen_expr (cc, c - 1);
            cc = c + 1;
            gb = 0;

            while (cc < this->t.get_toks ().size ())
              {
                token_t *&d = this->t.get_toks ()[cc];

                if (d->get_type () == SfTokenType::TOKEN_OPERATOR)
                  {
                    tok_operator *tod = static_cast<tok_operator *> (d);
                    const sf_string_t &dv = tod->get_v ();

                    if (dv == "(" || dv == "{" || dv == "[")
                      gb++;
                    else if (dv == ")" || dv == "}" || dv == "]")
                      gb--;
                  }
                else if (d->get_type () == SfTokenType::TOKEN_NEWLINE && !gb)
                  break;

                if (cc == this->t.get_toks ().size ())
                  break;
                ++cc;
              }

            expr_t *value = _gen_expr (c + 1, cc - 1);

            if (res != nullptr)
              {
                delete res;
                res = nullptr;
              }

            res = static_cast<stmt_t *> (new stmt_vardecl (name, value));
            c = cc;

            goto end;
          }
        else if (tv == "(")
          {
            /**
             * many times we need to fetch
             * the name _before_ the current token
             * (name is expr_t*)
             * It is best to create a separate
             * routine for that
             */
            expr_t *name = _get_name (c);
            sf_vec_t<expr_t *> args = _get_args (c);

            res = static_cast<stmt_t *> (new stmt_funcall (name, args));

            goto end;
          }
        else
          {
            goto defl;
          }
      }
      break;

    case SfTokenType::TOKEN_KEYWORD:
      {
        tok_keyword *tk = static_cast<tok_keyword *> (t);
        const sf_string_t &sk = tk->get_v ();

        if (sk == "if")
          {
            c++; // eat 'if'
            expr_t *cond = _get_nextline (c);
            sf_vec_t<stmt_t *> block = _get_block (c, _get_tabspace (c));

            if (c < this->t.get_toks ().size ()
                && this->t.get_toks ()[c]->is ("keyword:else"))
              {
                c++; // eat 'else'

                if (c < this->t.get_toks ().size ()
                    && this->t.get_toks ()[c]->is ("keyword:if"))
                  {
                    /* else if block */
                  }
                else
                  {
                    /* else block */
                  }
              }
          }
      }
      break;

    default:
      {
      defl:;
#if __SF_ENV_TYPE == __sf_env_type_debug
        _suppress_nptr_warning = true;
#endif
      }
      break;
    }

  c++;

  /**
   * NOTE: (important) this label skips the statement `c++;` above
   * This is intentional behavior; do not change it
   */
end:;
#if __SF_ENV_TYPE == __sf_env_type_debug
  if (res == nullptr && !_suppress_nptr_warning)
    {
      dbg (std::cout << "warn: returning nullptr statement\n";);
    }
#endif
  return res;
}

expr_t *
astsm_t::_gen_expr (size_t j, size_t k)
{
  expr_t *res = nullptr;

#if __SF_ENV_TYPE == __sf_env_type_debug
  bool _suppress_nptr_warning = false;
#endif

  for (size_t i = j; i <= k; i++)
    {
      token_t *&t = this->t.get_toks ()[i];

      switch (t->get_type ())
        {
        case SfTokenType::TOKEN_BOOL:
          {
            if (res != nullptr)
              {
                delete res;
                res = nullptr;
              }

            res = static_cast<expr_t *> (
                new expr_const (static_cast<Constant *> (
                    new const_bool (static_cast<tok_bool *> (t)->get_v ()))));
          }
          break;

        case SfTokenType::TOKEN_INT:
          {
            if (res != nullptr)
              {
                delete res;
                res = nullptr;
              }

            res = static_cast<expr_t *> (
                new expr_const (static_cast<Constant *> (
                    new const_int (static_cast<tok_int *> (t)->get_v ()))));
          }
          break;

        case SfTokenType::TOKEN_FLOAT:
          {
            if (res != nullptr)
              {
                delete res;
                res = nullptr;
              }

            res = static_cast<expr_t *> (
                new expr_const (static_cast<Constant *> (new const_float (
                    static_cast<tok_float *> (t)->get_v ()))));
          }
          break;

        case SfTokenType::TOKEN_STRING:
          {
            if (res != nullptr)
              {
                delete res;
                res = nullptr;
              }

            res = static_cast<expr_t *> (
                new expr_const (static_cast<Constant *> (new const_string (
                    static_cast<tok_string *> (t)->get_v ()))));
          }
          break;

        case SfTokenType::TOKEN_IDENTIFIER:
          {
            if (res != nullptr)
              {
                delete res;
                res = nullptr;
              }

            res = static_cast<expr_t *> (
                new expr_var (static_cast<tok_identifier *> (t)->get_v ()));
          }
          break;

        case SfTokenType::TOKEN_NONE:
          {
            if (res != nullptr)
              {
                delete res;
                res = nullptr;
              }

            res = static_cast<expr_t *> (
                new expr_const (static_cast<Constant *> (new const_none ())));
          }
          break;

        default:
#if __SF_ENV_TYPE == __sf_env_type_debug
          _suppress_nptr_warning = true;
#endif
          break;
        }
    }

end:;
#if __SF_ENV_TYPE == __sf_env_type_debug
  if (res == nullptr && !_suppress_nptr_warning)
    dbg (std::cout << "warn: returning nullptr expression\n";);
#endif
  return res;
}

expr_t *
astsm_t::_get_name (size_t b)
{
  if (!b)
    return nullptr;

  int gb = 0;
  int bb = static_cast<int> (b - 1);

  while (bb >= 0)
    {
      token_t *d = this->t.get_toks ()[bb];

      if (d->get_type () == SfTokenType::TOKEN_OPERATOR)
        {
          tok_operator *tod = static_cast<tok_operator *> (d);
          const sf_string_t &dv = tod->get_v ();

          if (dv == "(" || dv == "{" || dv == "[")
            gb++;
          else if (dv == ")" || dv == "}" || dv == "]")
            gb--;
        }
      else if (d->get_type () == SfTokenType::TOKEN_NEWLINE && !gb)
        break;

      --bb;
    }

  /* this should be unsafe */
  return _gen_expr (static_cast<size_t> (bb), b - 1);
}

sf_vec_t<expr_t *>
astsm_t::_get_args (int &b)
{
  b++; // eat '('
  sf_vec_t<expr_t *> res;

  int gb = 0;
  int lp = static_cast<int> (b);

  while (b < this->t.get_toks ().size ())
    {
      token_t *d = this->t.get_toks ()[b];

      if (d->get_type () == SfTokenType::TOKEN_OPERATOR)
        {
          tok_operator *tod = static_cast<tok_operator *> (d);
          const sf_string_t &dv = tod->get_v ();

          if (dv == ")" && !gb)
            {
              res.push_back (_gen_expr (lp, b - 1));
              break;
            }

          if (dv == "(" || dv == "{" || dv == "[")
            gb++;
          else if (dv == ")" || dv == "}" || dv == "]")
            gb--;

          if (dv == "," && !gb)
            {
              if (lp == b)
                {
                  if (b + 1 < this->t.get_toks ().size ()
                      && this->t.get_toks ()[b + 1]->get_type ()
                             == SfTokenType::TOKEN_OPERATOR
                      && static_cast<tok_operator *> (
                             this->t.get_toks ()[b + 1])
                                 ->get_v ()
                             == ")")
                    break;

                  throw sf_string_t ("syntax error");
                }

              res.push_back (_gen_expr (lp, b - 1));
              lp = b + 1;
            }
        }

      b++;
    }

end:;
  return res;
}

void
astsm_t::init ()
{
  while (c < t.get_toks ().size ())
    {
      stmt_t *st = _next_stmt ();
      if (st != nullptr)
        st->print ();
      s.push_back (st);
    }
}

expr_t *
astsm_t::_get_nextline (int &b)
{
  int bb = static_cast<int> (b);
  int gb = 0;

  while (b < this->t.get_toks ().size ())
    {
      token_t *d = this->t.get_toks ()[b];

      if (d->get_type () == SfTokenType::TOKEN_OPERATOR)
        {
          tok_operator *tod = static_cast<tok_operator *> (d);
          const sf_string_t &dv = tod->get_v ();

          if (dv == "(" || dv == "{" || dv == "[")
            gb++;
          else if (dv == ")" || dv == "}" || dv == "]")
            gb--;
        }

      if (d->get_type () == SfTokenType::TOKEN_NEWLINE && !gb)
        break;

      b++;
    }

  return _gen_expr (bb, b);
}

int
astsm_t::_get_tabspace (int b)
{
  int t = 0;
  int gb = 0;

  while (b >= 0)
    {
      token_t *d = this->t.get_toks ()[b];

      if (d->get_type () == SfTokenType::TOKEN_OPERATOR)
        {
          tok_operator *tod = static_cast<tok_operator *> (d);
          const sf_string_t &dv = tod->get_v ();

          if (dv == "(" || dv == "{" || dv == "[")
            gb++;
          else if (dv == ")" || dv == "}" || dv == "]")
            gb--;
        }

      if (d->get_type () == SfTokenType::TOKEN_SPACE && !gb)
        {
          t = static_cast<tok_space *> (d)->get_v ();
          goto end;
        }

      b--;
    }

end:;
  return t;
}

sf_vec_t<stmt_t *>
astsm_t::_get_block (int &b, int t)
{
  int bb = b;
  sf_vec_t<stmt_t *> res;

end:;
  return res;
}
} // namespace petal
} // namespace sf
