#if !defined(PETAL_AST_HPP)
#define PETAL_AST_HPP

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
};

class expr_t
{
  ExprType type;

public:
  explicit expr_t (ExprType _Type) : type{ _Type } {}
  virtual ~expr_t () = 0;
  virtual void print () = 0;
};
} // namespace petal
} // namespace sf

#endif // PETAL_AST_HPP
