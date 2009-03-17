// Oliver Kullmann, 16.2.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/VanderWaerdenProblems/plans/Transversals.hpp
  \brief Investigating the transversal hypergraph of van-der-Waerden hypergraphs

  The transversal hypergraph T(n,k) of arithprog_hg(k,n) for fixed k and
  running n has at least been implicitly studied for over 70 years in the
  form of r_k(n), the independence number of arithprog_hg(k,n).
  <ul>
   <li> It seems more natural to study the transversal number of
   arithprog_hg(k,n), that is, the minimal length of a hyperedge of T(n,k).
   </li>
   <li> The literature seems to concentrate on asymptotic results for r_k(n).
   </li>
   <li> This we want to complement by detailed studies on T(n,k). </li>
   <li> Considering the independence number instead of the transversal number,
   there are results in the literature (see below). </li>
  </ul>


  \todo Naming the transversal hypergraph of arithprog_hg(k,n)
  <ul>
   <li> Calling it tr_arithprog_hg(k,n). </li>
   <li> Perhaps tr_arithprog_hg(k,n) is a function which calls the special
   algorithms for computing transversal hypergraphs, according to which is
   best. </li>
   <li> For a hypergraph G, tau(G) is the transversal number. How to call
   the transversal number of arithprog_hg(k,n)? tau_arithprog_hg(k,n). </li>
   <li> While the independence number shall be called alpha_arithprog_hg(k,n).
   </li>
  </ul>


  \todo Relations to vanderwaerden_k(n_1, ..., n_k)
  <ul>
   <li> Let [2]_k denotes the list of k 2's. </li>
   <li> Then we have vanderwaerden_{k+1}([2]_k, m) > n iff
   tau_arithprog_hg(m,n) <= k. </li>
   <li> vanderwaerden_{k+1}([2]_k, m) is the smallest n such that
   however k numbers are picked, an arithmetic progression of size m
   must be contained. </li>
   <li> In other words, vanderwaerden_{k+1}([2]_k, m) is the smallest n such
   that tau_arithprog_hg(m,n) > k. </li>
   <li> It seems that for computing vanderwaerden_{k+1}([2]_k, m), we best
   search for the smallest n with tau_arithprog_hg(m,n) >= k+1 --- in this way
   we have only to decide whether or not a transversal of size at most k
   exists. This amounts to the same as computing the numbers
   tau_arithprog_hg(m,n) in succession, just using that these numbers are
   non-decreasing and each step is at most 1. </li>
   <li> A related sequence is A065825, which for given k is the smallest
   n such that alpha_arithprog_hg(3,n) = k. </li>
   <li> The known values are
   1, 2, 4, 5, 9, 11, 13, 14, 20, 24, 26, 30, 32, 36, 40, 41, 51, 54, 58, 63,
   71, 74, 82, 84, 92, 95, 100, 104, 111, 114, 121, 122, 137, 145, 150, 157,
   starting with k=1. </li>
   <li> For given m, the sequences vanderwaerden_{k+1}([2]_k, m),
   tau_arithprog_hg(m,n), alpha_arithprog_hg(3,n), A065825 are related as
   follows:
    <ol>
     <li> Given the sequence vanderwaerden_{k+1}([2]_k, m), one obtains
     tau_arithprog_hg(m,n) by running through k=0,1,..., and observing
     when first the value is strictly greater than n --- for this k we
     have tau_arithprog_hg(m,n) = k. </li>
     <li> The associated transformation function, where L is a strictly
     increasing sequence of natural numbers (the indices here start with 0):
     \verbatim
transform_threshold_l(L) := 
if emptyp(L) then [] else block(
 [n : 0, k : 0, R : []],
  for x in endcons(last(L)+1,L) do (
    if x > n then (
      R : append(R,create_list(k,i,1,x-n)), 
      n : x
    ),
    k : k+1
  ),
  return(R))$
     \endverbatim
     </li>
     <li> Given the sequence tau_arithprog_hg(m,n), one obtains
     vanderwaerden_{k+1}([2]_k, m) by running through n=0,1,..., and observing
     when first the value is strictly greater than k --- for this n we have
     vanderwaerden_{k+1}([2]_k, m) = n. </li>
     <li> In other words, the values of tau_arithprog_hg(m,n) are exactly the
     step-indices, where the value of tau_arithprog_hg(m,n) increases by one. </li>
     <li> The transformer (where L is a non-decreasing sequence of natural
     numbers, and the indices here start with 0):
     \verbatim
