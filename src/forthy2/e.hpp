#ifndef FORTHY2_E_HPP
#define FORTHY2_E_HPP

#include <exception>
#include <sstream>

#include "forthy2/pos.hpp"
#include "forthy2/util.hpp"

namespace forthy2 {
  using namespace std;

  struct E: exception {
    Pos pos;
    string msg;
    bool is_cached;

    template <typename...Args>
    E(const Pos &pos, Args &&...args):
      pos(pos), msg(str(forward<Args>(args)...)), is_cached(false) {}
    
    virtual const char* what() const throw() override {
      if (!is_cached) {
        stringstream buf;
        print(buf);
        auto *t(const_cast<E *>(this));
        t->msg = buf.str();
        t->is_cached = true;
      }

      return msg.c_str();
    }

    virtual void print(ostream &out) const {
      out << "Error";
      if (pos.file) { out << " in " << pos.file; }
      out << " at row " << pos.row << ", col " << pos.col << ":\n" << msg;
    }
  };
  
  struct ESys: E {
    template <typename...Args>
    ESys(const Pos &pos, Args &&...args): E(pos, forward<Args>(args)...) {}
  };
}

#endif
