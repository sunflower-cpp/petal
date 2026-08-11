#if !defined(PETAL_HEADER_HPP)
#define PETAL_HEADER_HPP

#include <fstream>
#include <functional>
#include <iostream>
#include <istream>
#include <map>
#include <memory>
#include <ostream>
#include <queue>
#include <stack>
#include <string>
#include <string_view>
#include <typeinfo>
#include <unordered_map>
#include <vector>

// C libraries
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace sf
{
// we use std:: for now
#define __sf_usingnamespacestd

#if !defined(__sf_usingnamespacestd)
#define __sf_usingnamespacestd

using namespace std;
#endif // __sf_usingnamespacestd

#if !defined(__sf_typedefs)
#define __sf_typedefs

using sf_char_t = char;
using sf_int_t = int;
using sf_float_t = float;
using sf_string_t = std::string;
using sf_strview_t = std::string_view;
using sf_bool_t = bool;

template <typename T, typename U = std::allocator<T>>
using sf_vec_t = std::vector<T, U>;
template <typename K, typename V, typename U = std::less<K>>
using sf_map_t = std::map<K, V, U>;
#endif // __sf_typedefs

} // namespace sf

#endif // PETAL_HEADER_HPP