transform_steps_l(L) := if length(L) <= 1 then [] else
 block([a : first(L), i : 1, R : []],
  for b in rest(L) do (
    if b > a then (R : endcons(i,R), a : b),
    i : i + 1
  ),
  return(R))$
     \endverbatim
     </li>
     <li> Given the sequence vanderwaerden_{k+1}([2]_k, m), one obtains
     A065825 XXX </li>
    </ol>
   </li>
  </ul>


  \todo Studying the transversal hypergraph
  <ul>
   <li> If the transversal-number t(n) increases (by one, i.e., it becomes
   t(n+1) = t(n) + 1), then for the set MTr(n) of minimum transversals we
   have |MTr(n+1)| >= |MTr(n)|, since for T in MTr(n) we have T + {n+1}
   in MTr(n+1). </li>
   <li> The other elements T in MTr(n+1) (in this case) are exactly the
   transversals T of G(n) of length t(n)+1 (using only vertices 1,...,n)
   which are also transversals of G(n+1), that is, they are (exactly) the
   minimum transversals of G(n) where those arithmetic progressions P of
   length 3-1=2 are added which yield an arithmetic progressions P + {n+1}
   of length 3. </li>
   <li> It seems possible that there are no such other elements T, i.e.,
   |MTr(n+1)| = |MTr(n)| seems possible? </li>
   <li> If on the other hand t(n) = t(n+1), then MTr(n+1) is exactly the
   (non-empty) set of T in MTr(n) which happen to be also transversals
   of MTr(n+1). </li>
   <li> So here we have |MTr(n+1)| <= |MTr(n)|. Equality seems possible?
   </li>
   <li> One can ask whether the count 1 of minimum transversals occurs
   infinitely often? Or more generally, whether every number occurs as
   count, and this infinitely often? </li>
   <li> One should have a look at the cases where we have a unique
   transversal. Perhaps these sets, as sequences, are known? </li>
  </ul>


  \todo Efficient computation of the transversal number
  <ul>
   <li> Yet the fastest algorithm is minimum_transversals_mongen, based on
   the simple algorithm transversals_bes.
    <ol>
     <li> It could be improved by incorporating the upper bounds coming
     from tau_arithprog_hg(k,x+y) <=  sum_i i in {x,y} tau_arithprog_hg(k,i).
     </li>
     <li> This should be done by first pre-computing for i in
     {1,...,n-1} the transversal number for the hypergraphs restricted
     to {1,...,i} and {i+1,...,n}, with i and n-i vertices, that is
     tau_arithprog_hg(k,i) and tau_arithprog_hg(k,n-i); lets call these
     numbers a_i and b_i. </li>
     <li> For the current partial transversal T these numbers are updated
     as new-a_i = max(old-a_i, T intersect {1,...,i}) and
     new-b_i = max(old-b_i, T intersect {i+1,...,n}). </li>
     <li> We must always have a_i + b_i <= B (where B is the current upper
     bound, which in our case is actually the (precise) transversal number).
     </li>
     <li> So each time a new element is added to the T, the numbers a_i, b_i
     are updated, and the branch is aborted when a_i + b_i > B. </li>
     <li> Of course, one could use look-ahead. What we have is just an
     additional active clause, controlling the "local sizes" of T (including
     the total size). </li>
     <li> More generally, applicable for arbitrary hypergraphs, we have given
     an upper bound B on the size of transversal T for hypergraph G, and
     for certain partitions A, B of the vertex set we have given lower bounds
     a, b on the transversal number of G_A, G_B, obtained by considering only
     hyperedges completely contained in A resp. B. Then we must have
     max(|T intersect A|,a) + max(|T intersect B|,b) <= B. </li>
     <li> As constraints, using boolean variables v in V(G), we get
     sum V(G) = B, sum A >= a, sum B >= b. </li>
     <li> This can be used in SAT solvers supporting cardinality constraints,
     or in constraint solvers. It seems, though, that only the above
     implications can be drawn (w.r.t. partial assignments!). </li>
     <li> No, actually also the lower bounds themselves can be used, either
     when too many vertices are crossed out, so that the lower bound can not
     be reached, or, just before that, when all remaining vertices have
     to be used to reach the lower bound. </li>
     <li> Regarding the lower bounds, we can consider arbitrary intervals
     {i, ..., j} <= {1,...,n}, where we must have
     |T intersect {i,...,j}| >= tau_transversal_hg(k,j-i+1). </li>
     <li> As above, using B we obtain also an upper bound on
     |T intersect {i,...,j}|, where this time in general the complement is
     the (disjoint) union of two intervals {1,...,i-1} and {j+1,...,n}. </li>
    </ol>
   </li>
   <li> A C++ implementation should be able to go quite beyond the known
   numbers:
    <ol>
     <li> See Hypergraphs/Transversals/plans/SizeParameter.hpp. </li>
    </ol>
   </li>
  </ul>


  \todo Translations to SAT
  <ul>
   <li> Alternatively SAT solvers with the ability to formulate cardinality
   constraints can be used. </li>
   <li> We have already implemented (as an old C++ program) the translation
   of linear inequalities into CNF, and so we can also use (ordinary) SAT
   solvers.
    <ol>
     <li> By "VdWTransversals 3 54 35" we create a Dimacs file, containing the
     hypergraph clauses for n=53 plus the upper bound (here b=35) on the
     transversal size (so that in this case the clause-set is unsatisfiable,
     while for b=36 it is satisfiable). </li>
     <li> And via "VdWTransversalsInc 3 1 0 OutputFile" we compute all the
     transversal number for k=3, starting with n=1. </li>
     <li> It seems that OKsolver_2002 and march_pl need a long time.
     \verbatim
> VdWTransversals 3 40 24
> OKsolver_2002-O3-DNDEBUG vdw_trans_3_40_24.cnf
s UNSATISFIABLE
c sat_status=0 initial_maximal_clause_length=4 initial_number_of_variables=169 initial_number_of_clauses=1067 initial_number_of_literal_occurrences=3459 running_time(s)=84.4 number_of_nodes=870214 number_of_single_nodes=3257 number_of_quasi_single_nodes=483 number_of_2-reductions=2279568 number_of_pure_literals=0 number_of_autarkies=4500 number_of_missed_single_nodes=6084 max_tree_depth=43 number_of_table_enlargements=0 reduced_maximal_clause_length=0 reduced_number_of_variables=2 reduced_number_of_clauses=6 reduced_number_of_literal_occurrences=17 number_of_1-autarkies=74022 number_of_initial_unit-eliminations=2 number_of_new_2-clauses=0 maximal_number_of_added_2-clauses=0 initial_number_of_2-clauses=77 file_name=vdw_trans_3_40_24.cnf
> march_pl vdw_trans_3_40_24.cnf
 main():: nodeCount: 98655
c main():: dead ends in main: 6199
c main():: lookAheadCount: 5794240
c main():: unitResolveCount: 1044234
c main():: time=28.300000
c main():: necessary_assignments: 54362
c main():: bin_sat: 0, bin_unsat 0
c main():: doublelook: #: 201867, succes #: 120077
c main():: doublelook: overall 3.646 of all possible doublelooks executed
c main():: doublelook: succesrate: 59.483, average DL_trigger: 85.056
s UNSATISFIABLE
> minisat vdw_trans_3_40_24.cnf
restarts              : 11
conflicts             : 11766          (41436 /sec)
decisions             : 14215          (50061 /sec)
propagations          : 407118         (1433736 /sec)
conflict literals     : 100155         (30.29 % deleted)
Memory used           : 3.54 MB
CPU time              : 0.283956 s
UNSATISFIABLE
> minisat vdw_trans_3_40_24.cnf
restarts              : 10
conflicts             : 8745           (49414 /sec)
decisions             : 10541          (1.53 % random) (59563 /sec)
propagations          : 281265         (1589310 /sec)
conflict literals     : 71249          (32.64 % deleted)
Memory used           : 1.82 MB
CPU time              : 0.176973 s
UNSATISFIABLE
> OKsolver_2002-O3-DNDEBUG vdw_trans_3_40_25.cnf
s SATISFIABLE
c sat_status=1 initial_maximal_clause_length=4 initial_number_of_variables=169 initial_number_of_clauses=1066 initial_number_of_literal_occurrences=3456 running_time(s)=13.5 number_of_nodes=149781 number_of_single_nodes=1054 number_of_quasi_single_nodes=155 number_of_2-reductions=372636 number_of_pure_literals=0 number_of_autarkies=1084 number_of_missed_single_nodes=1602 max_tree_depth=40 number_of_table_enlargements=0 reduced_maximal_clause_length=0 reduced_number_of_variables=2 reduced_number_of_clauses=6 reduced_number_of_literal_occurrences=17 number_of_1-autarkies=17208 number_of_initial_unit-eliminations=2number_of_new_2-clauses=0 maximal_number_of_added_2-clauses=0 initial_number_of_2-clauses=77 file_name=vdw_trans_3_40_25.cnf
c main():: nodeCount: 32051
c main():: dead ends in main: 1503
c main():: lookAheadCount: 1972878
c main():: unitResolveCount: 369319
c main():: time=8.890000
c main():: necessary_assignments: 21652
c main():: bin_sat: 0, bin_unsat 0
c main():: doublelook: #: 63523, succes #: 37370
c main():: doublelook: overall 3.371 of all possible doublelooks executed
c main():: doublelook: succesrate: 58.829, average DL_trigger: 83.574
c main():: SOLUTION VERIFIED :-)
s SATISFIABLE
> minisat vdw_trans_3_40_25.cnf
restarts              : 3
conflicts             : 431            (43109 /sec)
decisions             : 797            (79716 /sec)
propagations          : 9278           (927986 /sec)
conflict literals     : 3207           (8.94 % deleted)
Memory used           : 3.42 MB
CPU time              : 0.009998 s
SATISFIABLE
> minisat2 vdw_trans_3_40_25.cnf
restarts              : 5
conflicts             : 838            (46563 /sec)
decisions             : 1287           (1.48 % random) (71512 /sec)
propagations          : 20505          (1139357 /sec)
conflict literals     : 8038           (15.58 % deleted)
Memory used           : 1.69 MB
CPU time              : 0.017997 s
SATISFIABLE
     \endverbatim
     </li>
     <li> One should investigate whether the minisat-preprocessor makes
     things easier.
     \verbatim
