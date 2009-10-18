// Oliver Kullmann, 11.10.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/GreenTaoProblems/plans/GreenTao_4-3-3-3-4.hpp
  \brief Investigations on greentao_4(3,3,3,4)

  Generated by output_greentao_stdname([3,3,3,4],n) or
  output_greentao_sb_stdname([3,3,3,4],n).


  \todo Best local search algorithm
  <ul>
   <li>
   Evaluating
   \verbatim
E = eval_ubcsat("GreenTao_4-3-3-3-4_800.cnf", params=list(runs=100,cutoff=10000),monitor=TRUE)
   \endverbatim
   by plot(E$alg,E$best), the best algorithms seems sapsnr. </li>
   <li> However, considering n=1000, now gsat-tabu, adaptnovelty+, rots and
   samd seem best (for cutoff=10000), while sapsnr became rather weak! </li>
   <li> Testing these four algorithms with cutoff=10^6:
   \verbatim
E = eval_ubcsat("GreenTao_4-3-3-3-4_1000.cnf", params=list(runs=100,cutoff=1000000),monitor=TRUE, algs=list(gsat_tabu="gsat-tabu", adaptnoveltyp="adaptnovelty+", rots="rots", samd="samd"))
   \endverbatim
   (currently algorithms-names are inappropriately handled by eval_ubcsat):
   adaptnovelty+ is clearly best: the best min(=6), and a very small spread;
   the second is samd, but with worst min, and a far larger spread. </li>
  </ul>


  \todo Lower bounds: greentao_4(3,3,3,4) > 994
  <ul>
   <li> n=800 easily found satisfiable by sapsnr (cutoff=10*10^3,
   runs=100). </li>
   <li> n=850
    <ol>
     <li> cutoff=10^4: adaptnovelty+ reaches in 100 runs min=17
     (while sapsnr reaches min=12, and samd reaches min=15). </li>
     <li> cutoff=10^5: adaptnovelty+ reaches in 100 runs min=1, while sapsnr
     finds a solution in run 31 (seed=1051937617). </li>
    </ol>
   </li>
   <li> n=900
    <ol>
     <li> cutoff=10^4: adaptnovelty+ reaches in 100 runs min=22
     (while sapsnr reaches min=29, and samd reaches min=22). </li>
     <li> cutoff=10^5: adaptnovelty+ reaches in 100 runs min=3
     (while sapsnr reaches min=21, and samd reaches min=5). </li>
     <li> cutoff=10^6: adaptnovelty+ finds a solution in run 2
     (seed=446607350). </li>
    </ol>
   </li>
   <li> n=950
    <ol>
     <li> cutoff=10^6, using adaptnovelty+: reaches min=1 (median=4,
     mean=4.3). </li>
     <li> cutoff=10^7 (adaptnovelty+): found a solution in run 3
     (seed=3537296603). </li>
    </ol>
   </li>
   <li> n=975
    <ol>
     <li> cutoff=10^7 (adaptnovelty+): A solution was found in run 60
     (seed=839702132, osteps=9609423). </li>
    </ol>
   </li>
   <li> n=988
    <ol>
     <li> cutoff=10^7 (adaptnovelty+): A solution was found in run 19
     (seed=825817361, osteps=8785207). </li>
    </ol>
   </li>
   <li> n=989
    <ol>
     <li> cutoff=10^7 (adaptnovelty+):
     \verbatim
 1  2  3  4  5  6  7
 2 14 22 30 21  9  2
100
     \endverbatim
     </li>
     <li> cutoff=2*10^7 (adaptnovelty+):
     \verbatim
 1  2  3  4  5  6
 4 32 45 14  4  1
100
     \endverbatim
     </li>
     <li> cutoff=8*10^7 (adaptnovelty+) finds a solution in run 9
     (seed=3728380835, osteps=58003122). </li>
    </ol>
   </li>
   <li> n=990: cutoff=8*10^7 finds a solution in run 76 (seed=2964724610,
   osteps=19062436). </li>
   <li> n=991
    <ol>
     <li> cutoff=10^7 (adaptnovelty+):
     \verbatim
 1  2  3  4  5  6  7
 1  8 21 28 30  8  4
100
     \endverbatim
     </li>
     <li> cutoff=8*10^7 (adaptnovelty+):
     \verbatim
 1  2  3  4
18 68 13  1
100
     \endverbatim
     </li>
     <li> cutoff=16*10^7 (adaptnovelty+): finds a solution in run 5 (seed=
     2464081211, osteps=118475284). </li>
    </ol>
   </li>
   <li> n=994
    <ol>
     <li> cutoff=10^7 (adaptnovelty+):
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -cutoff 10000000 -runs 100 -solve -i GreenTao_4-3-3-3-4_994.cnf | tee GreenTao_4-3-3-3-4_994.cnf_OUT
 1  2  3  4  5  6  7  8
 1  2 13 20 37 18  7  2
     \endverbatim
     </li>
     <li> Checking all algorithms with cutoff=10^6:
     \verbatim
> E = eval_ubcsat("GreenTao_4-3-3-3-4_994.cnf", params=list(runs=100,cutoff=1000000),monitor=TRUE)
     \endverbatim
     The best algorithms seem to be gwsat, gsat_tabu, adaptnoveltyp and samd,
     with adaptnoveltyp clearly best (reaching also the best min=6). </li>
     <li> cutoff=16*10^7 (adaptnovelty+): finds a solution in run 7 (seed=
     2045601853, osteps=122505356). </li>
    </ol>
   </li>
   <li> n=995 </li>
   <li> n=1000
    <ol>
     <li> cutoff=10*10^3 with 100 runs reaches only min=68 (sapsnr), while
     using cutoff=100*10^3 we get min=65, so let's assume for now that it's
     unsatisfiable. </li>
     <li> However, using adaptnovelty+ with cutoff=100*10^3 we reach min=17,
     so here adaptnovelty+ is much better! </li>
     <li> cutoff=10^6: adaptnovelty+ reaches in 100 runs min=4
     (while sapsnr reaches min=50, and samd reaches min=8). </li>
     <li> cutoff=10^7 (adaptnovelty+): reaches in 100 runs min=1 (where
     median=5 and mean=5.01). </li>
     <li> cutoff=10^8 (adaptnovelty+):
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -cutoff 100000000 -runs 100 -solve -i GreenTao_4-3-3-3-4_1000.cnf | tee GreenTao_4-3-3-3-4_1000.cnf_OUT
 1  2  3  4
 6 51 40  3
     \endverbatim
     </li>
     <li> cutoff=16*10^7 (adaptnovelty+):
     \verbatim
 1  2  3
14 74 12
100
> summary(E$osteps)
     Min.   1st Qu.    Median      Mean   3rd Qu.      Max.
  4633000  36250000  57420000  66770000  93560000 156800000
     \endverbatim
     So let's assume this is unsatisfiable. </li>
    </ol>
   </li>
  </ul>

*/

