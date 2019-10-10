#ifndef FORTHY2_READ_HPP
#define FORTHY2_READ_HPP

#include <iostream>

#include "forthy2/int.hpp"

namespace forthy2 {
  struct Cx;
  struct DotForm;
  struct IdForm;
  struct LitForm;
  struct PairForm;
  struct Pos;
  struct Val;

  DotForm &read_dot(Cx &cx, Pos &pos, Form &x, istream &in);
  Form *read_form(Cx &cx, Pos &pos, istream &in);
  pair<uint64_t, uint8_t> read_frac(Cx &cx, Pos &pos, istream &in);
  IdForm &read_id(Cx &cx, Pos &pos, istream &in);
  pair<Int::Imp, bool> read_int(Cx &cx, Pos &pos, istream &in, bool is_hex);
  LitForm &read_num(Cx &cx, Pos &pos, istream &in);
  PairForm &read_pair(Cx &cx, Pos &pos, istream &in);
  void skip_ws(Pos &pos, istream &in);
}

#endif