> minisat2 -dimacs=vdw_trans_3_40_24_m2pp.cnf vdw_trans_3_40_24.cnf
> OKsolver_2002-O3-DNDEBUG vdw_trans_3_40_24_m2pp.cnf
s UNSATISFIABLE
c sat_status=0 initial_maximal_clause_length=5 initial_number_of_variables=150 initial_number_of_clauses=992 initial_number_of_literal_occurrences=3159 running_time(s)=28.4 number_of_nodes=278736 number_of_single_nodes=39 number_of_quasi_single_nodes=307 number_of_2-reductions=846245 number_of_pure_literals=0 number_of_autarkies=3786 number_of_missed_single_nodes=208 max_tree_depth=34 number_of_table_enlargements=0 reduced_maximal_clause_length=0 reduced_number_of_variables=0 reduced_number_of_clauses=0 reduced_number_of_literal_occurrences=0 number_of_1-autarkies=85839 number_of_initial_unit-eliminations=0 number_of_new_2-clauses=0 maximal_number_of_added_2-clauses=0 initial_number_of_2-clauses=52 file_name=vdw_trans_3_40_24_m2pp.cnf
> march_pl vdw_trans_3_40_24_m2pp.cnf
c main():: nodeCount: 581980
c main():: dead ends in main: 101283
c main():: lookAheadCount: 8918023
c main():: unitResolveCount: 8120863
c main():: time=64.440000
c main():: necessary_assignments: 364624
c main():: bin_sat: 0, bin_unsat 0
c main():: doublelook: #: 504762, succes #: 147097
c main():: doublelook: overall 6.214 of all possible doublelooks executed
c main():: doublelook: succesrate: 29.142, average DL_trigger: 80.024
s UNSATISFIABLE
> minisat2 -dimacs=vdw_trans_3_40_25_m2pp.cnf vdw_trans_3_40_25.cnf
> OKsolver_2002-O3-DNDEBUG vdw_trans_3_40_25_m2pp.cnf
s SATISFIABLE
c sat_status=1 initial_maximal_clause_length=5 initial_number_of_variables=149 initial_number_of_clauses=997 initial_number_of_literal_occurrences=3184 running_time(s)=1.9 number_of_nodes=19311 number_of_single_nodes=19 number_of_quasi_single_nodes=18 number_of_2-reductions=64340 number_of_pure_literals=0 number_of_autarkies=239 number_of_missed_single_nodes=43 max_tree_depth=33 number_of_table_enlargements=0 reduced_maximal_clause_length=0 reduced_number_of_variables=0 reduced_number_of_clauses=0 reduced_number_of_literal_occurrences=0 number_of_1-autarkies=13171 number_of_initial_unit-eliminations=0 number_of_new_2-clauses=0 maximal_number_of_added_2-clauses=0 initial_number_of_2-clauses=47 file_name=vdw_trans_3_40_25_m2pp.cnf
> march_pl vdw_trans_3_40_25_m2pp.cnf
c main():: nodeCount: 360128
c main():: dead ends in main: 47865
c main():: lookAheadCount: 5723996
c main():: unitResolveCount: 4829333
c main():: time=39.310000
c main():: necessary_assignments: 205107
c main():: bin_sat: 0, bin_unsat 0
c main():: doublelook: #: 323254, succes #: 100136
c main():: doublelook: overall 6.250 of all possible doublelooks executed
c main():: doublelook: succesrate: 30.977, average DL_trigger: 78.028
c main():: SOLUTION VERIFIED :-)
s SATISFIABLE
     \endverbatim
     It seems to help OKsolver_2002 (quite a bit, but likely still much worse
     than minisat), while march_pl seems to perform quite a bit worse on
     the preprocessed problems. </li>
     <li> minisat solves the problems (unsatisfiable as well as
     satisfiable) relatively easily (though with n=80 around 15 minutes are
     needed). </li>
     <li> Is minisat2 better than minisat?
     \verbatim
minisat2 vdw_trans_3_64_43.cnf
restarts              : 22
conflicts             : 1261598        (21895 /sec)
decisions             : 1423468        (1.35 % random) (24704 /sec)
propagations          : 68517361       (1189120 /sec)
conflict literals     : 17080977       (44.36 % deleted)
Memory used           : 3.25 MB
CPU time              : 57.6202 s
UNSATISFIABLE
> minisat vdw_trans_3_64_43.cnf
restarts              : 21
conflicts             : 932740         (19276 /sec)
decisions             : 1048977        (21679 /sec)
propagations          : 53595491       (1107628 /sec)
conflict literals     : 12450770       (45.50 % deleted)
Memory used           : 4.73 MB
CPU time              : 48.3876 s
UNSATISFIABLE
> minisat2 vdw_trans_3_65_44.cnf
restarts              : 22
conflicts             : 1324767        (21908 /sec)
decisions             : 1484394        (1.39 % random) (24547 /sec)
propagations          : 71723828       (1186090 /sec)
conflict literals     : 17963070       (42.79 % deleted)
Memory used           : 3.39 MB
CPU time              : 60.4708 s
UNSATISFIABLE
> minisat vdw_trans_3_64_43.cnf
restarts              : 22
conflicts             : 1331275        (18706 /sec)
decisions             : 1490338        (20941 /sec)
propagations          : 76617377       (1076568 /sec)
conflict literals     : 17680839       (44.17 % deleted)
Memory used           : 4.97 MB
CPU time              : 71.1682 s
UNSATISFIABLE
> minisat vdw_trans_3_71_50.cnf
restarts              : 25
conflicts             : 4375702        (15250 /sec)
decisions             : 4893653        (17055 /sec)
propagations          : 265492436      (925292 /sec)
conflict literals     : 65592198       (43.40 % deleted)
Memory used           : 6.57 MB
CPU time              : 286.928 s
SATISFIABLE
> minisat2 vdw_trans_3_71_50.cnf
restarts              : 26
conflicts             : 5730961        (17171 /sec)
decisions             : 6427303        (1.39 % random) (19257 /sec)
propagations          : 320252313      (959508 /sec)
conflict literals     : 86355473       (42.23 % deleted)
Memory used           : 4.94 MB
CPU time              : 333.767 s
SATISFIABLE
     \endverbatim
     It seems that actually minisat might be better on these instances
     than minisat2 (using more space, but less conflicts and less time). </li>
     <li> The satisfiable instances seem rather hard for local search solvers:
     \verbatim
