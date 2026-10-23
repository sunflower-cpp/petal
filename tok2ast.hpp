#if !defined(PETAL_TOK2AST_HPP)
#define PETAL_TOK2AST_HPP

#include "ast.hpp"
#include "header.hpp"
#include "token.hpp"
#include "tokstate.hpp"

namespace sf
{
namespace petal
{
class astsm_t
{
  toksm_t t;
  int c{ 0 }; /* cursor */

  sf_vec_t<stmt_t *> s;

  /**
   * calculate the next statement
   * updates `c`
   */
  stmt_t *_next_stmt ();

  /**
   * convert tokens t.toks[i, j] (both inclusive)
   * into expression
   */
  expr_t *_gen_expr (size_t i, size_t j);

public:
  explicit astsm_t (toksm_t _T) : t{ _T } {};

  sf_vec_t<stmt_t *> &
  get_s ()
  {
    return s;
  }

  const sf_vec_t<stmt_t *> &
  get_s () const
  {
    return s;
  }

  toksm_t &
  get_t ()
  {
    return t;
  }

  const toksm_t &
  get_t () const
  {
    return t;
  }

  inline int &
  get_c ()
  {
    return c;
  }

  inline const int &
  get_c () const
  {
    return c;
  }

  void init ();

  ~astsm_t () {}
};

} // namespace petal
} // namespace sf

#endif // PETAL_TOK2AST_HPP
