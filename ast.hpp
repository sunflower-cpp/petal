#if !defined(PETAL_AST_HPP)
#define PETAL_AST_HPP

#include "const.hpp"
#include "header.hpp"

namespace sf
{
namespace petal
{
enum class StmtType
{
  STMT_VARDECL,
  STMT_IFBLOCK,
  STMT_FUNCALL,
};

enum class ExprType
{
  EXPR_CONST,
  EXPR_FUNCALL,
};

class stmt_t
{
  StmtType type;

public:
  explicit stmt_t (StmtType _Type) : type{ _Type } {}
  virtual ~stmt_t () = 0;
  virtual void print () = 0;

  inline StmtType &
  get_type ()
  {
    return type;
  }
};

class expr_t
{
  ExprType type;

public:
  explicit expr_t (ExprType _Type) : type{ _Type } {}
  virtual ~expr_t () = 0;
  virtual void print () = 0;

  inline ExprType &
  get_type ()
  {
    return type;
  }
};

/* ----- Statements ----- */
class stmt_vardecl : public stmt_t
{
  expr_t *name = nullptr;
  expr_t *value = nullptr;

public:
  explicit stmt_vardecl (expr_t *_N, expr_t *_V)
      : stmt_t (StmtType::STMT_VARDECL), name{ _N }, value{ _V }
  {
  }

  ~stmt_vardecl () {}

  void
  print () override
  {
    std::cout << "[stmt_vardecl] name = ";
    if (name)
      name->print ();
    else
      std::cout << "(nullptr)\n";

    std::cout << "value = ";
    if (value)
      value->print ();
  };

  expr_t *
  get_name ()
  {
    return name;
  }

  const expr_t *
  get_name () const
  {
    return name;
  }

  expr_t *
  get_value ()
  {
    return value;
  }

  const expr_t *
  get_value () const
  {
    return value;
  }
};

class stmt_ifblock : public stmt_t
{
  expr_t *cond = nullptr;
  sf_vec_t<stmt_t *> body;
  /* TODO: elifs */
  sf_vec_t<stmt_t *> else_body;

public:
  explicit stmt_ifblock (expr_t *_Cond, sf_vec_t<stmt_t *> _Body,
                         sf_vec_t<stmt_t *> _Else_Body)
      : stmt_t (StmtType::STMT_IFBLOCK), cond{ _Cond }, body{ _Body },
        else_body{ _Else_Body }
  {
  }

  ~stmt_ifblock () {}

  void
  print () override
  {
    std::cout << "[stmt_ifblock] cond = ";

    if (cond)
      cond->print ();
    else
      std::cout << "(nullptr)\n";

    std::cout << "body: " << body.size ();

    size_t c = 0;
    for (auto &&i : body)
      {
        std::cout << "[" << (++c) << "] ";
        i->print ();
      }
  }

  expr_t *
  get_cond ()
  {
    return cond;
  }

  const expr_t *
  get_cond () const
  {
    return cond;
  }

  sf_vec_t<stmt_t *> &
  get_body ()
  {
    return body;
  }

  const sf_vec_t<stmt_t *> &
  get_body () const
  {
    return body;
  }

  sf_vec_t<stmt_t *> &
  get_else_body ()
  {
    return else_body;
  }

  const sf_vec_t<stmt_t *> &
  get_else_body () const
  {
    return else_body;
  }
};

class stmt_funcall : public stmt_t
{
  expr_t *name = nullptr;
  sf_vec_t<expr_t *> args;

public:
  explicit stmt_funcall () : stmt_t (StmtType::STMT_FUNCALL) {}
  ~stmt_funcall () {}

  void
  print () override
  {
    std::cout << "name: ";
    if (name == nullptr)
      std::cout << "(nullptr)";
    else
      name->print ();

    std::cout << "args: " << args.size () << '\n';
    for (expr_t *&i : args)
      i->print ();
  }
};

/* ----------- Expressions ----------- */
class expr_const : public expr_t
{
  Constant *c = nullptr;

public:
  explicit expr_const (Constant *_C = nullptr)
      : expr_t (ExprType::EXPR_CONST), c{ _C }
  {
  }

  void
  print () override
  {
    if (c == nullptr)
      std::cout << "(const_nullptr)\n";
    else
      c->print ();
  }

  ~expr_const () {}
};
} // namespace petal
} // namespace sf

#endif // PETAL_AST_HPP