> ubcsat-okl -alg samd -runs 100 -i vdw_trans_3_40_25.cnf
Clauses = 1066
Variables = 169
TotalLiterals = 3456
FlipsPerSecond = 724638
BestStep_Mean = 1531.870000
Steps_Mean = 100000.000000
Steps_Max = 100000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.000000
BestSolution_Median = 1.000000
BestSolution_Min = 1.000000
BestSolution_Max = 1.000000
> ubcsat-okl -alg walksat -runs 100 -i vdw_trans_3_40_25.cnf
Clauses = 1066
Variables = 169
TotalLiterals = 3456
FlipsPerSecond = 1727116
BestStep_Mean = 2559.370000
Steps_Mean = 100000.000000
Steps_Max = 100000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.000000
BestSolution_Median = 1.000000
BestSolution_Min = 1.000000
BestSolution_Max = 1.000000
> ubcsat-okl -alg walksat-tabu -runs 100 -i vdw_trans_3_40_25.cnf
Clauses = 1066
Variables = 169
TotalLiterals = 3456
FlipsPerSecond = 1700680
BestStep_Mean = 6494.100000
Steps_Mean = 100000.000000
Steps_Max = 100000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.000000
BestSolution_Median = 1.000000
BestSolution_Min = 1.000000
BestSolution_Max = 1.000000
> ubcsat-okl -alg rsaps -runs 100 -i vdw_trans_3_40_25.cnf
Clauses = 1066
Variables = 169
TotalLiterals = 3456
FlipsPerSecond = 1050420
BestStep_Mean = 576.900000
Steps_Mean = 100000.000000
Steps_Max = 100000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.000000
BestSolution_Median = 1.000000
BestSolution_Min = 1.000000
BestSolution_Max = 1.000000
     \endverbatim
     So perhaps rsaps is best here.
     </li>
     <li> Higher cutoffs:
     \verbatim
> ubcsat-okl -alg rsaps -runs 100 -cutoff 1000000 -i vdw_trans_3_40_25.cnf
Clauses = 1066
Variables = 169
TotalLiterals = 3456
FlipsPerSecond = 1098388
BestStep_Mean = 35359.710000
Steps_Mean = 964824.390000
Steps_Max = 1000000.000000
PercentSuccess = 7.00
BestSolution_Mean = 0.930000
BestSolution_Median = 1.000000
BestSolution_Min = 0.000000
BestSolution_Max = 1.000000
     \endverbatim
     Finding a local-minimum=1 is very easy (a few hundred steps), but finding
     a solution takes around 400000 steps. Similar for bigger instances:
     \verbatim
> ubcsat-okl -alg rsaps -runs 100 -i vdw_trans_3_71_50.cnf
Clauses = 2593
Variables = 342
TotalLiterals = 8172
FlipsPerSecond = 974659
BestStep_Mean = 3914.710000
Steps_Mean = 100000.000000
Steps_Max = 100000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.000000
BestSolution_Median = 1.000000
BestSolution_Min = 1.000000
BestSolution_Max = 1.000000
> ubcsat-okl -alg rsaps -runs 100 -cutoff 1000000 -i vdw_trans_3_71_50.cnf
Clauses = 2593
Variables = 342
TotalLiterals = 8172
FlipsPerSecond = 908430
BestStep_Mean = 3887.970000
Steps_Mean = 1000000.000000
Steps_Max = 1000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.000000
BestSolution_Median = 1.000000
BestSolution_Min = 1.000000
BestSolution_Max = 1.000000
> ubcsat-okl -alg rsaps -runs 100 -cutoff 10000000 -i vdw_trans_3_71_50.cnf
Clauses = 2593
Variables = 342
TotalLiterals = 8172
FlipsPerSecond = 907663
BestStep_Mean = 3736.860000
Steps_Mean = 10000000.000000
Steps_Max = 10000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.000000
BestSolution_Median = 1.000000
BestSolution_Min = 1.000000
BestSolution_Max = 1.000000
> ubcsat-okl -alg rsaps -runs 100 -cutoff 100000000 -i vdw_trans_3_71_50.cnf
Clauses = 2593
Variables = 342
TotalLiterals = 8172
FlipsPerSecond = 916484
BestStep_Mean = 4043.990000
Steps_Mean = 100000000.000000
Steps_Max = 100000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.000000
BestSolution_Median = 1.000000
BestSolution_Min = 1.000000
BestSolution_Max = 1.000000
     \endverbatim
     One sees that the (very few) solutions are very hard to find for a local
     search algorithm. </li>
     <li> UnitMarch seems not to perform:
     \verbatim
