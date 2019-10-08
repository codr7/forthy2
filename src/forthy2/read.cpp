#include "forthy2/cx.hpp"
#include "forthy2/fix.hpp"
#include "forthy2/pos.hpp"
#include "forthy2/read.hpp"

namespace forthy2 {
  Form *read_form(Cx &cx, Pos &pos, istream &in) {
    skip_ws(pos, in);
    Pos p(pos);
    Form *f;
    bool cte(false);
    
    if (char c(0); in.get(c)) {
      switch (c) {
      case '|':
        f = read_form(cx, pos, in);
        if (!f) { throw ESys(p, "Missing form"); }
        cte = true;
        break;
      default:
        in.unget();
        
        if (isdigit(c)) {
          f = &read_num(cx, pos, in);
        } else if (isgraph(c)) {
          f = &read_id(cx, pos, in);
        } else {
          throw ESys(pos, "Invalid input: ", c);
        }
      };

      if (in.get(c)) {
        if (c == ',') {
          Form *right(read_form(cx, pos, in));
          if (!right) { throw ESys(p, "Invalid pair"); }
          f = cx.pair_form.get(p, *f, *right);
        } else {
          in.unget();
        }
      }

      f->cte = cte;
      return f;
    }
    
    return nullptr;
  }

  pair<uint64_t, uint8_t> read_frac(Cx &cx, Pos &pos, istream &in) {
    char c(0);    
    uint64_t v(0);
    uint8_t s(0);
    
    while (in.get(c) && isdigit(c)) {
      v = v * 10 + c - '0';
      s++;
      pos.col++;
    }
    
    if (!in.eof()) { in.unget();}
    return make_pair(v, s);
  }

  IdForm &read_id(Cx &cx, Pos &pos, istream &in) {
    Pos p(pos);
    stringstream out;
    int arg_depth(0);
    char c(0);
    
    for (;;) {  
      if (!in.get(c) || (!arg_depth && (!isgraph(c) ||
                                        c == '|' ||
                                        c == '(' || c == ')' ||
                                        c == '{' || c == '}'))) {
        break;
      }
      
      out << c;

      switch (c) {
      case '[':
        arg_depth++;
        break;
      case ']':
        arg_depth--;
        break;
      default:
        break;
      }

      pos.col++;
    }

    if (!in.eof()) { in.unget(); }
    return *cx.id_form.get(p, cx.sym(out.str()));
  }
  
  pair<Int, bool> read_int(Cx &cx, Pos &pos, istream &in, bool is_hex) {
    Pos p(pos);
    bool is_neg(false);

    if (char c(0); in.get(c)) {
      is_neg = c == '-';
      in.unget();
    }
    
    Int v(0);
    in >> (is_hex ? hex : dec) >> v;
    if (in.fail()) { throw ESys(p, "Failed reading int"); }
    return make_pair(v, is_neg);
  }
  
  LitForm &read_num(Cx &cx, Pos &pos, istream &in) {
    Pos p(pos);
    bool is_hex(false);
    char c(0);
      
    if (in.get(c)) {
      if (c == '0') {
        if (in.get(c)) {
          if (c == 'x') {
            is_hex = true;
          } else {
            in.unget();
            in.unget();
          }                 
        }
      } else {
        in.unget();
      }
    }
    
    auto i(read_int(cx, pos, in, is_hex));
    
    if (!is_hex && in.get(c)) {
      if (c == '.') {
        auto f(read_frac(cx, pos, in));
        int64_t v(i.first * fix::pow(f.second) + f.first);

        FixVal &fv(cx.fix_type.get(cx, fix::make((i.first || !i.second) ? v : -v,
                                                 f.second)));
        
        return *cx.lit_form.get(p, fv);
      }
      
      in.unget();
    }

    return *cx.lit_form.get(p, cx.int_type.get(cx, i.first));
  }
  
  void skip_ws(Pos &pos, istream &in) {
    char c(0);
    
    while (in.get(c) && isspace(c)) {
      switch (c) {
      case ' ':
      case '\t':
        pos.col++;
        break;
      case '\n':
        pos.row++;
        pos.col = 0;
      };
    }

    if (!in.eof()) { in.unget(); }
  }
}
