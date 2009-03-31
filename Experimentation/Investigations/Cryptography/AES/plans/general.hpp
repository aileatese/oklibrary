// Matthew Gwynne, 27.3.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/Cryptography/AES/plans/general.hpp
  \brief On investigations into the Advanced Encryption Standard


  \todo Improve formulations : MG (as soon as possible)
  <ul>
   <li> Clean-up minisat output (of course, no intermediate results). </li>
   <li> More care! (Of course, the doxygen-output needs to be inspected) </li>
   <li> Explanations needed! </li>
   <li> And discussions! </li>
   <li> DONE No "is useful". </li>
   <li> DONE No "may be used". </li>
  </ul>


  \todo More experiments : MG (as soon as possible)
  <ul>
   <li> For the trivial instances (message and key set) more solvers need to
   be considered. In its own file. </li>
   <li> Also ciphertext and key set are to be investigated. </li>
   <li> What is the meaning of
   "Experiments on AES with the first 32 key bits not set" ? And what does
   the "summary" show? Apparently only trivial results, which are likely of
   no interest. </li>
   <li> Plan for more experiments! </li>
   <li> Solvers to be used : 
   <ul>
    <li> OKsolver </li>
    <li> minisat2 </li>
    <li> ubcsat-1-1-0 </li>
    <li> picosat </li>
    <li> RSat </li>
    <li> Satz </li>
    <li> march </li>
   </ul>
   </li>
  </ul>


  \todo Investigating Sbox given 8 bit input
  <ul>
   <li> Given 8 bits input to the Sbox, the output should be immediately 
   determined without any decisions needed. Is this actually the case? </li>
   <li> This question is motivated by the fact that the full AES translation
   seems to make some decisions when given all the input bits it needs, and
   this should not be the case. </li>
   <li> See Experimentation/Investigations/Cryptography/AES/plans/minisat2.hpp
   for experiments with minisat. </li>
   <li> Looking at this in maxima, with all input bits set to 0 :
   \verbatim
(%i7) apply_pa({-1,-2,-3,-4,-5,-6,-7,-8}, Sbox44ICCNF[2]);
Evaluation took 0.0200 seconds (0.0200 elapsed)
(%o7) {{-16,-15,-14,-13,11,12},{-16,-14,-12,11,13},{-16,-14,-11,15},{-16,-13,11},{-16,-12,15},
       {-16,-11,-9},{-16,-10,11,14},{-16,9,10},{-16,13,15},{-15,-14,-13,11,16},{-15,-14,11,13},
       {-15,-13,-12,11,16},{-15,-13,9,16},{-15,-13,10,16},{-15,-12,-10,11,13},{-15,-12,-9,11,14},
       {-15,-12,11,13,16},{-15,-11,10},{-15,-10,12,13,14,16},{-15,-9,10,11,12},{-15,9,10,14},
       {-15,9,11,14},{-15,10,12,16},{-14,-13,9,11},{-14,-12,-11,10},{-14,-12,-9,13,15},
       {-14,-12,9,10},{-14,-12,9,11,15},{-14,-12,9,11,16},{-14,-12,11},{-14,-11,-9,12,16},
       {-14,-9,10,11,16},{-14,9},{-14,9,10},{-14,9,15},{-14,10,16},{-14,11,16},{-14,12,16},
       {-14,13,16},{-13,-12,-11,14,16},{-13,-12,-9,14},{-13,-12,9},{-13,9,10,12,15},{-13,9,11,14},
       {-13,9,14},{-13,10,16},{-13,12,15,16},{-12,-11,10,13,14,16},{-12,9,10,11,15},{-12,9,11,15},
       {-12,9,13,14},{-11,-9,10,16},{-11,-9,14,15,16},{-11,9,10,14,15},{-11,10,14,15},{-11,14,16},
       {-10,-9,11,14},{-10,9,14,16},{-10,16},{-9,10,11},{-9,10,12,13},{-9,11,12,15},{-9,14,15},
       {-9,14,15,16},{-9,15,16},{9,10,12,13,16},{9,10,12,14},{9,11,12,13,14,15},{9,11,12,15,16},
       {9,11,13},{9,12,14,16},{9,12,16},{9,13,14,16},{10,11,12,14},{10,11,13,14,15,16},{10,12,15},
       {10,13,16},{10,14},{11,12,16},{11,13,14},{11,15,16}}
(%i8) statistics_cs(apply_pa({-1,-2,-3,-4,-5,-6,-7,-8}, Sbox44ICCNF[2]));
Evaluation took 0.0280 seconds (0.0270 elapsed)
(%o8) [8,81,320,6,2]
   \endverbatim
   </li>
   <li> With several different assignments in maxima : 
   \verbatim