> UnitMarch_32_bits vdw_trans_3_40_25.cnf
     \endverbatim
     seems unsuccesful (unfortunately, there are no statistics available, and
     also the seed can't be changed).
     </li>
     <li> VdWTransversals uses LinInequal-O3-DNDEBUG, which uses only an
     upper bound on the transversal size: It should be more efficient to
     use an (exact) equality; see "Complete LinInequal.cpp" in
     Transformers/Generators/plans/LinInequal.hpp. </li>
    </ol>
   </li>
   <li> Translation to pseudo-boolean problems:
    <ol>
     <li> The first impression, using "VdWTransversalsIncPB 3 1 0 Output"
     instead of "VdWTransversalsInc 3 1 0 Output", is that it is actually
     slower! </li>
    </ol>
   </li>
   <li> Also CSP solvers are interesting here. </li>
  </ul>


  \todo Elementary statistics for k=3
  <ul>
   <li> Just using clause-set statistics-functions:
   \verbatim
L_0_20 : create_list(transversal_hg_rs(arithprog_hg(3,n)),n,0,20)$
for i : 0 thru 20 do (print(i, statistics_fcs(arithprog_hg(3,i)), 
 statistics_fcs(L_0_20[i+1]), ncl_list_fcs(L_0_20[i+1])));
   \endverbatim
   we obtain
   \verbatim
0 [0,0,0,-1,inf] [0,1,0,0,0] [[0,1]]
1 [1,0,0,-1,inf] [1,1,0,0,0] [[0,1]]
2 [2,0,0,-1,inf] [2,1,0,0,0] [[0,1]]
3 [3,1,3,3,3] [3,3,3,1,1] [[1,3]]
4 [4,2,6,3,3] [4,3,4,2,1] [[1,2],[2,1]]
5 [5,4,12,3,3] [5,3,5,2,1] [[1,1],[2,2]]
6 [6,6,18,3,3] [6,4,8,2,2] [[2,4]]
7 [7,9,27,3,3] [7,10,30,3,3] [[3,10]]
8 [8,12,36,3,3] [8,25,100,4,4] [[4,25]]
9 [9,16,48,3,3] [9,38,186,5,4] [[4,4],[5,34]]
10 [10,20,60,3,3] [10,48,264,6,5] [[5,24],[6,24]]
11 [11,25,75,3,3] [11,58,362,7,5] [[5,7],[6,30],[7,21]]
12 [12,30,90,3,3] [12,73,498,8,6] [[6,25],[7,36],[8,12]]
13 [13,36,108,3,3] [13,86,642,9,6] [[6,6],[7,41],[8,32],[9,7]]
14 [14,42,126,3,3] [14,109,878,10,6] [[6,1],[7,14],[8,76],[9,14],[10,4]]
15 [15,49,147,3,3] [15,146,1284,11,7] [[7,4],[8,32],[9,102],[10,6],[11,2]]
16 [16,56,168,3,3] [16,210,2018,12,8] [[8,14],[9,60],[10,131],[11,4],[12,1]]
17 [17,64,192,3,3] [17,285,2959,12,9] [[9,43],[10,92],[11,148],[12,2]]
18 [18,72,216,3,3] [18,411,4578,12,10] [[10,97],[11,160],[12,154]]
19 [19,81,243,3,3] [19,614,7294,13,11] [[11,220],[12,248],[13,146]]
20 [20,90,270,3,3] [20,957,12090,14,11] [[11,2],[12,451],[13,400],[14,104]]
   \endverbatim
   </li>
   <li> So the sequence tau_arithprog_hg(3,n) (starting with n=0) begins with
   0,0,0,1,1,1,2,3,4,4,5,5,6,6,6,7,8,9,10,11,11. </li>
   <li> It follows that the sequence vanderwaerden_{k+1}([2]_k, 3) (starting
   with k=0) begins with
   3,6,7,8,10,12,15,16,17,18,19. </li>
   <li> The sequence n - tau_arithprog_hg(3,n) = r_3(n):
   0,1,2,2,3,4,4,4,4,5,5,6,6,7,8,8,8,8,8,8,9. </li>
   <li> Excluding the first term, this is sequence A003002;
   see [S. S. Wagstaff, Jr., On k-free sequences of integers, Math. Comp., 26
   (1972), 767-771]:
   \verbatim
1, 2, 2, 3, 4, 4, 4, 4, 5, 5, 
6, 6, 7, 8, 8, 8, 8, 8, 8, 9, 
9, 9, 9, 10, 10, 11, 11, 11, 11, 12,
12, 13, 13, 13, 13, 14, 14, 14, 14, 15,
16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
17, 17, 17
   \endverbatim
   (covering the range 1 <= n <= 53, see below for extended data for n <= 59).
   </li>
   <li> So the sequence tau_arithprog_hg(3,n) (starting with n=0) begins with
   \verbatim
0,
0,0,1,1,1,2,3,4,4,5,
5,6,6,6,7,8,9,10,11,11,
12,13,14,14,15,15,16,17,18,18,
19,19,20,21,22,22,23,24,25,25,
25,26,27,28,29,30,31,32,33,34,
34,35,36
   \endverbatim
   </li>
   <li> It follows that the sequence vanderwaerden_{k+1}([2]_k, 3) (starting
   with k=0) begins with
   \verbatim
3,
6,7,8,10,12,15,16,17,18,19,
21,22,23,25,27,28,29,31,33,34,
35,37,38,39,42,43,44,45,46,47,
48,49,50,52,53
   \endverbatim
   (covering the range 0 <= k <= 35. </li>
   <li> Another sequence of interest is the number of hyperedges:
   1,1,1,3,3,3,4,10,25,38,48,58,73,86,109,146,210,285,411,614,957. </li>
   <li> Doesn't seem to be in the eis-database (also after excluding the first
   terms). </li>
   <li> Perhaps also the maximum size of a hyperedge is of interest:
   0,0,0,1,2,2,2,3,4,5,6,7,8,9,10,11,12,12,12,13,14. </li>
   <li> Doesn't seem to be in the eis-database (also after excluding the first
   terms). </li>
   <li> Most natural (and relatively easiest to compute) amongst additional
   data on the transversal hypergraph seems to be the number of minimum
   hyperedges:
   \verbatim
