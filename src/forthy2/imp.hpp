#ifndef FORTHY2_IMP_HPP
#define FORTHY2_IMP_HPP

#include <functional>

namespace forthy2 {
  using namespace std;
  
  struct Call;
  struct Cx;
  
  using Imp = function<bool (Cx &cx)>;
}

#endif
