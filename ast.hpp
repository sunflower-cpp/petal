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
  EXPR_VAR,
};

class stmt_t
{
  StmtType type;

public:
  explicit stmt_t (StmtType _Type) : type{ _Type } {}
  virtual ~stmt_t () = default;
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
  virtual ~expr_t () = default;
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
public:
  struct elifbody_str
  {
    expr_t *c;
    sf_vec_t<stmt_t *> b;
  };

private:
  expr_t *cond = nullptr;
  sf_vec_t<stmt_t *> body;
  sf_vec_t<elifbody_str> elif_body;
  sf_vec_t<stmt_t *> else_body;

public:
  explicit stmt_ifblock (expr_t *_Cond, sf_vec_t<stmt_t *> _Body,
                         sf_vec_t<elifbody_str> _ElifBody,
                         sf_vec_t<stmt_t *> _Else_Body)
      : stmt_t (StmtType::STMT_IFBLOCK), cond{ _Cond }, body{ _Body },
        elif_body{ _ElifBody }, else_body{ _Else_Body }
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

    std::cout << "body: " << body.size () << '\n';

    size_t c = 0;
    for (stmt_t *&i : body)
      {
        std::cout << "[" << (++c) << "] ";

        if (i != nullptr)
          i->print ();
        else
          std::cout << "(stmt_nullptr)\n";
      }

    std::cout << "elif_body: " << elif_body.size () << '\n';

    c = 0;
    for (elifbody_str &i : elif_body)
      {
        std::cout << "[" << (++c) << "] ";

        std::cout << "cond: ";
        if (i.c != nullptr)
          i.c->print ();
        else
          std::cout << "(expr_nullptr)\n";

        std::cout << "body: " << i.b.size () << '\n';
        size_t d = 0;
        for (stmt_t *&j : i.b)
          {
            std::cout << "[" << (++d) << "] ";

            if (j != nullptr)
              j->print ();
            else
              std::cout << "(stmt_nullptr)\n";
          }
      }

    std::cout << "else_body: " << else_body.size () << '\n';

    c = 0;
    for (stmt_t *&i : else_body)
      {
        std::cout << "[" << (++c) << "] ";

        if (i != nullptr)
          i->print ();
        else
          std::cout << "(stmt_nullptr)\n";
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

  sf_vec_t<elifbody_str> &
  get_elifbody ()
  {
    return elif_body;
  }

  const sf_vec_t<elifbody_str> &
  get_elifbody () const
  {
    return elif_body;
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
  explicit stmt_funcall (expr_t *_Name, sf_vec_t<expr_t *> _Args)
      : stmt_t (StmtType::STMT_FUNCALL), name{ _Name }, args{ _Args }
  {
  }

  ~stmt_funcall () {}

  inline expr_t *&
  get_name ()
  {
    return name;
  }

  inline expr_t *const &
  get_name () const
  {
    return name;
  }

  inline sf_vec_t<expr_t *> &
  get_args ()
  {
    return args;
  }

  inline const sf_vec_t<expr_t *> &
  get_args () const
  {
    return args;
  }

  void
  print () override
  {
    std::cout << "funcall:\nname: ";
    if (name == nullptr)
      std::cout << "(nullptr)";
    else
      name->print ();

    std::cout << "args: " << args.size () << '\n';
    for (expr_t *&i : args)
      {
        if (i != nullptr)
          i->print ();
        else
          std::cout << "(expr_nullptr)\n";
      }
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

  Constant *
  get_c ()
  {
    return c;
  }

  const Constant *
  get_c () const
  {
    return c;
  }

  ~expr_const () {}
};

class expr_funcall : public expr_t
{
  expr_t *name = nullptr;
  sf_vec_t<expr_t *> args;

public:
  explicit expr_funcall (expr_t *_Name, sf_vec_t<expr_t *> _Args)
      : expr_t (ExprType::EXPR_FUNCALL), name{ _Name }, args{ _Args }
  {
  }

  void
  print () override
  {
    std::cout << "name: ";
    if (name == nullptr)
      std::cout << "nullptr\n";
    else
      name->print ();

    std::cout << "args: " << args.size () << '\n';
    for (expr_t *&i : args)
      {
        if (i != nullptr)
          i->print ();
        else
          std::cout << "(expr_nullptr)\n";
      }
  }

  ~expr_funcall () {}
};

class expr_var : public expr_t
{
  sf_string_t n;

public:
  explicit expr_var (sf_string_t _Name)
      : expr_t (ExprType::EXPR_VAR), n{ _Name }
  {
  }

  sf_string_t &
  get_n ()
  {
    return n;
  }

  const sf_string_t &
  get_n () const
  {
    return n;
  }

  void
  print () override
  {
    std::cout << "expr_var: " << n << '\n';
  }

  ~expr_var () {}
};
} // namespace petal
} // namespace sf

#endif // PETAL_AST_HPP
