// Oliver Kullmann, 11.3.2011 (Swansea)
/* Copyright 2011 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/VanderWaerdenProblems/plans/5-k/08.hpp
  \brief On investigations into vdw_2(5,8)


  \todo Best local search solver
  <ul>
   <li> For k=7 adaptg2wsat and ddfw are best (see
   VanderWaerdenProblems/plans/5-k/07.hpp). </li>
   <li>
   \verbatim
E = run_ubcsat("VanDerWaerden_2-5-8_330.cnf", runs=100,cutoff=2000000)
1. ddfw:
 1  3  4  5  6
 1  4 28 54 13
fps: 68776
2. ag2wsat:
 2  3  4  5  6  7
 2  2 22 43 29  2
fps: 238277
3. rnovp:
 3  4  5  6  7
 6 15 48 30  1
fps: 203370
4. rnov:
 3  4  5  6  7
 2 18 59 20  1
fps: 203044
5. anovp:
 3  4  5  6  7
 1 16 34 45  4
fps: 200393
6. anovpp:
 3  4  5  6  7
 1 11 42 40  6
fps: 200172
7. dano:
 3  4  5  6  7
 1  8 40 45  6
fps: 200256
8. rots:
 5  6  7  8  9
 5 14 35 39  7
fps: 251737
9. gwsat:
 5  7  8  9 10 11 12
 2  7 13 22 32 18  6
fps: 248558
   \endverbatim
   So ddfw and adaptg2wsat seem best. </li>
  </ul>


  \todo vdw_2(5,8) > 330
  <ul>
   <li> The conjecture is vdw_2(5,8) = 331. </li>
   <li> Certificate for n=330:
   \verbatim
3,4,5,6,9,12,13,14,21,22,
27,32,35,37,39,41,46,48,50,51,
52,53,55,57,62,64,65,68,71,76,
81,85,89,90,91,96,97,99,100,102,
106,108,110,115,120,125,126,127,133,135,
136,138,139,140,143,144,145,146,150,152,
153,154,156,164,167,170,171,173,177,178,
179,180,182,183,184,185,187,188,190,194,
196,197,198,203,211,213,214,215,217,221,
222,223,224,226,227,229,232,233,234,241,
242,247,252,255,258,261,266,270,271,272,
274,275,277,282,283,285,288,291,295,296,
301,305,309,310,311,316,317,318,320,323,
324,325,328,330
   \endverbatim
   or
   \verbatim
2,6,8,10,11,12,13,15,18,22,
27,32,35,37,39,41,45,46,47,51,
52,57,58,62,64,66,71,79,81,82,
83,85,89,90,91,92,94,95,96,97,
99,100,106,108,109,110,112,115,123,126,
133,134,135,136,138,139,140,143,144,146,
152,153,154,159,164,169,170,171,173,177,
179,180,182,183,185,187,188,189,190,194,
197,200,208,211,213,214,215,217,222,224,
226,228,229,231,234,238,240,241,242,244,
252,257,259,261,265,266,267,271,272,273,
276,277,278,284,286,291,296,301,302,303,
305,311,313,314,316,317,320,321,324,325,
327,328,330
   \endverbatim
   </li>
   <li> Using the palindromic solution for n=322:
    <ol>
     <li> Starting search with the best palindromic solution:
     \verbatim
> k1=5 k2=8 n=322 alg="adaptg2wsat" cutoff=1000000 runs=100 expdate=""; export k1 k2 n; cat AltExp/Exp_PdVanderWaerden_2-${k1}-${k2}_${alg}-${runs}-${cutoff}_${expdate}/VanDerWaerden_pd_2-${k1}-${k2}_${n}.cnf_sol | PdExtend-O3-DNDEBUG ${n} > solution

> RunVdWk1k2 ${k1} ${k2} ${n} adaptg2wsat 100 10000000 solution
UNSAT for n=331
> E=read_ubcsat("Exp_VanderWaerden_2-5-8_322_adaptg2wsat-100-10000000_2011-04-13-080441/VanDerWaerden_2-5-8_331.cnf_OUT",nrows=100)
 3  4  5
 5 46 49
100

> RunVdWk1k2 ${k1} ${k2} ${n} ddfw 100 10000000 solution
UNSAT for n=331
> E=read_ubcsat("Exp_VanderWaerden_2-5-8_322_ddfw-100-10000000_2011-04-13-185202/VanDerWaerden_2-5-8_331.cnf_OUT",nrows=100)
 1  2  3  4  5
 3  1  8 53 35
100

> n=330; RunVdWk1k2 ${k1} ${k2} ${n} adaptg2wsat 100 20000000 AltExp/Exp_VanderWaerden_2-5-8_322_ddfw-100-10000000_2011-04-13-185202/VanDerWaerden_2-${k1}-${k2}_${n}.cnf_sol
UNSAT for n=331
> E=read_ubcsat("AltExp/Exp_VanderWaerden_2-5-8_330_adaptg2wsat-100-20000000_2011-04-13-232550/VanDerWaerden_2-5-8_331.cnf_OUT",nrows=100)
 1  2  3  4  5
 2  3 19 60 16
100
     \endverbatim
     </li>
     \endverbatim
     </li>
    </ol>
   </li>
   <li> n=331
   \verbatim
adaptg2wsat:
 cutoff=40000000
 1  2  3  4  5
 3  3 33 59  2
100
 cutoff=80000000
 1  2  3  4
 5  4 39 34
82

ddfw:
 cutoff=20000000
 1  2  3  4  5
 4  2 27 58  9
100
 cutoff=40000000
 1  2  3  4
 7  5 43 45
100
 cutoff=80000000
 1  2  3  4
13 18 46 23
100
 cutoff=160000000
 1  2  3  4
24 14 46  8
92
   \endverbatim
   </li>
  </ul>


  \todo Best complete solver for palindromic problems
  <ul>
   <li> It seems that from the conflict-driven solvers minisat-2.2.0 is best,
   from the look-ahead solvers march_pl (followed by OKsolver_2002, then
   satz215), and that overall minisat-2.2.0 is best. </li>
  </ul>


  \todo Best local-search solver for palindromic problems
  <ul>
   <li> Best ubcsat-algorithm:
   \verbatim
> PdVanderWaerdenCNF-O3-DNDEBUG 5 8 312

> E=run_ubcsat("VanDerWaerden_pd_2-5-8_312.cnf",runs=100,cutoff=1000000)

ag2wsat
 0  1  2
57 36  7
FlipsPerSecond = 208908
paws
 0  1  2  3
52 22 25  1
FlipsPerSecond = 204942
nov
 0  1  2  3
43 20 28  9
FlipsPerSecond = 169408
novp_p
 0  1  2  3  4
39 18 27 15  1
FlipsPerSecond = 129391
novpc
 0  1  2  3  4
36 11 29 23  1
FlipsPerSecond = 206143
anovp
 0  1  2
35 48 17
FlipsPerSecond = 172125
novp
 0  1  2  3
34 16 35 15
FlipsPerSecond = 169951
anovpp
 0  1  2
33 41 26
FlipsPerSecond = 170963
ddfw
 0  1  2
29 59 12
FlipsPerSecond = 89456
dano
 0  1  2
27 44 29
FlipsPerSecond = 169269
g2wsat
 0  1  2  3
27 23 44  6
FlipsPerSecond = 221298
   \endverbatim
   (segmentation faults with saps and sapsnr). So adaptg2wsat seems clearly
   strongest. </li>
  </ul>


  \todo vdw_2^pd(5,8) = (312,323)
  <ul>
   <li> Determined by minisat-2.2.0:
    <ol>
     <li> Hardest problem for n=324:
     \verbatim
restarts              : 16777214
conflicts             : 19006590162    (4124 /sec)
decisions             : 21516030010    (0.00 % random) (4668 /sec)
propagations          : 379970924722   (82439 /sec)
conflict literals     : 508510692844   (22.16 % deleted)
Memory used           : 225.14 MB
CPU time              : 4.60912e+06 s
UNSATISFIABLE
     \endverbatim
     (this is, 53.3 days)
     </li>
     <li> While for n=313:
     \verbatim
restarts              : 2097150
conflicts             : 2076757141     (6872 /sec)
decisions             : 2356337872     (0.00 % random) (7798 /sec)
propagations          : 41736971474    (138117 /sec)
conflict literals     : 50113566661    (23.17 % deleted)
Memory used           : 91.68 MB
CPU time              : 302186 s (5036m)
UNSATISFIABLE
     \endverbatim
     </li>
     <li> Splitting the problem for n=313:
     \verbatim
> SplittingViaOKsolver -D20 VanDerWaerden_pd_2-5-8_313.cnf
> cd SplitViaOKsolver_D20VanDerWaerden_pd_258_313cnf_2011-08-14-215226/
> more Md5sum
0bce68a7593709239363cf3623bccf7f
> more Statistics
> E=read.table("Data")
> summary(E$n)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   20.0    20.0    20.0    20.9    21.0    48.0
> table(E$n)
   20    21    22    23    24    25    26    27    28    29    30    31    32
11451  5955  2928  1195   536   213   103    43    20    10    13     3     2
   33    34    36    37    38    39    48
    3     1     1     1     1     2     1
> more Result
s UNKNOWN
c sat_status                            2
c initial_maximal_clause_length         8
c initial_number_of_variables           157
c initial_number_of_clauses             9121
c initial_number_of_literal_occurrences 54905
c running_time(sec)                     407.5
c number_of_nodes                       44965
c number_of_single_nodes                0
c number_of_quasi_single_nodes          0
c number_of_2-reductions                637
c number_of_pure_literals               0
c number_of_autarkies                   0
c number_of_missed_single_nodes         0
c max_tree_depth                        20
c file_name                             VanDerWaerden_pd_2-5-8_313.cnf
c splitting_directory                   SplitViaOKsolver_D20VanDerWaerden_pd_258_313cnf_2011-08-14-215226/Instances
c splitting_cases                       22482

> ProcessSplitViaOKsolver SplitViaOKsolver_D20VanDerWaerden_pd_258_313cnf_2011-08-14-215226
> cd Process_SplitViaOKsolver_D20VanDerWaerden_pd_258_313cnf_2011-08-14-215226_2011-08-14-220708

290m24s

> E=read_processsplit_minisat()
22482: 4.34h, sum-cfs=4.668112e+08, mean-t=0.695s, mean-cfs=20764
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
 0.0120  0.1720  0.3480  0.6953  0.7400 29.4000
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
     35    5183   10950   20760   23110  740900
     \endverbatim
     That is a speed-up by a factor of 17. </li>
     <li> Splitting the problem for n=324, first with depth 12 (from the above
     time, we get an "average" of 1125.273s per sub-instance; recall that the
     instance is created by "PdVanderWaerdenCNF-O3-DNDEBUG 5 8 324"):
     \verbatim
> SplittingViaOKsolver -D12 -SD VanDerWaerden_pd_2-5-8_324.cnf
> cd SplitViaOKsolver_D12SDVanDerWaerden_pd_258_324cnf_2011-05-15-101121
> more Md5sum
64d71cced212d7377c121092fa7476ce
> more Statistics
> E=read.table("Data")
> summary(E$n)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  12.00   14.00   15.00   15.07   16.00   32.00
> table(E$n)
 12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  32
230 651 933 834 620 371 223 130  47  23  14   7   6   2   1   3   1
> more Result
s UNKNOWN
c sat_status                            2
c initial_maximal_clause_length         8
c initial_number_of_variables           162
c initial_number_of_clauses             9973
c initial_number_of_literal_occurrences 60446
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   0
c running_time(sec)                     22.8
c number_of_nodes                       8191
c number_of_single_nodes                0
c number_of_quasi_single_nodes          0
c number_of_2-reductions                8
c number_of_pure_literals               0
c number_of_autarkies                   0
c number_of_missed_single_nodes         0
c max_tree_depth                        12
c number_of_table_enlargements          0
c number_of_1-autarkies                 0
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             VanDerWaerden_pd_2-5-8_324.cnf
c splitting_directory                   SplitViaOKsolver_D12SDVanDerWaerden_pd_258_324cnf_2011-05-15-101121/Instances
c splitting_cases                       4096

# Processing all instances via shell-loop
     \endverbatim
     Aborted after 3200m where 2500 sub-instances were solved. This is much
     worse than depth 16 (see below). </li>
     <li> Now with depth 16, again using the depth-interpretation (from the
     above time, we get an "average" of 70.4s per sub-instance):
     \verbatim
> SplittingViaOKsolver -D16 -SD VanDerWaerden_pd_2-5-8_324.cnf
> cd SplitViaOKsolver_D16SDVanDerWaerden_pd_258_324cnf_2011-08-13-092457/
> more Md5sum
df571321afc590fa67f5cec11a8499a0
> more Statistics
> E=read.table("Data")
> summary(E$n)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  16.00   19.00   21.00   21.49   23.00   53.00
> table(E$n)
  16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31
 800 3146 6552 8855 9865 9037 7533 5790 4329 2867 1917 1253  888  681  472  370
  32   33   34   35   36   37   38   39   40   41   42   43   44   45   46   47
 282  180  122   97   76   68   66   35   33   30   21   18    8    9   10    7
  48   49   50   51   52   53
   8    1    3    3    2    1
> more Result
s UNKNOWN
c sat_status                            2
c initial_maximal_clause_length         8
c initial_number_of_variables           162
c initial_number_of_clauses             9973
c initial_number_of_literal_occurrences 60446
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   0
c running_time(sec)                     556.5
c number_of_nodes                       131045
c number_of_single_nodes                0
c number_of_quasi_single_nodes          0
c number_of_2-reductions                3415
c number_of_pure_literals               0
c number_of_autarkies                   0
c number_of_missed_single_nodes         0
c max_tree_depth                        16
c number_of_table_enlargements          0
c number_of_1-autarkies                 0
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             VanDerWaerden_pd_2-5-8_324.cnf
c splitting_directory                   SplitViaOKsolver_D16SDVanDerWaerden_pd_258_324cnf_2011-08-13-092457/Instances
c splitting_cases                       65435

# Processing all instances via shell-loop:
# Completed (cs-oksvr):
real    3051m16.442s
user    3041m24.429s
sys     38m48.998s
     \endverbatim
     Needs to be re-done with complete data collection. But this is a speed
     up by one order of magnitude! </li>
     <li> So we see that via splitting we can be much faster! Perhaps one
     could roughly say that conflict-driven solvers are most effective on
     easy instances. Once they "learned too much" they are becoming very
     ineffective. </li>
     <li> Now using the n-interpretation for the splitting (cs-oksvr):
     \verbatim
> SplittingViaOKsolver -D20 VanDerWaerden_pd_2-5-8_324.cnf
> cd SplitViaOKsolver_D20VanDerWaerden_pd_258_324cnf_2011-08-13-100405/
> cat Md5sum
eddf332aaa434cc2b1368a6142294914
> cat Statistics
> E=read.table("Data")
> summary(E$n)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  20.00   20.00   20.00   20.78   21.00   45.00
> table(E$n)
   20    21    22    23    24    25    26    27    28    29    30    31    32
51422 18774  9798  4237  1894   807   339   180    88    53    33    16     9
   33    34    35    36    38    45
    4     2     4     4     2     1
> cat Result
s UNKNOWN
c sat_status                            2
c initial_maximal_clause_length         8
c initial_number_of_variables           162
c initial_number_of_clauses             9973
c initial_number_of_literal_occurrences 60446
c running_time(sec)                     1411.1
c number_of_nodes                       175357
c number_of_single_nodes                0
c number_of_quasi_single_nodes          0
c number_of_2-reductions                1831
c number_of_pure_literals               0
c number_of_autarkies                   0
c number_of_missed_single_nodes         0
c max_tree_depth                        20
c file_name                             VanDerWaerden_pd_2-5-8_324.cnf
c splitting_directory                   SplitViaOKsolver_D20VanDerWaerden_pd_258_324cnf_2011-08-13-100405/Instances
c splitting_cases                       87667

> ProcessSplitViaOKsolver SplitViaOKsolver_D20VanDerWaerden_pd_258_324cnf_2011-08-13-100405
# total process time not available due to earlier version
> E=read_processsplit_minisat()
87667: 36.88h, sum-cfs=4.394574e+09, mean-t=1.515s, mean-cfs=50128
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  0.016   0.224   0.504   1.515   1.252 244.200
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
      7    8158   18650   50130   45420 5684000
     \endverbatim
     Say 40h~1.7d total process time, makes a speed-up of 53.3/1.7 ~ 30,
     where an optimal parallelisation can be achieved with up to
     40h~144000s/245 ~ 580 processors. </li>
    </ol>
   </li>
   <li> Certificates:
    <ol>
     <li> n=311:
     \verbatim
1,6,8,9,11,14,16,17,19,22,
26,29,30,32,33,35,40,41,49,50,
55,57,60,61,62,64,68,71,73,74,
75,76,79,80,81,83,84,85,88,89,
90,91,93,96,100,102,104,106,107,109,
114,115,123,124,129,131,132,134,135,136,
138,142,145,147,148,149,150,153,154,155
     \endverbatim
     </li>
     <li> n=322:
     \verbatim
1,2,4,5,6,7,13,14,18,21,
27,32,35,37,39,41,45,46,47,48,
50,51,52,53,55,56,62,64,66,68,
71,76,82,85,89,90,94,96,97,99,
100,101,102,108,109,110,112,120,125,126,
127,129,133,135,136,138,139,140,143,144,
145,150,152,153,154,156,159
     \endverbatim
    </ol>
   </li>
   <li> "RunPdVdWk1k2 5 8 adaptg2wsat 100 1000000" yields
   \verbatim
Break point 1: 306
Break point 2: 323
   \endverbatim
   </li>
   <li> However minisat-2.2.0 determines instances with n <= 312 as
   satisfiable. So this is our first case of a failure of the
   RunPdVdWk1k2-method. Increase the cutoff. </li>
   li> "RunPdVdWk1k2 5 8 adaptg2wsat 100 2000000" yields
   \verbatim
Break point 1: 312
Break point 2: 323
   \endverbatim
   finding all solutions in the first run with the previous solution.
   </li>
  </ul>

*/
