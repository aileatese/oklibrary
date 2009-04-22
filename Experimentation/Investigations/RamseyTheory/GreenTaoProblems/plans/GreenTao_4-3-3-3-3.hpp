// Oliver Kullmann, 22.4.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/GreenTaoProblems/plans/GreenTao_4-3-3-3-3.hpp
  \brief Investigations on greentao_4(3,3,3,3)


  \todo Lower bounds: greentao_3(3,3,3,3) > 363
  <ul>
   <li> Best we see first where adaptnovelty+ finds easily solutions. </li>
   <li> n=300 very easily satisfiable. </li>
   <li> n=338 easily satisfiable. </li>
   <li> n=348 found satisfiable (cutoff=10^6, seed=1463613527). </li>
   <li> n=352 found satisfiable (cutoff=10^6, seed=3476207011). </li>
   <li> n=355 found satisfiable (cutoff=10^6, seed=3865650519). </li>
   <li> n=356 found satisfiable (cutoff=10^6, seed=1266825813). </li>
   <li> n=357
    <ol>
     <li>
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 100 -cutoff 1000000 -i GreenTao_4-3-3-3-3_357.cnf
clauses = 26471
Variables = 1428
TotalLiterals = 77628
FlipsPerSecond = 659761
BestStep_Mean = 447147.770000
Steps_Mean = 1000000.000000
Steps_Max = 1000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 2.330000
BestSolution_Median = 2.000000
BestSolution_Min = 1.000000
BestSolution_Max = 4.000000
     \endverbatim
     seems unsatisfiable.
     </li>
     <li>
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 1000 -cutoff 10000000 -i GreenTao_4-3-3-3-3_357.cnf
Clauses = 26471
Variables = 1428
TotalLiterals = 77628
FlipsPerSecond = 628361
BestStep_Mean = 3492205.863000
Steps_Mean = 9675267.971000
Steps_Max = 10000000.000000
PercentSuccess = 5.90
BestSolution_Mean = 1.236000
BestSolution_Median = 1.000000
BestSolution_Min = 0.000000
BestSolution_Max = 2.000000
     \endverbatim
     A solution was found e.g. with seed=876327096. </li>
    </ol>
   </li>
   <li> n=358 found satisfiable with cutoff=10*10^6 and seed=1641133745. </li>
   <li> n=359 found satisfiable with cutoff=10*10^6 and seed=2108885839. </li>
   <li> n=360 found satisfiable with cutoff=10*10^6 and seed=1802549929. </li>
   <li> n=361 found satisfiable with cutoff=10*10^6 and seed=1427782088
   (140 runs needed). </li>
   <li> n=362 found satisfiable with cutoff=10*10^6 and seed=2256326590. </li>
   <li> n=363 found satisfiable with cutoff=10*10^6 and seed=342405381. </li>
   <li> n=364 </li>
   <li> n=365
    <ol>
     <li>
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 1000 -cutoff 10000000 -i GreenTao_4-3-3-3-3_365.cnf

     \endverbatim
     </li>
    </ol>
   </li>
   <li> n=375: adaptnovelty+ reaches only a minimum about 5. </li>
   <li> n=450: adaptnovelty+ reaches only a minimum about 18. </li>
   <li> n=600
    <ol>
     <li> The instance-generation by Maxima takes far too long.
      <ul>
       <li> nbfcsfd2fcs_aloamo is rather slow, but a worse bottleneck
       is standardise_fcs. </li>
       <li> And worst is standard_statistics_fcs! </li>
       <li> Where actually these statistics are not so informative anymore,
       since they mix three different types of clauses. So we better
       should have separate statistics on the hypergraphs, on the alo-
       and alo-clauses, and for everything together. </li>
      </ul>
     </li>
     <li> adaptnovelty+ reaches only values in the sixties. </li>
    </ol>
   </li>
  </ul>

*/

