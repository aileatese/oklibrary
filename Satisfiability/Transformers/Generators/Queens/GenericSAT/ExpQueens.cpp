// Oliver Kullmann, 14.8.2018 (Swansea)
/* Copyright 2018 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

#include <iostream>
#include <string>

#include <cstdlib>

#include "Backtracking.hpp"
#include "NQueens.hpp"
#include "InOut.hpp"

namespace {

const std::string version = "0.3.7";
const std::string date = "13.10.2018";
const std::string program = "ExpQueens"
#ifndef NDEBUG
  "_debug"
#endif
;
const std::string error = "ERROR[" + program + "]: ";

void show_usage() noexcept {
  const std::string prompt = "\n> " + program;
  std::cout << "USAGE in two information-only and three main forms:\n"
    "\n> " << program << "\n"
    " shows usage information and exists.\n"
    "\n> " << program << " (-v | --version)\n"
    " shows version informations and exits.\n"
    "\n The following main usage-forms all start with N, the order of the square.\n"
    " Round brackets \"()\" indicate a list of possible options (as characters), square brackets \"[]\" indicate optional arguments.\n"
    "\n> " << program << " N\n"
    " uses NQeens::TawHeuristics.\n"
    "\n> " << program << " N (f,r,s)\n"
    " uses first-open, random, or square for the branching heuristics.\n"
    "\n> " << program << " N r [seed]\n"
    " uses seed for the random form.\n";
  std::exit(0);
}

void version_information() noexcept {
  std::cout << program << ":\n"
   " Version: " << version << "\n"
   " Last change date: " << date << "\n"
#ifdef NDEBUG
   " Compiled with NDEBUG\n"
#else
   " Compiled without NDEBUG\n"
#endif
#ifdef __OPTIMIZE__
   " Compiled with optimisation options\n"
#else
   " Compiled without optimisation options\n"
#endif
   " Compilation date: " __DATE__ " " __TIME__ "\n"
#ifdef __GNUC__
   " Compiler: g++, version " __VERSION__ "\n"
#else
   " Compiler not gcc\n"
#endif
  ;
  std::exit(0);
}

}

int main(const int argc, const char* const argv[]) {
  if (argc == 1) show_usage();
  if (argc == 2 and std::string(argv[1]) == "-v") version_information();
  const ChessBoard::coord_t N = InOut::interprete(argc, argv, error);
  const std::string option = (argc == 2) ? "" : argv[2];
  NQueens::AmoAlo_board Fq(N);
  if (option == "") {
    Backtracking::CountSat<NQueens::AmoAlo_board, NQueens::TawHeuristics<>> B;
    const auto rFq = B(Fq);
    std::cout << rFq;
    return 0;
  }
  else if (option == "f") {
    Backtracking::CountSat<NQueens::AmoAlo_board, NQueens::FirstOpen> B;
    const auto rFq = B(Fq);
    std::cout << rFq;
    return 0;
  }
  else if (option == "r") {
    if (argc == 3) {
      Backtracking::CountSat<NQueens::AmoAlo_board, NQueens::FirstOpenRandom> B(N);
      const auto rFq = B(Fq);
      std::cout << rFq;
      return 0;
    } else {
      typedef NQueens::FirstOpenRandom::seed_t seed_t;
      const seed_t seed = std::stoul(argv[3]);
      typedef NQueens::FirstOpenRandom::vec_seed_t vec_seed_t;
      Backtracking::CountSat<NQueens::AmoAlo_board, NQueens::FirstOpenRandom> B(N,vec_seed_t{{seed}});
      const auto rFq = B(Fq);
      std::cout << rFq;
      return 0;
    }
  }
  else if (option == "s") {
    Backtracking::CountSat<NQueens::AmoAlo_board, NQueens::FirstOpenRandom> B(ChessBoard::enum_square(N));
    const auto rFq = B(Fq);
    std::cout << rFq;
    return 0;
  }
  else if (option == "p") {
    NQueens::PhasedAmoAlo_board Fq(N);
    Backtracking::CountSat<NQueens::PhasedAmoAlo_board, NQueens::TawHeuristics<NQueens::PhasedAmoAlo_board>> B;
    const auto rFq = B(Fq);
    std::cout << rFq;
    return 0;
  }
  else {
    std::cerr << error << "Uninterpreted argument \"" << option << "\".\n";
    std::exit(InOut::code(InOut::Error::uninterpreted_argument));
  }
}