A3(n):=arithprog_hg(3,n)$
L60_3 : minimum_transversals_mongen(60,A3,[{}])$
1 0 1
2 0 1
3 1 3
4 1 2
5 1 1
6 2 4
7 3 10
8 4 25
9 4 4
10 5 24
11 5 7
12 6 25
13 6 6
14 6 1
15 7 4
16 8 14
17 9 43
18 10 97
19 11 220
20 11 2
21 12 18
22 13 62
23 14 232
24 14 2
25 15 33
26 15 2
27 16 12
28 17 36
29 18 106
30 18 1
31 19 11
32 19 2
33 20 4
34 21 14
35 22 40
36 22 2
37 23 4
38 24 86
39 25 307
40 25 20
41 25 1
42 26 4
43 27 14
44 28 41
45 29 99
46 30 266
47 31 674
48 32 1505
49 33 3510
50 34 7726
51 34 14
52 35 50
53 36 156
54 36 2
55 37 8
56 38 26
57 39 56
58 39 2
59 40 4
   \endverbatim
   </li>
   <li> With a C++ implementation this should be extendible to values quite
   a bit beyond the known numbers (see above "Efficient computation of the
   transversal number"). </li>
   <li> Just computing the transversal numbers, using minisat and the
   direct translation (as provided by "VdWTransversalsInc 3 1 0 OutputFile";
   see above):
   \verbatim
60 41
61 42
62 43
63 43
64 44
65 45
66 46
67 47
68 48
69 49
70 50
71 50
72 51
73 52
74 52
75 53
76 54
77 55
78 56
79 57
80 58
81 59
82 59
83 60
84 60
85 61
86 62
87 63
88 64
89 65
90 66
91 67
92 67
   \endverbatim
   </li>
  </ul>


  \todo Elementary statistics for k=4
  <ul>
   <li> The sequence r_4(n) (starting with n=1) is A003003:
   \verbatim
1, 2, 3, 3, 4, 5, 5, 6, 7, 8,
8, 8, 9, 9, 10, 10, 11, 11, 12, 12,
13, 13, 14, 14, 15, 15, 16, 17, 17, 18,
18, 18, 19, 20, 20, 20, 21, 21, 21, 22,
22, 22, 23, 23, 24, 24, 24, 25, 25, 26,
26
   \endverbatim
   (covering the range 1 <= n <= 51). </li>
   <li> Just using clause-set statistics-functions:
   \verbatim
L_0_20_4 : create_list(transversal_hg_rs(arithprog_hg(4,n)),n,0,20)$
for i : 0 thru 20 do (print(i, statistics_fcs(arithprog_hg(4,i)), statistics_fcs(L_0_20_4[i+1]), ncl_list_fcs(L_0_20_4[i+1])));
0 [0,0,0,-1,inf] [0,1,0,0,0] [[0,1]]
1 [1,0,0,-1,inf] [1,1,0,0,0] [[0,1]]
2 [2,0,0,-1,inf] [2,1,0,0,0] [[0,1]]
3 [3,0,0,-1,inf] [3,1,0,0,0] [[0,1]]
4 [4,1,4,4,4] [4,4,4,1,1] [[1,4]]
5 [5,2,8,4,4] [5,4,5,2,1] [[1,3],[2,1]]
6 [6,3,12,4,4] [6,5,8,2,1] [[1,2],[2,3]]
7 [7,5,20,4,4] [7,11,24,3,2] [[2,9],[3,2]]
8 [8,7,28,4,4] [8,14,38,3,2] [[2,4],[3,10]]
9 [9,9,36,4,4] [9,19,58,4,2] [[2,2],[3,14],[4,3]]
10 [10,12,48,4,4] [10,26,94,4,2] [[2,1],[3,8],[4,17]]
11 [11,15,60,4,4] [11,40,164,5,3] [[3,6],[4,24],[5,10]]
12 [12,18,72,4,4] [12,58,258,5,4] [[4,32],[5,26]]
13 [13,22,88,4,4] [13,130,672,6,4] [[4,3],[5,102],[6,25]]
14 [14,26,104,4,4] [14,277,1646,7,5] [[5,30],[6,233],[7,14]]
15 [15,30,120,4,4] [15,404,2621,8,5] [[5,2],[6,209],[7,187],[8,6]]
16 [16,35,140,4,4] [16,661,4742,9,6] [[6,45],[7,458],[8,156],[9,2]]
17 [17,40,160,4,4] [17,961,7478,9,6] [[6,10],[7,260],[8,621],[9,70]]
18 [18,45,180,4,4] [18,1324,11028,10,7] [[7,100],[8,714],[9,484],[10,26]]
19 [19,51,204,4,4] [19,1920,17189,11,7] [[7,24],[8,380],[9,1189],[10,317],[11,10]]
20 [20,57,228,4,4] [20,2904,27602,12,8] [[8,104],[9,1388],[10,1257],[11,152],[12,3]]
   \endverbatim
   </li>
   <li> So the sequence tau_arithprog_hg(4,n) (starting with n=0) begins with
   0,0,0,0,1,1,1,2,2,2,2,3,4,4,5,5,6,6,7,7,8. </li>
   <li> It follows that the sequence vanderwaerden_{k+1}([2]_k, 4) (starting
   with k=0) begins with
   4,7,11,12,14,16,18,20. </li>
   <li> The sequence n - tau_arithprog_hg(4,n) = r_4(n):
   0,1,2,3,3,4,5,5,6,7,8,8,8,9,9,10,10,11,11,12,12. </li>
   <li> Another sequence of interest is the number of hyperedges:
   1,1,1,1,4,4,5,11,14,19,26,40,58,130,277,404,661,961,1324,1920,2904. </li>
   <li> Doesn't seem to be in the eis-database (also after excluding the first
   terms). </li>
   <li> Perhaps also the maximum size of a hyperedge is of interest:
   0,0,0,0,1,2,2,3,3,4,4,5,5,6,7,8,9,9,10,11,12. </li>
   <li> Computing the number of minimum transversals:
   \verbatim
A4(n):=arithprog_hg(4,n)$
L60_4 : minimum_transversals_mongen(60,A4,[{}])$
1 0 1
2 0 1
3 0 1
4 1 4
5 1 3
6 1 2
7 2 9
8 2 4
9 2 2
10 2 1
11 3 6
12 4 32
13 4 3
14 5 30
15 5 2
16 6 45
17 6 10
18 7 100
19 7 24
20 8 104
21 8 10
22 9 210
23 9 12
24 10 115
25 10 2
26 11 80
27 11 8
28 11 4
29 12 12
30 12 2
31 13 17
32 14 121
33 14 6
34 14 2
35 15 10
36 16 62
37 16 6
38 17 64
39 18 359
40 18 14
   \endverbatim
   </li>
  </ul>


  \todo Elementary statistics for k=5
  <ul>
   <li> The sequence r_5(n) (starting with n=1) is A003004:
   \verbatim
1, 2, 3, 4, 4, 5, 6, 7, 8, 8,
9, 10, 11, 12, 12, 13, 14, 15, 16, 16,
16, 16, 16, 17, 18, 18, 19, 20, 21, 21,
22, 22, 23, 24, 24, 25, 26, 27, 28, 28,
29, 30, 31, 32, 32, 32, 32, 32, 33, 33
   \endverbatim
   (covering the range 1 <= n <= 50). </li>
   <li> Some functions to organise the experiment:
   \verbatim
statistics_hg(G) := statistics_fcs(G)$
compute_transversals_hg(k,N) :=
 block([L : []], 
  for n : 0 thru N do block(
   [A : arithprog_hg(k,n), G],
    G : transversal_hg_rs(A), 
    L : endcons(G,L), 
    print(n,statistics_hg(A),statistics_hg(G),ncl_list_fcs(G))),
  return(L))$
   \endverbatim 
   </li>
   <li>
   \verbatim
L_0_20_5 : compute_transversals_hg(5,20);
0 [0,0,0,-1,inf] [0,1,0,0,0] [[0,1]]
1 [1,0,0,-1,inf] [1,1,0,0,0] [[0,1]]
2 [2,0,0,-1,inf] [2,1,0,0,0] [[0,1]]
3 [3,0,0,-1,inf] [3,1,0,0,0] [[0,1]]
4 [4,0,0,-1,inf] [4,1,0,0,0] [[0,1]]
5 [5,1,5,5,5] [5,5,5,1,1] [[1,5]]
6 [6,2,10,5,5] [6,5,6,2,1] [[1,4],[2,1]]
7 [7,3,15,5,5] [7,6,9,2,1] [[1,3],[2,3]]
8 [8,4,20,5,5] [8,8,14,2,1] [[1,2],[2,6]]
9 [9,6,30,5,5] [9,10,21,3,1] [[1,1],[2,7],[3,2]]
10 [10,8,40,5,5] [10,13,30,3,2] [[2,9],[3,4]]
11 [11,10,50,5,5] [11,20,55,4,2] [[2,6],[3,13],[4,1]]
12 [12,12,60,5,5] [12,28,88,4,2] [[2,4],[3,16],[4,8]]
13 [13,15,75,5,5] [13,57,217,5,2] [[2,2],[3,10],[4,42],[5,3]]
14 [14,18,90,5,5] [14,85,358,5,2] [[2,1],[3,6],[4,52],[5,26]]
15 [15,21,105,5,5] [15,124,563,6,3] [[3,5],[4,49],[5,68],[6,2]]
16 [16,24,120,5,5] [16,180,886,6,3] [[3,4],[4,27],[5,128],[6,21]]
17 [17,28,140,5,5] [17,306,1697,7,3] [[3,3],[4,12],[5,110],[6,177],[7,4]]
18 [18,32,160,5,5] [18,483,2920,8,3] [[3,2],[4,4],[5,84],[6,274],[7,118],[8,1]]
19 [19,36,180,5,5] [19,761,4934,8,3] [[3,1],[4,4],[5,33],[6,359],[7,316],[8,48]]
20 [20,40,200,5,5] [20,1199,8346,9,4] [[4,5],[5,24],[6,208],[7,740],[8,220],[9,2]]
   \endverbatim
   </li>
   <li> So the sequence tau_arithprog_hg(5,n) (starting with n=0) begins with
   0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4. </li>
   <li> It follows that the sequence vanderwaerden_{k+1}([2]_k, 5) (starting
   with k=0) begins with
   5,10,15,20. </li>
   <li> The sequence n - tau_arithprog_hg(5,n) = r_5(n):
   0,1,2,3,4,4,5,6,7,8,8,9,10,11,12,12,13,14,15,16,16. </li>
   <li> The sequence length(arithprog_hg(5,n)[2]) begins with
   1,1,1,1,1,5,5,6,8,10,13,20,28,57,85,124,180,306,483,761,1199. </li>
   <li> And the max-rank sequence begins with
   0,0,0,0,0,1,2,2,2,3,3,4,4,5,5,6,6,7,8,8,9. </li>
   <li> Computing the number of minimum transversals:
   \verbatim
