// Oliver Kullmann, 13.12.2010 (Swansea)
/* Copyright 2010 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/VanderWaerdenProblems/plans/3-k/36.hpp
  \brief On investigations into vdw_2(3,36)


  \todo vanderwaerden_2(3,36) > 1255
  <ul>
   <li> The very weak current conjecture is vanderwaerden_2(3,36) = 1256. </li>
   <li> Starting search with the best palindromic solution:
   \verbatim
> k=36 n=1174 cutoff=10000000 expdate="2010-12-02-143818"; export k n; cat AltExp/Exp_PdVanderWaerden_2-3-${k}_gsat-tabu-100-${cutoff}_${expdate}/VanDerWaerden_pd_2-3-${k}_${n}.cnf_sol | PdExtend-O3-DNDEBUG ${n} > solution

> RunVdW3k ${k} ${n} rots 100 100000000 solution
   \endverbatim
   </li>
   <li> n=1203 found satisfiable with certificate
   \verbatim
34,46,71,72,79,83,85,88,89,101,
126,145,146,148,153,162,177,183,185,194,
214,233,268,273,293,296,301,307,310,311,
344,348,360,368,379,397,399,421,422,442,
473,479,486,495,508,510,527,545,555,560,
589,597,606,626,627,643,644,658,666,681,
695,700,714,737,740,745,749,751,767,782,
792,823,825,829,849,851,856,878,888,922,
923,934,952,954,960,973,996,999,1028,1034,
1047,1063,1065,1073,1082,1088,1100,1125,1156,1161,
1193
   \endverbatim
   </li>
   <li> n=1214 found satisfiable with certificate
   \verbatim
2,28,33,67,80,114,117,125,142,144,
151,155,187,209,213,215,216,218,244,246,
253,265,266,287,289,303,324,336,339,347,
366,394,401,410,438,440,446,447,458,468,
472,505,524,525,551,562,585,595,606,631,
643,659,668,673,694,696,697,717,746,768,
770,773,779,805,808,810,817,820,838,845,
853,857,879,891,902,921,928,932,949,964,
986,1001,1002,1005,1006,1013,1027,1050,1066,1067,
1079,1104,1117,1143,1154,1186,1214
   \endverbatim
   </li>
   <li> n=1232 found satisfiable with certificate
   \verbatim
31,64,73,74,86,93,96,111,130,131,
147,168,181,197,199,222,234,236,249,278,
281,286,292,295,296,310,316,318,352,353,
360,369,401,406,407,419,429,440,444,480,
493,514,530,551,555,569,582,606,612,619,
623,625,648,678,685,688,693,697,715,717,
725,730,734,759,776,791,796,797,808,834,
851,873,884,910,924,925,945,956,962,981,
984,995,998,1019,1030,1035,1048,1050,1063,1085,
1087,1110,1129,1130,1141,1161,1167,1180,1184,1206
   \endverbatim
   </li>
   <li> n=1244 found satisfiable with certificate
   \verbatim
18,37,52,80,91,99,128,134,166,171,
173,191,195,222,237,240,260,263,265,274,
284,297,313,321,337,343,356,371,374,385,
388,408,417,424,432,459,461,467,499,504,
518,522,528,559,561,565,570,572,573,592,
615,617,633,646,667,684,689,703,721,740,
741,746,750,778,783,792,818,829,839,851,
852,876,894,898,905,925,948,966,968,985,
987,1000,1009,1017,1036,1040,1051,1073,1079,1090,
1091,1116,1127,1133,1151,1162,1170,1172,1188,1209,
1236
   \endverbatim
   </li>
   <li> n=1253 found satisfiable with certificate
   \verbatim
33,51,70,84,101,122,125,127,136,138,
173,183,196,220,242,247,249,250,269,279,
287,292,294,307,312,323,329,343,344,361,
380,384,390,395,398,423,442,458,460,464,
471,477,506,528,529,553,565,569,571,580,
583,606,612,645,656,691,694,699,728,730,
738,767,773,775,788,797,810,824,842,849,
871,898,904,908,915,935,939,941,952,953,
958,973,976,1009,1010,1026,1032,1050,1052,1056,
1071,1084,1093,1098,1121,1126,1157,1167,1172,1175,
1198,1219,1249
   \endverbatim
   </li>
   <li> n=1255 found satisfiable with certificate
   \verbatim
25,36,72,73,80,103,109,142,164,168,
171,173,180,191,201,216,247,253,282,284,
291,294,328,332,339,353,355,358,386,405,
413,423,427,430,464,466,475,480,503,534,
541,549,550,558,586,587,590,612,615,617,
649,654,665,688,702,709,725,735,756,771,
776,783,799,802,812,820,830,836,839,849,
874,894,908,913,923,941,957,960,961,982,
985,1019,1022,1031,1035,1042,1058,1068,1093,1098,
1104,1116,1145,1163,1178,1182,1183,1200,1215,1216,
1241,1244
   \endverbatim
   </li>
   <li> n=1256:
    <ol>
     <li> rots, cutoff=10^8:
     \verbatim
 1  2  3
16 74 10
100
     \endverbatim
     </li>
    </ol>
   </li>
  </ul>


  \todo Palindromic version:
  <ul>
   <li> 1174 < vanderwaerden_g([3,36],"pd") =(conj) 1175 =(conj)
   vanderwaerden([3,36]) - 81. </li>
   <li> vanderwaerden_g([3,36],"pdsat") =(conj) 1158. </li>
   <li> Certificates:
    <ol>
     <li> n=1158:
     \verbatim
27,56,58,62,74,91,101,130,132,148,
149,154,161,165,171,187,189,218,228,232,
257,263,270,276,301,305,321,338,346,364,
393,399,428,432,467,469,473,475,486,498,
520,537,569,572
     \endverbatim
     </li>
     <li> n=1174:
     \verbatim
27,32,40,57,62,79,93,110,116,120,
121,145,151,167,168,196,203,232,234,237,
254,283,289,293,320,337,339,342,356,380,
394,396,409,425,431,448,460,483,512,514,
515,522,549,552,571,577
     \endverbatim
     </li>
    </ol>
   </li>
   <li> "RunPdVdW3k 36 gsat-tabu 100 20000000" (older version, without also
   using solution for n-1 in the alternation phase) yields
   \verbatim
Break point 1: 1158
Break point 2: 1175
   \endverbatim
   where all solutions were found within in the first 43 runs (so the second
   break-point is rather weak). </li>
   <li> Rerunning it with doubled cutoff, and using the solution for n-1.
   We also need the ability to start late. </li>
  </ul>

*/
