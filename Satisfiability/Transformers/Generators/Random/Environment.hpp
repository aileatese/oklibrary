// Oliver Kullmann, 5.3.2019 (Swansea)
/* Copyright 2019 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/* Strings describing the environment

   Delivers constant string-objects
    - compilation_date
    - compiler_version
    - git_id
    - optimisation

   plus the function
     output_environment(out, program, version, date)
   which obtains the other three strings to describe the program as arguments.


Assumes macros
 - GITID (the git-ID as string)
 - OPTIMISATION (the list of compilation-options as string)
are defined.

In order to define them on the command-line, assuming that "$(CXXFLAGS)" is
used late in the command for compilation, use e.g

> CXXFLAGS="-DGITID=\"\\\"ABC\\\"\"" make

to define GITIT as the string "ABC" (the will yield a redefinition-warning,
if the makefile already gives its own definition, got GITID, and this
warning seems appropriate).

If your makefile doesn't define GITIT in the first place, then just use

> -DGITID="ABC" make

For our makefile, one can use

> make git_id="ABC"


*/

#ifndef ENVIRONMENT_6Kk9MX4Wbw
#define ENVIRONMENT_6Kk9MX4Wbw

#include <string>
#include <ostream>

namespace Environment {

// Turning the value of a macro into a string:
#define S(x) #x
#define STR(x) S(x)

  const std::string compilation_date = __DATE__ " " __TIME__;
  const std::string compiler_version =
#ifdef __GNUC__
   "g++ " __VERSION__
#elif _MSC_VER
   STR(_MSC_VER)
#else
   ""
#endif
;
  const std::string optimisation =
#ifdef OPTIMISATION
   OPTIMISATION
#else
   ""
#endif
;

  const std::string git_id =
#ifdef GITID
   GITID
#else
   ""
#endif
;

  struct ProgramInfo {
    const std::string& comp_date = compilation_date;
    const std::string& comp_version = compiler_version;
    const std::string& comp_opt = optimisation;
    const std::string& git = git_id;
    const std::string prg;
    const std::string vrs;
    const std::string date;
    ProgramInfo(const std::string& prg, const std::string& vrs, const std::string& date) noexcept : prg(prg), vrs(vrs), date(date) {}
  };
  std::ostream& operator <<(std::ostream& out, const ProgramInfo& pi) {
    out << pi.prg << " " << pi.vrs << " " << pi.date << " " << pi.git << "\n";
    out << pi.comp_version << " " << pi.comp_date << "\n";
    return out << pi.comp_opt << "\n";
  }

}

#endif
