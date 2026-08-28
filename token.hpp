#if !defined(PETAL_TOKEN_HPP)
#define PETAL_TOKEN_HPP

#include "header.hpp"

namespace sf
{
namespace petal
{
/**
 * "TokenType" on Windows is already
 * used in standard.
 * Hurts, but I'm used to it.
 */
enum class SfTokenType
{
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
};
} // namespace petal
} // namespace petal

#endif // PETAL_TOKEN_HPP
