// Oliver Kullmann, 9.9.2019 (Swansea)
/* Copyright 2019, 2020 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/* Creating experiments, currently for ExpQueensRC only:

   Creates an experiment-directory, with the executable copied there,
   and with a Makefile, which is executed with, e.g.,

   > make -j12

   which runs the experiment with 12 jobs in parallel (if available).
   The results are then to be found in results.R, with logfile giving
   further details.

   The results of the jobs are saved in files tX_Y_Z, indicating the
   parameter values. These files can be removed by "make clean" (while
   "make cleanall" also removes results.R).

   The main target is "all", which calls first "run" and then "transfer" (of
   the single experiment-files into the overall results.R).
   If the experiment is interrupted, then it can be restarted by just using
   "make" (with the appropriate j-parameter) again.

*/

/* TODOS

1. Further arguments, to specify intervals for the other three parameters
   (heuristic, caching, symmetry-breaking) are needed.

2. Use of joblist or revjoblist (running through jobs by increasing or
   decreasing N):

   - With the current default-N (from 4 to 17), on cs-kullmann-server, with
     j=24 (max-memory usage apparently around 300 GB), the ascending order
     takes 1h50min, the descending order takes 2h00min (roughly).
   - It seems the run-times of jobs are up to random changes the same.
   - The main difference seems to be in core-utilisation, where an higher
     average CPU-usage is reported for ascending order.
   - This seems to contradict common wisdom, in the form of the
     LPT sequencing https://www.encyclopediaofmath.org/index.php/LPT_sequencing
     "largest-processing-time-first sequencing",
     which according to the above page is optimal:
       "LPT is asymptotically absolutely as well as relatively optimal in
       expectation, even if the machines have different speeds."
       "With such a good performance, the LPT heuristic has been successfully
       applied to various scheduling environments in delivering a near
       minimum-makespan schedule."
   - So currently the order of make-targets uses "joblist", not "revjoblist".
   - Just due to the fact, that the longest task, for N=17, heur=1, cache=1,
     comes relatively late in the order? It is number 27, and it
     only scheduled after 16:40 min, and its runtime is around 103 min.
   - So do we consider this just as random coincidence?
   - Or should the order of heuristcs in ExpQueensRC be changed, having
     first the better heuristics, the min-forms, and then the max-forms?

3. Compare with other scripts/programs producing makefiles (N-Queens,
   Latin squares), to create a common base.
   - Compare also with script Run (in this directory), which likely is
     now obsolete.

4. Update to new standard (use of Environment.hpp).

5. Make also ExpQueens available here.

*/

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#include <ProgramOptions/Environment.hpp>

#include "CreateExperiment.hpp"
#include "Caching.hpp"
#include "Heuristics.hpp"

namespace {

  const Environment::ProgramInfo proginfo{
        "0.2.4",
        "11.5.2020",
        __FILE__,
        "Oliver Kullmann",
        "https://github.com/OKullmann/oklibrary/blob/master/Satisfiability/Transformers/Generators/Queens/GenericSAT/CreateExperiment.cpp",
        "GPL v3"};

  using namespace CreateExperiment;

  const std::string executable_default = "./ExpQueensRC";
  constexpr par_t N_upper_default = 17;
  constexpr par_t N_lower_default = 4;
  constexpr par_t H_upper_default = Heuristics::maxHeurOptions;
  constexpr par_t H_lower_default = 0;
  constexpr par_t C_upper_default = Caching::maxCachOptions;
  constexpr par_t C_lower_default = 0;
  constexpr par_t S_lower_default = 0;
  constexpr par_t S_upper_default = 1;

  const std::string experiment_stem = "Experiment_";
  const std::string logfile_name = "logfile";
  const std::string makefile_name = "Makefile";
  const std::string resultfile_name = "results.R";

  bool show_usage(const int argc, const char* const argv[]) {
    assert(argc >= 1);
    if (argc != 2 or not Environment::is_help_string(argv[1])) return false;
    const std::string& program = proginfo.prg;
    std::cout << "USAGE:\n"
    "> " << program << " [-v | --version]\n"
    " shows version information and exits.\n"
    "> " << program << " [-h | --help]\n"
    " shows help information and exits.\n"
    "> " << program << " [Nup=" << N_upper_default << "] "
    "[Nlo=" << N_lower_default << "] "
    "[exec=" << executable_default << "]\n"
    "creates the experiment-director with N from Nlo to Nup.\n"
;
    return true;
  }

}

int main(const int argc, const char* const argv[]) {

  if (Environment::version_output(std::cout, proginfo, argc, argv)) return 0;
  if (show_usage(argc, argv)) return 0;

  Environment::Index index;
  const par_t N_upper = argc<=index ? N_upper_default : std::stoi(argv[index++]);
  const par_t N_lower = argc<=index ? N_lower_default : std::stoi(argv[index++]);
  const std::string executable = argc<=index ? executable_default : argv[index++];
  index.deactivate();
  const par_t H_upper = H_upper_default;
  const par_t H_lower = H_lower_default;
  const par_t C_upper = C_upper_default;
  const par_t C_lower = C_lower_default;
  const par_t S_lower = S_lower_default;
  const par_t S_upper = S_upper_default;
  const ParRange N{N_lower, N_upper};
  const ParRange H{H_lower, H_upper};
  const ParRange C{C_lower, C_upper};
  const ParRange S{S_lower, S_upper};

  using namespace std::filesystem;
  const path executable_path(executable);
  if (not is_regular_file(executable_path)) return 1;
  const std::string executable_filename = executable_path.filename();

  using Environment::CurrentTime;
  const CurrentTime Now;
  using Environment::remove;
  const std::string directory_name =
    experiment_stem +
    std::to_string(N_lower) + "_" + std::to_string(N_upper) + "_" +
    std::to_string(CurrentTime::ticks_as_uints(Now.ticks)) +
    "_" + remove(Now.date, '.')  + "_" +
    remove(remove(Now.time, ':'), '_');

  std::cout << "Creating directory \"" << directory_name << "\".\n";
  const path directory_path("./" + directory_name);
  if (exists(directory_path)) return 2;
  if (not create_directory(directory_path)) return 3;

  copy(executable_path, directory_path);

  const path logfile_path(path(directory_path).append(logfile_name));
  if (exists(logfile_path)) return 4;
  std::fstream logfile(logfile_path, std::ios_base::out);
  if (not logfile) return 5;

  logfile << Environment::Wrap{proginfo, Environment::OP::simple}
    << "\nN=" << N << ", H=" << H << ", C=" << C << "\n\n";
  if (not logfile) return 6;
  logfile.close();

  if (std::system((directory_name + "/" + executable_filename + " -v >> " + std::string(logfile_path)).c_str()) != 0) return 7;

  const path makefile_path(path(directory_path).append(makefile_name));
  if (exists(makefile_path)) return 8;
  std::fstream makefile(makefile_path, std::ios_base::out);
  if (not makefile) return 9;

  write_makefile(makefile,
                 make_job_description({N, H, C, S}),
                 "./" + executable_filename,
                 resultfile_name);

  if (not makefile) return 10;

}