(%i5) statistics_cs(apply_pa({-1,-2,-3,-4,-5,-6,-7,-8},Sbox44ICCNF[2]));
Evaluation took 0.0240 seconds (0.0270 elapsed)
(%o5) [8,81,320,6,2]
(%i6) statistics_cs(apply_pa({1,-2,-3,-4,-5,-6,-7,-8},Sbox44ICCNF[2]));
Evaluation took 0.0280 seconds (0.0260 elapsed)
(%o6) [8,81,320,6,2]
(%i7) statistics_cs(apply_pa({-1,2,-3,-4,-5,-6,-7,-8},Sbox44ICCNF[2]));
Evaluation took 0.0280 seconds (0.0250 elapsed)
(%o7) [8,69,272,6,2]
(%i8) statistics_cs(apply_pa({-1,-2,3,-4,-5,-6,-7,-8},Sbox44ICCNF[2]));
Evaluation took 0.0240 seconds (0.0250 elapsed)
(%o8) [8,76,288,6,1]
(%i9) statistics_cs(apply_pa({-1,-2,-3,4,-5,-6,-7,-8},Sbox44ICCNF[2]));
Evaluation took 0.0240 seconds (0.0260 elapsed)
(%o9) [8,74,298,6,2]
(%i10) statistics_cs(apply_pa({-1,-2,-3,-4,5,-6,-7,-8},Sbox44ICCNF[2]));
Evaluation took 0.0240 seconds (0.0240 elapsed)
(%o10) [8,68,264,6,2]
(%i11) statistics_cs(apply_pa({-1,-2,-3,-4,-5,6,-7,-8},Sbox44ICCNF[2]));
Evaluation took 0.0240 seconds (0.0260 elapsed)
(%o11) [8,81,319,6,1]
(%i12) statistics_cs(apply_pa({-1,-2,-3,-4,-5,-6,7,-8},Sbox44ICCNF[2]));
Evaluation took 0.0280 seconds (0.0270 elapsed)
(%o12) [8,84,324,6,1]
(%i13) statistics_cs(apply_pa({-1,-2,-3,-4,-5,-6,-7,8},Sbox44ICCNF[2]));
Evaluation took 0.0240 seconds (0.0250 elapsed)
(%o13) [8,73,287,6,2]
   \endverbatim
   </li>
   <li> Whether or not unit clauses occur immediately after setting all Sbox
   input bits (using the current sbox cnf) depends on the assignment. </li>
   <li> A better Sbox cnf representation seems to be needed. </li>
   <li> However, the primary goal is for problems where the key is not known,
   not simple encryption and decryption, so further insight into where the
   Sbox is used and exactly what bits being set, we wish to allow easier
   deductions with, needs to be known (although many representations can be
   tried). </li>
  </ul>


  \todo Generate problem instances
  <ul>
   <li> To generate instances of AES as a SAT problem where the primary
   variables are the plaintext, key and ciphertext (each 128 variables),
   the following code generates problem instances as described below: 
   \verbatim
removeTopNVars(C,n) := subset(C, lambda([a], is(abs(a) <= (uaapply(max,listify(map(abs,C))) - n))));

hex2il(h) := block([cl],
  cl : charlist(h),
  print(cl),
  return(map(lambda([b], hex2int(simplode(b))), partition_elements(cl,2)))
)$

gen_uc_ass_aes(ph, pbn, kh ,kbn,ch, cbn) := block(
  return(
    map(lambda([a],{a}),union(
      removeTopNVars(AESHexToPA(ph,aes_make_vars_int("p",1,128)),pbn),
      removeTopNVars(AESHexToPA(kh,aes_make_vars_int("k",1,128)),kbn),
      removeTopNVars(AESHexToPA(ch,aes_make_vars_int("c",1,128)),cbn)))));

