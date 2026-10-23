#if !defined(PETAL_CONST_HPP)
#define PETAL_CONST_HPP

#include "header.hpp"

namespace sf
{
namespace petal
{
enum class SfConstType
{
  CONST_INT,
  CONST_FLOAT,
  CONST_STRING,
  CONST_BOOL,
  CONST_NONE
};

class Constant
{
  SfConstType type;

public:
  explicit Constant (SfConstType _Type) : type{ _Type } {}
  virtual ~Constant () = 0;
  virtual void print () = 0;

  inline SfConstType &
  get_type ()
  {
    return type;
  }
};
} // namespace petal
} // namespace sf

#endif // PETAL_CONST_HPP
