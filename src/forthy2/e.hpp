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
    bool cached;

    template <typename...Args>
    E(Pos pos, Args &&...args):
      pos(pos), msg(str(forward<Args>(args)...)), cached(false) {}
    
    const char* what() const throw() override {
      if (!cached) {
        stringstream buf;
        print(buf);
        auto *t(const_cast<E *>(this));
        t->msg = buf.str();
        t->cached = true;
      }

      return msg.c_str();
    }

    void print(ostream &out) const {
      out << "Error";
      if (pos.file) { out << " in " << pos.file; }
      out << " at row " << pos.row << ", col " << pos.col << ":\n" << msg;
    }
  };
  
  struct ESys: E {
    template <typename...Args>
    ESys(Pos pos, Args &&...args): E(pos, forward<Args>(args)...) {}
  };
}

#endif
