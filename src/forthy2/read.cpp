#include "forthy2/cx.hpp"
#include "forthy2/fix.hpp"
#include "forthy2/pos.hpp"
#include "forthy2/read.hpp"

namespace forthy2 {  
  Form *read_form(Cx &cx, Pos &pos, istream &in, bool skip) {
    if (skip) { skip_ws(pos, in); }
    Pos p(pos);
    Form *f;
    
    if (char c(0); in.get(c)) {
      switch (c) {
      case '_':
        pos.col++;
        return &cx.nil_form.ref();
      case '{':
        pos.col++;
        f = &read_scope(cx, pos, in);
        break;
      case '(':
        pos.col++;
        f = &read_stack(cx, pos, in);
        break;
      case '\'':
        pos.col++;
        f = &read_quote(cx, pos, in);
        break;
      case '%':
        pos.col++;
        f = &cx.splice_form.get(p);
        break;
      case '.':
        if (in.get(c)) {
          in.unget();

          if (c == '.' || c == ':') {
            in.unget();
            f = &read_id(cx, pos, in);
            break;
          }
        }

        pos.col++;
        f = &read_dot(cx, pos, nullptr, in);
        break;
      case ';':
        in.unget();
        return nullptr;
      case ',':
        pos.col++;
        f = &read_pair(cx, pos, in);
        break;
      case '&':
        pos.col++;        
        if (!(f = read_form(cx, pos, in, false))) { throw ESys(p, "Invalid ref"); }
        if (!dynamic_cast<RefForm *>(f)) { f = &cx.ref_form.get(p, *f); }
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
        if (c == '.') {
          if (in.get(c)) {
            in.unget();

            if (c == ':') {
              in.unget();
            } else {
              pos.col++;
              f = &read_dot(cx, pos, f, in);
            }
          }
        } else {
          in.unget();
        }
      }
      
      return f;
    }
    
    return nullptr;
  }

  DotForm &read_dot(Cx &cx, Pos &pos, Form *x, istream &in) {
    Pos p(pos);
    Form *z = read_form(cx, pos, in, true);
    if (!z) { throw ESys(p, "Missing z-form"); }
    Form *y = read_form(cx, pos, in, true);
    DotForm &d(cx.dot_form.get(p, x, y, *z));
    return d;
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
    char c(0), pc(0);
    
    for (;;) {  
      if (!in.get(c) || (!arg_depth && (!isgraph(c) ||
                                        c == '|' ||
                                        c == ']' ||
                                        c == ';' ||
                                        ((c == '.' || c == ':') &&
                                         pc && pc != '.' && pc != ':') ||
                                        (c != '.' && c != ':' &&
                                         pc && (pc == '.' || pc == ':')) ||
                                        (c == ',' && pc && pc != ',') ||
                                        c == '(' || c == ')' ||
                                        c == '{' || c == '}'))) {
        in.unget();
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
      pc = c;
    }

    
    
    return cx.id_form.get(p, cx.sym(out.str()));
  }
  
  Int::Imp read_int(Cx &cx, Pos &pos, istream &in, bool is_hex) {
    Pos p(pos);
    Int::Imp v(0);
    in >> (is_hex ? hex : dec) >> v;
    if (in.fail()) { throw ESys(p, "Failed reading int"); }
    return v;
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
        if (in.get(c)) {
          in.unget();

          if (isdigit(c)) {
            pos.col++;
            auto f(read_frac(cx, pos, in));
            int64_t v(i * Fix::pow(f.second) + f.first);
            Fix &fv(cx.fix_type.get(cx, v, f.second));
            return cx.lit_form.get(p, fv);
          }
        }
      }
      
      in.unget();
    }

    return cx.lit_form.get(p, cx.int_type.get(cx, i));
  }

  PairForm &read_pair(Cx &cx, Pos &pos, istream &in) {
    Pos p(pos);
    Form *l = read_form(cx, pos, in, false);
    if (!l) { throw ESys(p, "Missing left form"); }
    Form *r = read_form(cx, pos, in, true);
    if (!r) { throw ESys(p, "Missing right form"); }
    PairForm &d(cx.pair_form.get(p, *l, *r));
    return d;
  }

  Form &read_quote(Cx &cx, Pos &pos, istream &in) {
    Pos p(pos);
    Form *f(read_form(cx, pos, in, false));
    if (!f) { throw ESys(p, "Invalid quote"); }
    return cx.quote_form.get(p, *f);
  }

  ScopeForm &read_scope(Cx &cx, Pos &pos, istream &in) {
    ScopeForm &root(cx.scope_form.get(pos)), *out(&root);
    char c(0);
    
    for (;;) {
      skip_ws(pos, in);
      if (!in.get(c)) { throw ESys(out->pos, "Open scope"); }

      if (c == '}') {
        pos.col++;
        break;
      }

      if (c == ';') {
        pos.col++;
        ScopeForm &prev(*out);
        out = &cx.scope_form.get(pos);
        prev.body.push_back(out);
      } else {
        in.unget();
        Form *f(read_form(cx, pos, in, true));
        if (!f) { throw ESys(out->pos, "Open scope"); }
        out->body.push_back(f);
      }
    }

    return root;
  }

  StackForm &read_stack(Cx &cx, Pos &pos, istream &in) {
    StackForm &root(cx.stack_form.get(pos)), *out(&root);
    char c(0);
    
    for (;;) {
      skip_ws(pos, in);
      if (!in.get(c)) { throw ESys(out->pos, "Open stack"); }

      if (c == ')') {
        pos.col++;
        break;
      }

      if (c == ';') {
        pos.col++;
        StackForm &prev(*out);
        out = &cx.stack_form.get(pos);
        prev.body.push_back(out);
      } else {
        in.unget();
        Form *f(read_form(cx, pos, in, true));
        if (!f) { throw ESys(out->pos, "Open stack"); }
        out->body.push_back(f);
      }
    }

    return root;
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