A5(n):=arithprog_hg(5,n)$
L40_5 : minimum_transversals_mongen(40,A5,[{}])$
1 0 1
2 0 1
3 0 1
4 0 1
5 1 5
6 1 4
7 1 3
8 1 2
9 1 1
10 2 9
11 2 6
12 2 4
13 2 2
14 2 1
15 3 5
16 3 4
17 3 3
18 3 2
19 3 1
20 4 5
21 5 24
22 6 112
23 7 619
24 7 40
25 7 2
26 8 270
27 8 70
28 8 12
29 8 2
30 9 26
31 9 5
32 10 745
33 10 266
34 10 81
35 11 534
36 11 236
37 11 115
38 11 48
39 11 16
40 12 80
41 12 32
42 12 12
43 12 4
44 12 1
45 13 5
   \endverbatim
   </li>
  </ul>


  \todo Elementary statistics for k=6
  <ul>
   <li> The sequence r_6(n) (starting with n=1) is A003005:
   \verbatim
1, 2, 3, 4, 5, 5, 6, 7, 8, 9,
9, 10, 11, 12, 13, 13, 14, 15, 16, 17,
17, 18, 19, 20, 21, 22, 22, 22, 23, 23,
23, 24, 25, 25, 26, 27, 28, 28, 29, 30,
31, 31, 31, 32, 33, 34, 34, 35, 36, 37
   \endverbatim
   (covering the range 1 <= n <= 50). </li>
   <li>
   \verbatim
L_0_20_6 : compute_transversals_hg(6,20)$
0 [0,0,0,-1,inf] [0,1,0,0,0] [[0,1]]
1 [1,0,0,-1,inf] [1,1,0,0,0] [[0,1]]
2 [2,0,0,-1,inf] [2,1,0,0,0] [[0,1]]
3 [3,0,0,-1,inf] [3,1,0,0,0] [[0,1]]
4 [4,0,0,-1,inf] [4,1,0,0,0] [[0,1]]
5 [5,0,0,-1,inf] [5,1,0,0,0] [[0,1]]
6 [6,1,6,6,6] [6,6,6,1,1] [[1,6]]
7 [7,2,12,6,6] [7,6,7,2,1] [[1,5],[2,1]]
8 [8,3,18,6,6] [8,7,10,2,1] [[1,4],[2,3]]
9 [9,4,24,6,6] [9,9,15,2,1] [[1,3],[2,6]]
10 [10,5,30,6,6] [10,12,22,2,1] [[1,2],[2,10]]
11 [11,7,42,6,6] [11,26,60,3,2] [[2,18],[3,8]]
12 [12,9,54,6,6] [12,37,102,3,2] [[2,9],[3,28]]
13 [13,11,66,6,6] [13,49,147,4,2] [[2,6],[3,37],[4,6]]
14 [14,13,78,6,6] [14,62,202,4,2] [[2,4],[3,38],[4,20]]
15 [15,15,90,6,6] [15,80,277,5,2] [[2,2],[3,40],[4,37],[5,1]]
16 [16,18,108,6,6] [16,177,720,5,3] [[3,26],[4,113],[5,38]]
17 [17,21,126,6,6] [17,346,1601,6,3] [[3,9],[4,120],[5,208],[6,9]]
18 [18,24,144,6,6] [18,543,2746,6,3] [[3,4],[4,74],[5,352],[6,113]]
19 [19,27,162,6,6] [19,697,3733,7,3] [[3,3],[4,44],[5,389],[6,224],[7,37]]
20 [20,30,180,6,6] [20,933,5314,8,3] [[3,2],[4,30],[5,354],[6,421],[7,116],[8,10]]
   \endverbatim
   </li>
   <li> So the sequence tau_arithprog_hg(6,n) (starting with n=0) begins with
   0,0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3. </li>
   <li> It follows that the sequence vanderwaerden_{k+1}([2]_k, 6) (starting
   with k=0) begins with
   6,11,16. </li>
   <li> The sequence n - tau_arithprog_hg(6n) = r_6(n):
   0,1,2,3,4,5,5,6,7,8,9,9,10,11,12,13,13,14,15,16,17. </li>
   <li> The sequence length(arithprog_hg(6,n)[2]) begins with
   1,1,1,1,1,1,6,6,7,9,12,26,37,49,62,80,177,346,543,697,933. </li>
   <li> And the max-rank sequence begins with
   0,0,0,0,0,0,1,2,2,2,2,3,3,4,4,5,5,6,6,7,8. </li>
   <li> Computing the number of minimum transversals:
   \verbatim
oklib_monitor : true;
A6(n):=arithprog_hg(6,n)$
L60_6 : minimum_transversals_mongen(60,A6,[{}])$
1 0 1
2 0 1
3 0 1
4 0 1
5 0 1
6 1 6
7 1 5
8 1 4
9 1 3
10 1 2
11 2 18
12 2 9
13 2 6
14 2 4
15 2 2
16 3 26
17 3 9
18 3 4
19 3 3
20 3 2
21 4 29
22 4 12
23 4 5
24 4 3
25 4 2
26 4 1
27 5 4
28 6 27
29 6 2
30 7 34
31 8 889
32 8 140
33 8 19
34 9 1214
35 9 325
36 9 48
37 9 8
38 10 325
39 10 38
40 10 6
41 10 2
42 11 28
43 12 2810
44 12 725
45 12 262
46 12 53
47 13 1221
48 13 210
49 13 64
50 13 32
51 13 16
52 14
   \endverbatim
   </li>
  </ul>


  \todo Elementary statistics for k=7
  <ul>
   <li>
   \verbatim
