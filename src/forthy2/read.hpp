#ifndef FORTHY2_READ_HPP
#define FORTHY2_READ_HPP

#include <iostream>

#include "forthy2/int.hpp"

namespace forthy2 {
  struct Cx;
  struct Pos;
  struct Val;

  pair<uint64_t, uint8_t> read_frac(Cx &cx, Pos &pos, istream &in);
  Val &read_id(Cx &cx, Pos &pos, istream &in);
  pair<Int, bool> read_int(Cx &cx, Pos &pos, istream &in, bool is_hex);
  Val &read_num(Cx &cx, Pos &pos, istream &in);
  Val *read_val(Cx &cx, Pos &pos, istream &in);
  void skip_ws(Pos &pos, istream &in);
}

#endif
