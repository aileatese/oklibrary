// Oliver Kullmann, 9.6.2019 (Swansea)
/* Copyright 2019 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

#include <iostream>

#include <cassert>

#include <ProgramOptions/Environment.hpp>

#include "QClauseSets.hpp"

namespace {

  const Environment::ProgramInfo proginfo{
        "0.0.8",
        "6.11.2019",
        __FILE__,
        "Oliver Kullmann",
        "https://github.com/OKullmann/oklibrary/blob/master/Satisfiability/Transformers/Generators/Random/TestQClauseSets.cpp",
        "GPL v3"};

  using namespace RandGen;

}

int main(const int argc, const char* const argv[]) {
  if (Environment::version_output(std::cout, proginfo, argc, argv))
  return 0;

  {assert(not valid(block_v{}));
   assert((not valid(block_v{{1,Q::fa}})));
   assert((not valid(block_v{{1,Q::ex}})));
   assert((valid(block_v{{1,Q::ex},{1,Q::ex}})));
   assert((not valid(block_v{{1,Q::fa},{1,Q::fa}})));
   assert((valid(block_v{{1,Q::fa},{1,Q::fa}}, false)));
   assert((not valid(block_v{{{2,3},Q::ex},{{2,3},Q::ex}})));
   assert((valid(block_v{{{1,3},Q::ex},{{1,3},Q::ex}})));
   assert((not valid(block_v{{{1,3},Q::fa},{{1,3},Q::fa}})));
   assert((valid(block_v{{{1,3},Q::fa},{{1,3},Q::fa}}, false)));
   assert((valid(block_v{{14,Q::both},{5,Q::fa},{{6,10},Q::fa},{{11,14},Q::ex}})));
   assert((not valid(block_v{{15,Q::both},{5,Q::fa},{{6,10},Q::fa},{{11,14},Q::ex},{{15,15},Q::fa}})));
   assert((valid(block_v{{15,Q::both},{5,Q::fa},{{6,10},Q::fa},{{11,14},Q::ex},{{15,15},Q::fa}}, false)));
   assert((not valid(block_v{{14,Q::ex},{5,Q::fa},{{6,10},Q::fa},{{11,14},Q::ex}})));
   assert((not valid(block_v{{14,Q::fa},{5,Q::fa},{{6,10},Q::fa},{{11,14},Q::fa}})));
   assert((valid(block_v{{14,Q::fa},{5,Q::fa},{{6,10},Q::fa},{{11,14},Q::fa}}, false)));
   assert((valid(block_v{{16,Q::ex},{6,Q::ex},{{7,10},Q::ex},{{11,16},Q::ex}})));
   assert((not valid(block_v{{14,Q::both},{5,Q::fa},{{6,10},Q::fa},{{10,14},Q::ex}})));
   assert((not valid(block_v{{14,Q::both},{5,Q::fa},{{5,10},Q::fa},{{11,14},Q::ex}})));
   assert((valid(block_v{{2,Q::ex},{1,Q::ex},{{2,2},Q::ex}})));
   assert((not valid(block_v{{2,Q::ex},{1,Q::both},{{2,2},Q::ex}})));
  }

  {assert((read_block_v("") == block_v{{1,Q::ex},{1,Q::ex}}));
   assert((read_block_v("  \n\n  \t ") == block_v{{1,Q::ex},{1,Q::ex}}));
   assert((read_block_v("123") == block_v{{123,Q::ex},{123,Q::ex}}));
   assert((read_block_v("-1") == block_v{{gen_uint_t(-1),Q::ex},{gen_uint_t(-1),Q::ex}}));

   assert((read_block_v("a10 123") == block_v{{133,Q::both},{10,Q::fa}, {{11,133},Q::ex}}));

   assert((read_block_v("a10 a10 123") == block_v{{143,Q::both},{10,Q::fa}, {{11,20},Q::fa}, {{21,143},Q::ex}}));
   assert((read_block_v(" a10 \n a10 e1 \n 123\n") == block_v{{144,Q::both},{10,Q::fa}, {{11,20},Q::fa}, {{21,21},Q::ex}, {{22,144},Q::ex}}));

   bool thrown = false;
   try { read_block_v("a18446744073709551615 1"); }
   catch (const std::domain_error& e) {
     assert(e.what() == std::string_view("VarInterval(gen_uint_t,gen_uint_t): a = 0"));
     thrown = true;
   }
   assert(thrown);
   thrown = false;
   try { read_block_v("a18446744073709551614 2"); }
   catch (const std::domain_error& e) {
     assert(e.what() == std::string_view("VarInterval(gen_uint_t,gen_uint_t): a > b"));
     thrown = true;
   }
   assert(thrown);
  }

  {assert(not valid(Qvector{}, true));
   assert(not valid(Qvector{}, false));
   for (gen_uint_t i = 0; i <= 3; ++i) {
     const Q q = Q(i);
     for (int j = 0; j <= 1; ++j) {
       const bool b(j);
       assert(not valid(Qvector{q}, b));
     }
   }
   assert((not valid(Qvector{Q::fa,Q::fa}, true)));
   assert((valid(Qvector{Q::fa,Q::fa}, false)));
   assert((valid(Qvector{Q::both,Q::fa,Q::ex}, false)));
   assert((valid(Qvector{Q::both,Q::fa,Q::ex}, true)));
   assert((not valid(Qvector{Q::both,Q::fa,Q::ex,Q::fa}, true)));
   assert((valid(Qvector{Q::both,Q::fa,Q::ex,Q::fa}, false)));
   assert((not valid(Qvector{Q::both,Q::fa,Q::ex,Q(3)}, false)));
   assert((not valid(Qvector{Q::fa,Q::fa,Q::ex,Q::fa}, false)));
   assert((not valid(Qvector{Q::ex,Q::fa,Q::ex,Q::fa}, false)));
  }
}
