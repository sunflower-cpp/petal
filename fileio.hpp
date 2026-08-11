#if !defined(PETAL_FILEIO_HPP)
#define PETAL_FILEIO_HPP

#include "header.hpp"

namespace sf
{
namespace petal
{
class FileView
{
private:
  std::fstream f; /* file */
  bool got_eof;

public:
  FileView (const char *_V)
      : f{ std::fstream (_V, std::ios::in | std::ios::out | std::ios::trunc) },
        got_eof{ false }
  {
  }

  inline char
  read_one () /* reads and moves cursor */
  {
    int r = f.get ();

    if (r == EOF)
      {
        got_eof = true;
        return '\0';
      }

    return static_cast<char> (r);
  }

  inline void
  rshift_back () /* move cursor towards 0 */
  {
    f.seekg (-1, std::ios::cur);
  }

  void
  rshift_front () /* move cursor away from 0 */
  {
    f.seekg (1, std::ios::cur);
  }

  inline bool
  at_end () /* end of file? */
  {
    return got_eof;
  }

  ~FileView ()
  {
    if (f)
      f.close ();
  }
};

using fileview_t = FileView;
} // namespace petal
} // namespace sf

#endif // PETAL_FILEIO_HPP