gen_uc_ass_aes_comp(ph, pbn, kh ,kbn, cbn) := block([ch],
 ch : il2hex(transpose_l(
         aes_encrypt_l(
           hex2il(ph),
           hex2il(kh)),
         4)),
 return(gen_uc_ass_aes(ph,pbn,kh,kbn,ch,cbn))
)$
plaintext_hex : "32488853038D31734198AA2E0370D450"$
key_hex : "3F6A2B7E151628AED2A6ABF7158809CF"$
for r from 2 step 1 thru 10 do block([aes_num_rounds:r],
  aes_cs : aes_cnf_fcs(),
  output_cs_f(sconcat("AES r=",r," NPKC"),aes_cs,sconcat("AES_r",r,".cnf")),
  ch: apply(sconcat,map(lambda([s],lpad(int2hex(s),"0",2)),
    aes_encrypt_l(
      hex2il(plaintext_hex),
      hex2il(key_hex)))
    ),
  for pn from 0 thru 0 do (
    for kn from 0 step 2 thru 64 do (
      for cn from 0 thru 0 do block(
        output_cs_f(
          sconcat("AES UC R=",r," PN=",pn,"KN=",kn,"CN=",cn,
            "P=",plaintext_hex,"K=",key_hex),
          cs_to_fcs(gen_uc_ass_aes(plaintext_hex,pn,key_hex,kn,ch,cn)),
          sconcat("AES_UC_r",r,"_pn",pn,"_kn",kn,"_cn",cn,
            "_P",plaintext_hex,"_K",key_hex,".cnf")),
        print(sconcat("AES UC R=",r," PN=",pn,"KN=",kn,"CN=",cn,
           " P=",plaintext_hex,"K=",key_hex))))));
   \endverbatim
   The above code generates files "AES_r2.cnf" (for round 2 for example) 
   containing the main AES translation (with no variable assignments) and then 
   "AES_UC_r2_pn0_kn0_cn0_P32488853038D31734198AA2E0370D450_K3F6A2B7E151628AED2A6ABF7158809CF.cnf"
   as the unit clauses for setting up a 2 round AES translation with all 
   plaintext, key and ciphertext bits set and the plaintext and key
   provided as "32488853038D31734198AA2E0370D450" and
   "3F6A2B7E151628AED2A6ABF7158809CF" in the standard AES format.
   </li>
   <li> To merge the AES translation cnf with the assignment unit clauses 
   generated, the following script generates the problem instances : 
   \verbatim
#!/bin/bash

# Grab the number of clauses from each
CL1=`grep "^p" $1  | cut -d " " -f "4"`
CL2=`grep "^p" $2  | cut -d " " -f "4"`

NewCL=`expr $CL1 + $CL2`
cat $1 | sed -e "s/p \+\([a-zA-Z]\+\) \+\([0-9]\+\).*$/p \1 \2 $NewCL/"
cat $2 | grep -v "^p"
   \endverbatim
   called "mergeSameVarCNFs.sh" and can be used in the following way : 
   \verbatim
./mergeSameVarCNFs.sh AES_r2.cnf AES_UC_r2_pn0_kn32_cn0_P00000000000000000000000000000000_K00000000000000000000000000000000.cnf > AES_r2_kn_32_P00000000000000000000000000000000_K00000000000000000000000000000000_SAT.cnf   
   \endverbatim
   </li>
   <li> For experimentation, the following is then an example for 
   running a particular SAT solver (minisat in the example below) on the given
   problem instance :
   \verbatim
for k in `seq 0 32 128`; do
  for r in `seq 2 2 10`; do
    echo "K = " $k "R = " $r;
    ./mergeSameVarCNFs.sh "AES_r${r}.cnf" "AES_UC_r${r}_pn0_kn${k}_cn0_P00000000000000000000000000000000_K00000000000000000000000000000000.cnf" > "AES_r${r}_k   n_${k}_P00000000000000000000000000000000_K00000000000000000000000000000000_SAT.cnf" ;
    time ./solvers/minisat/core/minisat "AES_r${r}_kn_${k}_P00000000000000000000000000000000_K00000000000000000000000000000000_SAT.cnf" > "AES_r${r}_kn_${k}_P   00000000000000000000000000000000_K00000000000000000000000000000000_SAT.cnf.results.minisat" 2> "AES_r${r}_kn_${k}_P00000000000000000000000000000000_K000000000   00000000000000000000000_SAT.cnf.results.minisat" ;
  done
done
   \endverbatim
   </li>
  </ul>


  \todo Computing AES ciphertext given full 128-bit key and plaintext
  <ul>
   <li> Question here is : Given the current translation, how well can a SAT
   solver perform a simple AES computation? </li>
   <li> It should be that through unit clause propagation etc, the SAT solver
   should be very quick? </li>
   <li> See Experimentation/Investigations/Cryptography/AES/plans/minisat2.hpp
   for results using minisat2. </li>
   <li> Add results for other solvers. </li>
  </ul>


  \todo Performance of solvers on AES instances with 0-16 key bits unknown
  <ul>
   <li> Question here is : Given the current translation, how many key bits can
   a SAT solver derive in reasonable time given the plaintext and ciphertext, 
   and how does this scale as we leave more key bits unknown? </li>
   <li> This is motivated by the idea to compare such results to brute force. 
   </li>
   <li> 16 bits are used at first to allow a range of results to be generated
   in a reasonable time. The idea is to then move onto larger numbers of unknown
   key bits. </li>
   <li> See Experimentation/Investigations/Cryptography/AES/plans/minisat2.hpp
   for results using minisat2. </li>
   <li> See Experimentation/Investigations/Cryptography/AES/plans/OKsolver.hpp
   for results using OKsolver. </li>
   <li> Add results for other solvers. </li>
  </ul>

*/
