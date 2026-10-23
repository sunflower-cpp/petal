#if !defined(PETAL_CONST_HPP)
#define PETAL_CONST_HPP

#include "header.hpp"

#include <iostream>
#include <string>
#include <utility>

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
  virtual ~Constant () = default;
  virtual void print () = 0;

  inline SfConstType &
  get_type ()
  {
    return type;
  }
};

class const_int : public Constant
{
public:
  int value;

  explicit const_int (int _Value)
      : Constant{ SfConstType::CONST_INT }, value{ _Value }
  {
  }

  void
  print () override
  {
    std::cout << "const_int: " << value << '\n';
  }

  ~const_int () {}
};

class const_float : public Constant
{
public:
  float value;

  explicit const_float (float _Value)
      : Constant{ SfConstType::CONST_FLOAT }, value{ _Value }
  {
  }

  void
  print () override
  {
    std::cout << "const_float: " << value << '\n';
  }

  ~const_float () {}
};

class const_string : public Constant
{
public:
  std::string value;

  explicit const_string (std::string _Value)
      : Constant{ SfConstType::CONST_STRING }, value{ std::move (_Value) }
  {
  }

  void
  print () override
  {
    std::cout << "const_string: " << value << '\n';
  }

  ~const_string () {}
};

class const_bool : public Constant
{
public:
  bool value;

  explicit const_bool (bool _Value)
      : Constant{ SfConstType::CONST_BOOL }, value{ _Value }
  {
  }

  void
  print () override
  {
    std::cout << "const_bool: " << (value ? "true\n" : "false\n");
  }

  ~const_bool () {}
};

class const_none : public Constant
{
public:
  const_none () : Constant{ SfConstType::CONST_NONE } {}

  void
  print () override
  {
    std::cout << "const: none\n";
  }

  ~const_none () {}
};

} // namespace petal
} // namespace sf

#endif // PETAL_CONST_HPP
