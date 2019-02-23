// Oliver Kullmann, 23.2.2019 (Swansea)
/* Copyright 2019 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

#include "ClauseSets.hpp"

#include <cassert>

int main() {

  using namespace ClauseSets;
  using namespace VarLit;

  const AClause c1{{Lit(1),Lit(2),Lit(2)}};
  assert(c1.size() == 2);
  const EClause c2{3_l,-4_l};
  assert(c1 != c2);
  const PairClause pc{{1_l,2_l},{3_l,-4_l,Lit(3)}};
  assert(pc.first == c1);
  assert(pc.second == c2);
  assert(DClause().empty());
  assert(DClause().index == 0);
  const DClause C1{{{1_l,2_l},{3_l,-4_l}},2};
  assert(C1.P == pc);
  assert(C1.index == 2);

}