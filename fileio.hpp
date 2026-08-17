#if !defined(PETAL_FILEIO_HPP)
#define PETAL_FILEIO_HPP

#include "header.hpp"

namespace sf
{
namespace petal
{
class FileReaderView
{
private:
  std::fstream f; /* file */
  bool got_eof;

public:
  FileReaderView (const char *_V)
      : f{ std::fstream (_V, std::ios::in | std::ios::out) }, got_eof{ false }
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

  inline std::string
  read_all ()
  {
    std::stringstream buf;
    buf << f.rdbuf ();

    return buf.str ();
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

  ~FileReaderView ()
  {
    if (f)
      f.close ();
  }
};

using filereaderview_t = FileReaderView;
} // namespace petal
} // namespace sf

#endif // PETAL_FILEIO_HPP
