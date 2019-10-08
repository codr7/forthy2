#ifndef FORTHY2_READ_HPP
#define FORTHY2_READ_HPP

#include <iostream>

#include "forthy2/int.hpp"

namespace forthy2 {
  struct Cx;
  struct IdForm;
  struct LitForm;
  struct Pos;
  struct Val;

  Form *read_form(Cx &cx, Pos &pos, istream &in);
  pair<uint64_t, uint8_t> read_frac(Cx &cx, Pos &pos, istream &in);
  IdForm &read_id(Cx &cx, Pos &pos, istream &in);
  pair<Int, bool> read_int(Cx &cx, Pos &pos, istream &in, bool is_hex);
  LitForm &read_num(Cx &cx, Pos &pos, istream &in);
  void skip_ws(Pos &pos, istream &in);
}

#endif
