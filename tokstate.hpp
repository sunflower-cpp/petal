#if !defined(PETAL_TOKSTATE_HPP)
#define PETAL_TOKSTATE_HPP

#include "header.hpp"
#include "token.hpp"

namespace sf
{
namespace petal
{
/*
  TOKEN_STRING = 0,
  TOKEN_INT = 1,
  TOKEN_FLOAT = 2,
  TOKEN_OPERATOR = 3,
  TOKEN_NEWLINE = 4,
  TOKEN_SPACE = 5,
  TOKEN_EOF = 6,
  TOKEN_IDENTIFIER = 7,
  TOKEN_KEYWORD = 8,
  TOKEN_BOOL = 9,
  TOKEN_COUNT,
*/

class token_t
{
protected:
  SfTokenType type;

public:
  explicit token_t (SfTokenType _Type) : type{ _Type } {}
  virtual ~token_t () = 0;
  virtual inline void print () = 0;

  inline const SfTokenType &
  get_type ()
  {
    return type;
  }
};

class tok_string : public token_t
{
  sf_string_t v;

public:
  explicit tok_string (sf_string_t _V)
      : token_t (SfTokenType::TOKEN_STRING), v{ _V }
  {
  }

  ~tok_string () override {}

  const sf_string_t &
  get_v () const
  {
    return v;
  }

  inline void
  print () override
  {
    std::cout << "[tok_string] (v) " << v << '\n';
  }
};

class tok_int : public token_t
{
  sf_int_t v;

public:
  explicit tok_int (int _V) : token_t (SfTokenType::TOKEN_INT), v{ _V } {}
  ~tok_int () override {}

  int
  get_v () const
  {
    return v;
  }

  inline void
  print () override
  {
    std::cout << "[tok_int] (v) " << v << '\n';
  }
};

class tok_float : public token_t
{
  sf_float_t v;

public:
  explicit tok_float (float _V) : token_t (SfTokenType::TOKEN_FLOAT), v{ _V }
  {
  }

  ~tok_float () override {}

  float
  get_v () const
  {
    return v;
  }

  inline void
  print () override
  {
    std::cout << "[tok_float] (v) " << std::setprecision (15) << v << '\n';
  }
};

class tok_operator : public token_t
{
  sf_string_t v;

public:
  explicit tok_operator (sf_string_t _V)
      : token_t (SfTokenType::TOKEN_OPERATOR), v{ _V }
  {
  }

  ~tok_operator () override {}

  const sf_string_t &
  get_v () const
  {
    return v;
  }

  inline void
  print () override
  {
    std::cout << "[tok_operator] (v) " << v << '\n';
  }
};

class tok_newline : public token_t
{
public:
  tok_newline () : token_t (SfTokenType::TOKEN_NEWLINE) {}
  ~tok_newline () override {}

  inline void
  print () override
  {
    std::cout << "[tok_newline]" << '\n';
  }
};

class tok_space : public token_t
{
  sf_int_t v;

public:
  explicit tok_space (sf_int_t _V)
      : token_t (SfTokenType::TOKEN_SPACE), v{ _V }
  {
  }

  ~tok_space () override {}

  sf_int_t &
  get_v ()
  {
    return v;
  }

  inline void
  print () override
  {
    std::cout << "[tok_space] (v) " << v << '\n';
  }
};

class tok_eof : public token_t
{
public:
  tok_eof () : token_t (SfTokenType::TOKEN_EOF) {}
  ~tok_eof () override {}

  inline void
  print () override
  {
    std::cout << "[tok_eof]" << '\n';
  }
};

class tok_identifier : public token_t
{
  sf_string_t v;

public:
  explicit tok_identifier (sf_string_t _V)
      : token_t (SfTokenType::TOKEN_IDENTIFIER), v{ _V }
  {
  }

  ~tok_identifier () override {}

  const sf_string_t &
  get_v () const
  {
    return v;
  }

  inline void
  print () override
  {
    std::cout << "[tok_identifier] (v) " << v << '\n';
  }
};

class tok_keyword : public token_t
{
  sf_string_t v;

public:
  explicit tok_keyword (sf_string_t _V)
      : token_t (SfTokenType::TOKEN_KEYWORD), v{ _V }
  {
  }

  ~tok_keyword () override {}

  const sf_string_t &
  get_v () const
  {
    return v;
  }

  inline void
  print () override
  {
    std::cout << "[tok_keyword] (v) " << v << '\n';
  }
};

class tok_bool : public token_t
{
  sf_bool_t v;

public:
  explicit tok_bool (bool _V) : token_t (SfTokenType::TOKEN_BOOL), v{ _V } {}
  ~tok_bool () override {}

  bool
  get_v () const
  {
    return v;
  }

  inline void
  print () override
  {
    std::cout << "[tok_bool] (v) " << v << '\n';
  }
};

class toksm_t
{
private:
  sf_vec_t<token_t *> toks;
  sf_string_t raw;
  char *rp; /* cursor */

  token_t *_next_tok ();

public:
  explicit toksm_t (sf_string_t _Raw) : raw{ _Raw }
  {
    rp = const_cast<char *> (raw.data ());
  }

  bool
  init () /* start processing tokens */
  {
    token_t *t = _next_tok ();
    while (t && t->get_type () != SfTokenType::TOKEN_EOF)
      {
        toks.push_back (t);
        t = _next_tok ();
      }

    if (t && t->get_type () == SfTokenType::TOKEN_EOF)
      delete t;

    return true;
  }

  sf_vec_t<token_t *> &
  get_toks ()
  {
    return toks;
  }

  ~toksm_t () {}
};

} // namespace petal
} // namespace sf

#endif // PETAL_TOKSTATE_HPP
