// Oliver Kullmann, 19.7.2008 (Swansea)
/* Copyright 2008, 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/RamseyProblems/plans/general.hpp
  \brief On investigations into %Ramsey problems


  \todo Connections
  <ul>
   <li> See ComputerAlgebra/RamseyTheory/Lisp/Ramsey/plans/general.hpp. </li>
   <li> See Ramsey.cpp (to be updated) for a C++ generator. </li>
   <li> See ComputerAlgebra/Hypergraphs/Lisp/plans/Generators.hpp. </li>
   <li> See
   ComputerAlgebra/Satisfiability/Lisp/Generators/RamseyTheory/plans/RamseyProblems.hpp.
   </li>
  </ul>


  \todo Generation of problem instances
  <ul>
   <li> Generation of CNF representations:
    <ol>
     <li> By the Maxima system, via "output_ramsey2_stdname(q,r,n)" we
     create "Ramsey_q_r_n.cnf", for ramsey_2^r(q). </li>
     <li> However, output_ramsey2_stdname(5,2,40) yields a segmentation
     fault on a 32-bit machine (not enough memory, when introducing
     the colouring symbols); so we need to use the following (C++)
     application. </li>
     <li> More generally (and faster), the application "Ramsey" can generate
     also non-diagonal problems, via
     \verbatim
Ramsey-O3-DNDEBUG q1 q2 r n | ExtendedToStrictDimacs-O3-DNDEBUG > Ramsey_q1_q2_r_n.cnf
     \endverbatim
     for ramsey_2^r(q1,q2). </li>
    </ol>
   </li>
  </ul>


  \todo How to handle experimental data?
  <ul>
   <li> How to store the data? </li>
   <li> For the ubcsat-algorithms we need some script to run through all
   of them; see
   ExperimentSystem/ControllingLocalSearch/plans/DataCollection.hpp. </li>
  </ul>


  \todo Data sheets
  <ul>
   <li> All the numbers and all known information should be available
   on some html-page. </li>
  </ul>


  \todo Experiments to be run
  <ul>
   <li> The following experiments need to be discussed and moved to other
   todos, as well as linked in with plans for the experiment system:
    <ul>
     <li> Iterating through UBCSAT algorithms to see which algorithms are best
     for small to medium size %Ramsey problems. See
     ExperimentSystem/ControllingLocalSearch/plans/AlgorithmSelection.hpp.
     </li>
     <li> Running through the parameter space for problems of the form
     ramsey_2^2(q_1,q_2) using the standard, simple translation, to determine
     performance and scalability of solvers on the basic problem. </li>
     <li> Running through the parameter space for the problems of the form
     ramsey_2^2(q_1,q_2) using each symmetry breaking technique to determine
     whether such techniques help solvers to find solutions or prove UNSAT etc. 
     </li>
     <li> Running through the parameter space for the problems of the form
     ramsey_2^2(q_1,q_2) using cardinality constraints (both generated by 
     unary_bb_crd2fcl in 
     ComputerAlgebra/Satisfiability/Lisp/PseudoBoolean/CardinalityConstraints.mac) 
     and potentially any solvers with special handling of cardinality 
     constraints (for example, mxc - see 
     http://www.cs.sfu.ca/research/groups/mxp/MXC/ ). See 
     "Investigate introduction of cardinality constraints".</li>
    </ul>
   </li>
   <li> See 
   Experimentation/Investigations/RamseyTheory/RamseyProblems/plans/Ramsey_2_4_4.hpp
   for investigations concerning ramsey_2^2(4,4) including various symmetry 
   breaking and cardinality constraint conjectures/concerns. </li>
   <li> See 
   Experimentation/Investigations/RamseyTheory/RamseyProblems/plans/Ramsey_2_4_6.hpp
   for investigations concerning ramsey_2^2(4,6) including various symmetry 
   breaking concerns. </li>
   <li> See 
   Experimentation/Investigations/RamseyTheory/RamseyProblems/plans/Ramsey_2_5_5.hpp
   for investigations concerning ramsey_2^2(5,5) including various symmetry 
   breaking and cardinality constraint conjectures/concerns. </li>
   <li> See 
   Experimentation/Investigations/RamseyTheory/RamseyProblems/plans/Ramsey_2_3_10.hpp
   for investigations concerning ramsey_2^2(3,10) including various symmetry 
   breaking and cardinality constraint conjectures/concerns. </li>
  </ul>


  \todo Investigate introduction of cardinality constraints
  <ul>
   <li> It is a conjecture of MG that any %Ramsey problem of the form
   ramsey_2^2(q), if it has a solution, must have a solution where
   the number of edges labelled with one label differs at most one from
   the number of edges labelled with the other. </li>
   <li> The intuition (and potential for generalisation to more than 2
   labels/partitions) is that dominating a labelling/colouring of a graph
   with more of one label/colour than another, simply makes it harder to avoid
   forming monochromatic q-cliques in that label. </li>
  </ul>


  \todo ramsey_2^2(3)
  <ul>
   <li> Satisfiability for n=5 is trivial for any SAT solver. </li>
   <li> So is unsatisfiability for n=6. </li>
  </ul>


  \todo ramsey_2^2(6)
  <ul>
   <li> Known is 102 <= ramsey_2^2(6) <= 165. </li>
   <li> These clause-sets are too big (for direct representation). </li>
  </ul>


  \todo Investigating the parameter tuple [[3,3],2]
  <ul>
   <li> Creating the relevant instances: by
   \verbatim
R5: ramsey2_ofcs(3,2,5);
R6: ramsey2_ofcs(3,2,6);
   \endverbatim
   we create the two relevant (ordered formal) clause-sets. </li>
   <li> Satisfying assignments:
   \verbatim
R5SAT : setify(all_sat_ofcs(R5))$
length(R5SAT);
  12
   \endverbatim
   </li>
   <li> Now we need to investigate the operation of the automorphism group
   of R5 on R5SAT (what are the really different solutions?).
    <ol>
     <li> For this we need to compute the automorphism group of R5; see
     "Automorphisms of Ramsey clause-sets" in
     RamseyTheory/Lisp/Ramsey/plans/general.hpp. </li>
     <li> One solution (as graph; see "Representing solutions as graphs" below)
     is the C^5, and we have all hamiltonian cycles of the K_5 as similar
     solutions under the operation of the S_5: This yields 4! / 2 = 12
     solutions, so actually all solutions are isomorphic to C^5. </li>
     <li> We need to divide by 2 here since we are considering "cyclic
     permutations" (so that [1,2,3,4,5] is the same as [1,5,4,3,2]). </li>
    </ol>
   </li>
   <li> Via
   \verbatim
length(all_aut_ofcs(R5));
  13
   \endverbatim
   we see that there are only the obvious autarkies. </li>
  </ul>


  \todo Exploring the parameter space
  <ul>
   <li> A systematic exploration of different parameter tuples is needed. </li>
   <li> For instance, if one has parameters k and q, and then considers the 
   Ramsey tuple ramsey_(k+1)^2(2,...k times...,2,q) for instance, how do such 
   Ramsey  numbers grow? </li>
  </ul>


  \todo Autarkies
  <ul>
   <li> We should investigate autarkies of Ramsey-clause-sets. </li>
   <li> It could be that for smaller n interesting autarkies exist, and so
   they could serve for providing lower bounds. </li>
  </ul>


  \todo Blocked clauses
  <ul>
   <li> We should investigate blocked clauses of Ramsey-clause-sets. </li>
  </ul>


  \todo Symmetry breaking
  <ul>
   <li> An important way of making the problems simpler for SAT solvers
   is to add symmetry-breaking clauses. </li>
   <li> See "Symmetry breaking" in
   ComputerAlgebra/Satisfiability/Lisp/Generators/RamseyTheory/plans/RamseyProblems.hpp.
   </li>
   <li> We should try to figure out the automorphism groups of the clause-sets.
   See "Automorphisms of Ramsey clause-sets" in
   RamseyTheory/Lisp/Ramsey/plans/general.hpp. </li>
   <li> The goal is to find as many as possible assignments which can
   be made "w.l.o.g."; and also additional short clauses are of interest. </li>
  </ul>


  \todo Representing solutions as graphs
  <ul>
   <li> A solution for the parameter-values ([[p,q],2]; n) (that is,
   a labelling of the K_n with colours 0,1 such that no clique of size p
   of colour 0 and no clique of size q of colour 1 exists), corresponds to
   a graph with n vertices not containing a clique of size p or an independent
   set of size q. </li>
   <li> This graph representation brings with it a notion of isomorphic
   solutions by using graph isomorphisms. </li>
   <li> If p = q, then as an additional symmetry we have the correspondence
   between a graph and its complement. </li>
   <li> The underlying reasoning is as follows:
    <ol>
     <li> We consider the general problem of when two solutions of a
     satisfiability problem are to be considered "similar". </li>
     <li> The strongest possibility (detecting the most similarities) seems
     to use the automorphism group of the set of all (total) solutions,
     and then to consider two solutions as similar iff they are in the
     same orbit under this operation (i.e., there is an automorphism turning
     the one solution into the other). </li>
     <li> This considers only the solution space, not the representation. 
     </li>
     <li> Perhaps most common is to consider the automorphism group of the
     representation (and its operation), which yields a subgroup of the
     automorphism group of the solutions. </li>
     <li> For the Ramsey problems presented as clause-sets we know the
     automorphisms given by S_n, and S_n x ZZ_2 for symmetric problems. </li>
     <li> In the graph-case we are considering here this yields exactly
     to consider two solutions as similar iff their graphs are isomorphic,
     where for symmetric problems we consider also a graph and its
     complement as similar. </li>
    </ol>
   </li>
   <li> For the %Ramsey parameter tuple [[3,3],2] and n = 5 we have the
   solution C^5 (the cycle with 5 edges), which is self-dual (and this
   is the only solution; see above). </li>
   <li> We should have an extensive catalogue as possible for the known
   solution types (if possible, augmented by the information how many
   solutions in total they represent). </li>
  </ul>


  \todo Self-dual solutions
  <ul>
   <li> For the Ramsey parameter tuple [[3,3],2] we have a self-dual
   solution (a graph isomorphic to its complement). </li>
   <li> Are there self-dual solutions for all [[p,p],2] ?? </li>
   <li> We need to check the known cases! </li>
   <li> For [[5,5],2] and n=42 the number of edges (861) of K_n is odd, so
   if the conjecture ramsey_2^2(5,5) = 43 is true, then there would be
   no self-dual solution here. </li>
  </ul>


  \todo "Visualising" solutions
  <ul>
   <li> Via SAT solvers we can compute certain solutions for problems somewhat
   smaller than the interesting sizes. </li>
   <li> The task is to "look" at these solutions, extract some structure, and
   then to systematically search for "such" solutions. </li>
   <li> Of course, everything theoretically known needs to be explored. </li>
   <li> From the practical side, there has been work (e.g., Marijn Heule) for
   van der Waerden problems. </li>
   <li> See "Representing solutions as graphs" above; perhaps that's the
   best what we can do for those problems? But if we know more about the
   symmetries between solutions (i.e., the automorphism group of the solution
   space, then we might obtain further compression. </li>
   <li> There is also the simple representation of these solutions using 
   colours for the two labels/partitions. </li>
   <li> Colouring edges rather than simply showing a graph with edges missing
   seems a much better solution, as from a visualisation point of view, one 
   sees both the graph and it's complement at the same time, and so the colour
   symmetry is more obvious to the eye (as both the graph and it's complement
   are important for discerning patterns). </li>
   <li> Both visualisations should be made available, and translations from a 
   solution (set of literals using the canonical variable naming) to graphs
   and graph labellings should be written. </li>
   <li> Both visualisations are now possible in the library for r=2,s=2:
    <ul>
     <li> Given a partial assignment S as a solution to the %Ramsey problem
     "ramsey_2^2(p,q) > n?", one may show the underlying graph represented
     by the edges labelled with p in the following way:
     \verbatim
n : 17$
S: {1,-2,-3,4,-5,-6,7,8,9,-10,11,-12,13,-14,-15,-16,-17,18,-19,-20,21,-22,23,24,
    -25,26,27,-28,-29,-30,-31,32,-33,34,-35,36,37,-38,39,40,41,-42,43,-44,-45,
    46,47,-48,-49,-50,51,52,-53,54,55,-56,57,-58,-59,60,-61,62,-63,64,-65,66,
    -67,-68,-69,70,71,-72,73,74,75,76,-77,78,-79,80,81,82,-83,-84,-85,86,87,88,
    89,-90,-91,-92,93,94,95,-96,-97,98,-99,-100,-101,-102,103,-104,105,106,107,
    -108,109,-110,111,112,113,-114,-115,-116,-117,118,-119,120,121,-122,123,
    124,125,126,-127,-128,129,-130,-131,132,-133,-134,135,-136}$
draw_graph(g2mg(ramsey_counterex_graph(n,S)))$
     \endverbatim
     </li>
     <li> Given a partial assignment S as a solution to the %Ramsey problem
     "ramsey_2^2(p,q) > n?", one may show the complete graph with different
     coloured edges for the labels p and q in the following way:
     \verbatim
n : 17$
S: {1,-2,-3,4,-5,-6,7,8,9,-10,11,-12,13,-14,-15,-16,-17,18,-19,-20,21,-22,23,
    24,-25,26,27,-28,-29,-30,-31,32,-33,34,-35,36,37,-38,39,40,41,-42,43,-44,
    -45,46,47,-48,-49,-50,51,52,-53,54,55,-56,57,-58,-59,60,-61,62,-63,64,-65,
    66,-67,-68,-69,70,71,-72,73,74,75,76,-77,78,-79,80,81,82,-83,-84,-85,86,
    87,88,89,-90,-91,-92,93,94,95,-96,-97,98,-99,-100,-101,-102,103,-104,105,
    106,107,-108,109,-110,111,112,113,-114,-115,-116,-117,118,-119,120,121,
    -122,123,124,125,126,-127,-128,129,-130,-131,132,-133,-134,135,-136}$
vis_ramsey_sol(n,S) :=
  draw_graph(g2mg(ramsey_counterex_graph(n,S)),
    show_edges=edges(g2mg(comp_graph(ramsey_counterex_graph(n,S)))),
    fixed_vertices=create_list(i,i,1,n))$
vis_ramsey_sol(17,S)$
     \endverbatim
     </li>
    </ul>
   </li>
   <li> The real question is how to draw such things well. </li>
  </ul>


  \todo Statistics functions are needed to analyse counter examples
  <ul>
   <li> Visualising counter examples as in '"Visualising" solutions' seems only
   to be useful for reasonably small "n" and therefore, one should also provide
   statistics functions to extract some summarised information from the
   satisfying assignments we get from these Ramsey problems. </li>
   <li> Some example statistics: 
    <ul>
     <li> Number of edges with each label. </li>
     <li> Frequency distribution of number of a particular colour edges leaving
     each node. </li>
     <li> Number of cycles of a given colour/label of a given length. </li>
    </ul>
   </li>
   <li> Several of these should be possible using the standard 
   statistics/analysis functions already available for graphs. </li>
  </ul>


  \todo Better SAT solvers
  <ul>
   <li> These problems seem to be quite structured, so that quite something
   is known (at least more than for Van der Waerden numbers), but SAT solvers
   apparently can't exploit any of it. </li>
   <li> What about constraint solvers? What do they use, and how succesful
   are they? </li>
   <li> Active clause-sets should be attractive.
    <ol>
     <li> Incorporating some of the knowledge we have for these problems. </li>
     <li> They should also be able to better detect symmetries. </li>
    </ol>
   </li>
   <li> Compressed representation of clauses:
    <ol>
     <li> If that ZAP systems, which allows to use "annotated clauses", clauses
     plus a permutation group acting on the variables, is open-source, then it
     would be very natural to apply it here:
      <ol>
       <li> The clause-set F_R([q_1, ..., q_s], r, n) can be expressed then
       by just s clauses together with the symmetric group S_n. </li>
       <li> However it is not available. </li>
       <li> One should have a look at those papers. </li>
       <li> A point here is that S_n does act faithful but not
       strongly faithful on the clauses (i.e., on the underlying hypergraph)
       --- can this be repaired or improved (S_n is a rather large group here)?
       </li>
      </ol>
     </li>
    </ol>
   </li>
  </ul>
  
  
  \bug Fix obsolete notations DONE
  <ul>
   <li> See "Systematic notations for the numbers in %Ramsey theory" in
   ComputerAlgebra/RamseyTheory/plans/general.hpp for the standardised
   notations. </li>
   <li> All old "N_R" or whatever need to be updated. </li>
  </ul>

*/

