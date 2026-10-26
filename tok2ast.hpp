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

  /* utility functions */

  /**
   * gets the name just before token at `b`
   * assumes token at `b` is '('
   * @returns name as an expression on success, nullptr otherwise
   */
  expr_t *_get_name (size_t b);

  /**
   * gets the arglist, assumes token at b is `(`
   * @returns vector of arguments on success
   */
  sf_vec_t<expr_t *> _get_args (int &b);

  /**
   * get the entire expression by scanning
   * tokens till the end of line (bracket matched)
   * @returns expression on successful pass, nullptr otherwise
   */
  expr_t *_get_nextline (int &b);

  /**
   * get tab/scope count of the current line
   */
  int _get_tabspace (int b);

  /**
   * Instead of having separate routines
   * for vec<toks> -> vec<stmt>,
   * we have one routine to directly
   * get the statements.
   * this routine is supposed to be big
   * and hence should be used with caution.
   * @param b newline token that stars a block
   * @param t tabspace
   * @returns vec of statements
   * @note updates `b` to end-of-loop
   */
  sf_vec_t<stmt_t *> _get_block (int &b, int t);

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
