// Oliver Kullmann, 1.7.2020 (Swansea)
/* Copyright 2020 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/* Data structures representing extended rows for the 2-sweep algorithm

*/

#ifndef EXTROWS_Q9FdphioR5
#define EXTROWS_Q9FdphioR5

#include <bitset>
#include <ostream>

#include <cstdint>

#include "Dimensions.hpp"

namespace ExtRows {

  namespace D = Dimensions;

  enum class ERtypes {bitset=0, uint=1 };
  std::ostream& operator <<(std::ostream& out, const ERtypes rt) {
    switch (rt) {
    case ERtypes::bitset : return out << "bitset";
    case ERtypes::uint   : return out << "uint";
    default : return out << "ERtypes::undefined";
    }
  }


  template <class R>
  class ExtRow {
    typedef std::bitset<3*D::N-2> extrow_t;
    static_assert(D::N <= 32); // so that to_ullong suffices
    extrow_t b;
  public :
    ExtRow(const R& r) noexcept : b(r.to_ullong() << (D::N-1)) {}
    operator R() const noexcept {
      return ((b << (D::N-1)) >> 2*(D::N-1)).to_ullong();
    }
    void add(const R& r) noexcept { b |= ExtRow(r).b; }
    void left() noexcept { b <<= 1; }
    void right() noexcept { b >>= 1; }
  };


  template <class R>
  class ExtRow_uint {
    typedef std::uint64_t extrow_t;
    static_assert(D::N <= 22); // so that 3N-2 <= 64
    extrow_t b;
  public :
    ExtRow_uint(const R& r) noexcept : b(r.to_ullong() << (D::N-1)) {}
    operator R() const noexcept {
      return (unsigned long long)((b << (D::N-1)) >> 2*(D::N-1));
    }
    void add(const R& r) noexcept { b |= ExtRow_uint(r).b; }
    void left() noexcept { b <<= 1; }
    void right() noexcept { b >>= 1; }
  };


  template <ERtypes> struct ChoiceERT_;
  template <> struct ChoiceERT_<ERtypes::bitset> {
    template <class X> using type = ExtRow<X>;
  };
  template <> struct ChoiceERT_<ERtypes::uint> {
    template <class X> using type = ExtRow_uint<X>;
  };
  template <ERtypes ert, class X>
  using ChoiceERT = typename ChoiceERT_<ert>::type<X>;

}

#endif