L_0_22_7 : compute_transversals_hg(7,22)$
0 [0,0,0,-1,inf] [0,1,0,0,0] [[0,1]]
1 [1,0,0,-1,inf] [1,1,0,0,0] [[0,1]]
2 [2,0,0,-1,inf] [2,1,0,0,0] [[0,1]]
3 [3,0,0,-1,inf] [3,1,0,0,0] [[0,1]]
4 [4,0,0,-1,inf] [4,1,0,0,0] [[0,1]]
5 [5,0,0,-1,inf] [5,1,0,0,0] [[0,1]]
6 [6,0,0,-1,inf] [6,1,0,0,0] [[0,1]]
7 [7,1,7,7,7] [7,7,7,1,1] [[1,7]]
8 [8,2,14,7,7] [8,7,8,2,1] [[1,6],[2,1]]
9 [9,3,21,7,7] [9,8,11,2,1] [[1,5],[2,3]]
10 [10,4,28,7,7] [10,10,16,2,1] [[1,4],[2,6]]
11 [11,5,35,7,7] [11,13,23,2,1] [[1,3],[2,10]]
12 [12,6,42,7,7] [12,17,32,2,1] [[1,2],[2,15]]
13 [13,8,56,7,7] [13,24,55,3,1] [[1,1],[2,15],[3,8]]
14 [14,10,70,7,7] [14,32,80,3,2] [[2,16],[3,16]]
15 [15,12,84,7,7] [15,47,132,4,2] [[2,12],[3,32],[4,3]]
16 [16,14,98,7,7] [16,63,194,4,2] [[2,9],[3,40],[4,14]]
17 [17,16,112,7,7] [17,80,260,5,2] [[2,6],[3,49],[4,24],[5,1]]
18 [18,18,126,7,7] [18,115,406,5,2] [[2,4],[3,48],[4,61],[5,2]]
19 [19,21,147,7,7] [19,213,868,5,2] [[2,2],[3,35],[4,121],[5,55]]
20 [20,24,168,7,7] [20,387,1730,6,2] [[2,1],[3,16],[4,199],[5,142],[6,29]]
21 [21,27,189,7,7] [21,624,3022,7,3] [[3,12],[4,159],[5,369],[6,83],[7,1]]
22 [22,30,210,7,7] [22,848,4436,7,3] [[3,8],[4,141],[5,386],[6,273],[7,40]]
   \endverbatim
   </li>
   <li> So the sequence tau_arithprog_hg(7,n) (starting with n=0) begins with
   0,0,0,0,0,0,0,1,1,1,1,1,1,1,2,2,2,2,2,2,2,3,3. </li>
   <li> It follows that the sequence vanderwaerden_{k+1}([2]_k, 7) (starting
   with k=0) begins with
   7,14,21. </li>
   <li> The sequence n - tau_arithprog_hg(7n) = r_7(n):
   0,1,2,3,4,5,6,6,7,8,9,10,11,12,12,13,14,15,16,17,18,18,19. </li>
   <li> The sequence length(arithprog_hg(7,n)[2]) begins with
   1,1,1,1,1,1,1,7,7,8,10,13,17,24,32,47,63,80,115,213,387,624,848. </li>
   <li> And the max-rank sequence begins with
   0,0,0,0,0,0,0,1,2,2,2,2,2,3,3,4,4,5,5,5,6,7,7. </li>
  </ul>


  \todo Elementary statistics for k=8
  <ul>
   <li>
   \verbatim
L_0_24_8 : compute_transversals_hg(8,24)$
0 [0,0,0,-1,inf] [0,1,0,0,0] [[0,1]]
1 [1,0,0,-1,inf] [1,1,0,0,0] [[0,1]]
2 [2,0,0,-1,inf] [2,1,0,0,0] [[0,1]]
3 [3,0,0,-1,inf] [3,1,0,0,0] [[0,1]]
4 [4,0,0,-1,inf] [4,1,0,0,0] [[0,1]]
5 [5,0,0,-1,inf] [5,1,0,0,0] [[0,1]]
6 [6,0,0,-1,inf] [6,1,0,0,0] [[0,1]]
7 [7,0,0,-1,inf] [7,1,0,0,0] [[0,1]]
8 [8,1,8,8,8] [8,8,8,1,1] [[1,8]]
9 [9,2,16,8,8] [9,8,9,2,1] [[1,7],[2,1]]
10 [10,3,24,8,8] [10,9,12,2,1] [[1,6],[2,3]]
11 [11,4,32,8,8] [11,11,17,2,1] [[1,5],[2,6]]
12 [12,5,40,8,8] [12,14,24,2,1] [[1,4],[2,10]]
13 [13,6,48,8,8] [13,18,33,2,1] [[1,3],[2,15]]
14 [14,7,56,8,8] [14,23,44,2,1] [[1,2],[2,21]]
15 [15,9,72,8,8] [15,50,120,3,2] [[2,30],[3,20]]
16 [16,11,88,8,8] [16,76,212,3,2] [[2,16],[3,60]]
17 [17,13,104,8,8] [17,98,292,4,2] [[2,12],[3,76],[4,10]]
18 [18,15,120,8,8] [18,121,384,4,2] [[2,9],[3,82],[4,30]]
19 [19,17,136,8,8] [19,152,508,5,2] [[2,6],[3,89],[4,56],[5,1]]
20 [20,19,152,8,8] [20,203,722,5,2] [[2,4],[3,84],[4,113],[5,2]]
21 [21,21,168,8,8] [21,263,976,5,2] [[2,2],[3,81],[4,171],[5,9]]
22 [22,24,192,8,8] [22,474,2002,5,3] [[3,64],[4,240],[5,170]]
23 [23,27,216,8,8] [23,737,3347,6,3] [[3,30],[4,310],[5,365],[6,32]]
24 [24,30,240,8,8] [24,1097,5222,6,3] [[3,8],[4,330],[5,676],[6,83]]
   \endverbatim
   </li>
   <li> So the sequence tau_arithprog_hg(8,n) (starting with n=0) begins with
   0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,2,2,2,2,2,2,2,3,3,3. </li>
   <li> It follows that the sequence vanderwaerden_{k+1}([2]_k, 8) (starting
   with k=0) begins with
   8,15,22. </li>
   <li> The sequence n - tau_arithprog_hg(8n) = r_8(n):
   0,1,2,3,4,5,6,7,7,8,9,10,11,12,13,13,14,15,16,17,18,19,19,20,21. </li>
   <li> The sequence length(arithprog_hg(8,n)[2]) begins with
   1,1,1,1,1,1,1,1,8,8,9,11,14,18,23,50,76,98,121,152,203,263,474,737,1097.
   </li>
   <li> And the max-rank sequence begins with
   0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,3,3,4,4,5,5,5,5,6,6. </li>
  </ul>

*/

