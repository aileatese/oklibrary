// Matthew Gwynne, 16.7.2009 (Swansea)
/* Copyright 2009, 2010 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ComputerAlgebra/Satisfiability/Lisp/PseudoBoolean/plans/CardinalityConstraints.hpp
  \brief Plans for translations of cardinality constraints into CNF


  \todo Connections
  <ul>
   <li> See "Cardinality constraints" in
   ComputerAlgebra/Satisfiability/Lisp/FiniteFunctions/plans/Thresholds.hpp
   for the boolean-function point-of-view. </li>
   <li> And see "Translations to SAT" in
   ComputerAlgebra/Hypergraphs/Lisp/Transversals/Bounded/plans/general.hpp
   for the important application of finding hypergraph transversals of
   bounded size. </li>
  </ul>


  \todo Representing "cardinality constraints"
  <ul>
   <li> DONE (fixed now the notion of a "cardinality constraint")
   We need some direct representation of a condition that the (integer)
   sum of some given boolean variables is =,>,>=,<,<= some bound B. </li>
   <li> We need also some general scheme for such special
   constraint-representations. </li>
   <li> See "The notion of a pseudo-boolean constraint" in
   ComputerAlgebra/Satisfiability/Lisp/PseudoBoolean/plans/general.hpp. </li>
   <li> Let's use "crd" for "cardinality constraint", "crdl" for lists of
   cardinality constraints, "crds" for sets, and "fcrdl" resp. "fcrds" for
   "formal" lists resp. sets of cardinality constraints. </li>
   <li> DONE
   A "cardinality constraint" is a triple [a,L,b], where L is a
   list of literals, while a,b are natural numbers or 0 or inf. </li>
   <li> The meaning is that for the number s of satisfied literals in L
   we have a <= s <= b. </li>
   <li> DONE (for cardinality constraints the translations into sums is not
   of real relevance)
   It would be good if for the relation we would not just use some string,
   but the actually Maxima-presentation of the corresponding Maxima-operator:
    <ol>
     <li> Now how to refer to the Maxima-operator "<" ? Apparently this is done
     by using strings. Now how from a string to get back the operator?
     Apparently by for example subst("<=",r,r(3,4)), which yields 3 <= 4. </li>
     <li> For example
     \verbatim
C : ["cardinality", "<", {v1,-v2,v3}, 6];
Cs : subst(C[2], r, r(sum_l(listify(C[3])), C[4]));
  v3-v2+v1 < 6
Csa : at(Cs, [v1=1, v2=0, v3=1]);
  2 < 6
is(Csa);
  true
     \endverbatim
     </li>
     <li> DONE
     The literals here however are boolean literals, so substitution
     of values 0,1 seems inappropriate? On the one hand, boolean variables
     are supposed to be "positive functions", and also we have variables like
     "1". </li>
     <li> DONE (the sum-representation is not really appropriate here)
     Perhaps we make the distinction that if a cardinality constraint
     occurs in a mixed problem, then the interpretation of the other part
     (boolean or non-boolean CNF or DNF) is determinative, while free-standing
     cardinality constraints are interpreted in the ordinary arithmetic sense
     as above, based on further specifications of the domains of the variables
     involved. </li>
     <li> DONE (again, not really appropriate here)
     So in the context of a boolean clause-set one can use cardinality
     constraints like ["cardinality", "=", {1,2,3}, 2], which is equivalent
     to the CNF {{1,2},{1,3},{2,3},{-1,-2,-3}} (while
     ["cardinality", "=", {1,-2,3}, 2] is equivalent to the CNF
     {{1,-2},{1,3},{-2,3},{-1,2,-3}}). </li>
     <li> However, as argued below, the cardinality constraint is only
     concerned about *literals* which are set to true, and so implicitly
     in this context always literals set to false are regarded as zero. </li>
     <li> So it seems that the above Maxima-sum (like "v3-v2+v1") is not
     really appropriate here --- first the literals have to be evaluated,
     and then "true" is interpreted as 1, while "false" is interpreted as 0.
     </li>
    </ol>
   </li>
   <li> What are non-boolean cardinality constraints?
    <ol>
     <li> It seems the appropriate generalisation would be to ask that amongst
     the given set of literals at least, exactly, at most etc. of
     the literals are satisfied by the assignment. </li>
     <li> So one sees that it is not sensible to add up *variables*, but
     literals are to be considered, which are (relative to some (total)
     assignment) either true or false, and one considers then only the
     literals which are true, and makes a requirement on their count. </li>
    </ol>
   </li>
   <li> DONE (the distinction doesn't seem to be of importance)
    Lists or sets:
    <ol>
     <li> With a list we generalise cardinality constraints in the direction
     of pseudo-boolean constraints. </li>
     <li> Perhaps it makes sense to have set-cardinality-constraints, and
     list-cardinality-constraints (as a generalisation). </li>
    </ol>
   </li>
   <li> DONE (no type identifiers)
   Perhaps just "card" instead of "cardinality" is enough as the first
   element of the list.
    <ol>
     <li> Actually, yet we do not use such type-identifiers,
     but it is the context which determines the nature of the objects? </li>
     <li> So we should just drop the "card"-string as part of a cardinality
     constraint? </li>
     <li> A point in favour of having this identify would be if such
     cardinality constraints would be instances of more general invocations
     of "constraints", all just thrown together in one constraint-container.
     </li>
     <li> However, here we should consider cardinality-constraints just as
     generalisations of clauses, and so we should just employ triples like
      ["=", {1,2,3}, 2]. </li>
    </ol>
   </li>
   <li> DONE
   How to call these constraints?
    <ol>
     <li> "crd" for "cardinality constraint"? </li>
     <li> And then further specialised regarding boolean or non-boolean
     variables, and CNF- or DNF-interpretation of variables? </li>
     <li> Perhaps we aim at a symbolism where "crd" can just replace
     "clause", while otherwise everything else is reused?! </li>
    </ol>
   </li>
   <li> Mixed problems:
    <ol>
     <li> It seems mixed problem instances should be lists of problem
     instances. </li>
     <li> Using "cs-crd" for a pair of (boolean) clause-set and (necessarily
     boolean) cardinality constraint. </li>
     <li> For such lists we should have the same type of literals for all
     components. </li>
    </ol>
   </li>
  </ul>


  \todo Direct realisations
  <ul>
   <li> For all types of clause-sets (boolean and non-boolean, CNF and DNF)
   and all types of (in)equalities provide the direct (combinatorial)
   realisations. </li>
   <li> The CNF-representation for boolean literals is given now by
   direct_crd2cl.
    <ol>
     <li> We should also provide statistic-functions (which, of course,
     compute the statistics directly). </li>
     <li> We need to prove the assertions regarding prime-implicates
     (that is, direct_crd2cl_lt and direct_crd2cl_ge compute repetition-free
     lists of (exactly the) prime implicates; see below). </li>
    </ol>
   </li>
   <li> Let L be a set of boolean literals (of size m).
    <ol>
     <li> sum(L) < B has the CNF-realisation consisting of all B-subsets
     of L, which are (then) complemented. </li>
     <li> Example L = {1,-2,3} and B=2: {{-1,2},{-1,-3},{2,-3}} </li>
     <li> The number of clauses is thus binomial(m,B). </li>
     <li> sum(L) <= B is equivalent to sum(L) < B+1. </li>
     <li> sum(L) >= B has the DNF-realisation consisting of all B-subsets
     of L. </li>
     <li> Example L = {1,-2,3} and B=2: {{1,-2},{1,3},{-2,3}} </li>
     <li> So the number of clauses is binomial(m,B). </li>
     <li> sum(L) > B is equivalent to sum(L) >= B+1. </li>
     <li> sum(L) >= B is equivalent to sum(-L) <= m-B. </li>
     <li> sum(L) <= B is equivalent to sum(-L) >= m-B. </li>
     <li> sum(L) = B is equivalent to sum(L) <= B and sum(L) >= B. </li>
     <li> So the CNF-representation of sum(L) = B is the union of the
     CNF-representations of sum(L) < B+1 and sum(-L) < m-B+1. </li>
     <li> That is, we have all (B+1)-subsets of L, complemented, and
     all (m-B+1)-subsets of L. </li>
     <li> The number of clauses is thus binomial(m,B+1) + binomial(m,m-B+1) =
     binomial(m,B+1) + binomial(m,B-1). </li>
     <li> Example L = {1,-2,3} and B=2: {{-1,2,-3},{1,-2},{1,3},{-2,3}}. </li>
     <li> And the DNF-representation of sum(L) = B is the product of the
     DNF-representations of sum(L) >= B and sum(-L) >= m-B. </li>
     <li> That is, we have of B-subsets of L and all (m-B)-subsets of
     -L. </li>
     <li> Example L = {1,-2,3} and B=2:
     {{1,-2},{1,3},{-2,3}} x {{-1},{2},{-3}} = {{1,-2,-3},{1,2,3},{-1,-2,3}}.
     </li>
     <li> One sees that the DNF-representation just lists all total satisfying
     assignments (no resolution is possible between them). </li>
     <li> The number of clauses is thus binomial(m,B). </li>
    </ol>
   </li>
   <li> These clause-sets coincide with the sets of all prime implicates resp.
   prime implicants:
    <ol>
     <li> Only for the "="-forms resolutions are possible. </li>
     <li> For the CNF-representations all clashing clauses overlap
     in at least two literals, and thus all resolutions are blocked. </li>
     <li> And above we already realised that no resolution is possible
     regarding the DNF-realisations. </li>
    </ol>
    So without using additional variables these representations are optimal.
   </li>
   <li> And also using the DNF-representations seems always nearly to use
   the same number of clauses, so that translations DNF -> CNF seem fruitless.
   </li>
  </ul>


  \todo Simplifications
  <ul>
   <li> For crd2scrd we have the following problems:
    <ol>
     <li> Is sort stable?? </li>
     <li> Is ">" to be used instead of ">="?? </li>
    </ol>
    This problems are of general relevance. </li>
  </ul>


  \todo Application of partial assignments
  <ul>
   <li> As a special case of "Application of partial assignments" in
   ComputerAlgebra/Satisfiability/Lisp/PseudoBoolean/plans/general.hpp,
   the result of phi*[a,L,b] = [a',L',b'] is obtained by removing the
   variables of phi from L, and subtracting the number of satisfied literals
   in L from a and b. </li>
  </ul>


  \todo Change specification of variables in cardinality_cl etc.
  <ul>
   <li> Currently the variables in cardinality_totalizer_cl, 
   cardinality_totalizer_cl etc are of the form "ctt(l,i)" where
   l is a list specifying where in the recursive procedure these variables
   are introduced. </li>
   <li> This representation relies heavily on the algorithm, and means
   that it is essentially impossible to properly define or describe the
   variables separately from the algorithm. </li>
   <li> However, these variables are simply the unary representation of
   the cardinality of a certain sublist L' of the list of input literals L, and
   therefore a better representation would be "ctt(a,b,i)" where a and b 
   define the upper and lower bound of the L' in L. </li>
   <li> Then for example, the initial variables list passed into
   cardinality_totalizer_cl as S, would be 
   [ctt(1,length(E),1),...,ctt(1,length(E),length(E))] and then within 
   cardinality_totalizer_cl, the two new lists of variables produced would be
   [ctt(1,length(E_1).1),...,ctt(1,length(E_1),length(E_1))] 
   and 
   [ctt(length(E_1)+1,length(E),1)...,ctt(length(E_1)+1,length(E),length(E_2))]. 
   </li>
  </ul>


  \todo Functions such as cardinality_totalizer_cl should take cardinality
  constraints
  <ul>
   <li> Currently functions such as cardinality_totalizer_cl and
   cardinality_comparator_cl take the parameters given in the
   boolean constraint [a,L,b] individually. </li>
   <li> These functions should take the whole constraint as a single argument
   as in other functions such as crd2cl. </li>
  </ul>


  \todo Partial assignments for CNFs with detection of forced assignments via
  UCP
  <ul> 
   <li>
   The basic definitions and algorithms for CNF representations of
   boolean cardinality constraints with detection of forced assignments
   via UCP are provided in CardinalityConstraints.mac. </li>
   <li> However, one must also explicitly define the satisfying and falsifying
   partial assignments, even if these assignments are implicitly defined
   through the description of the algorithm. Such definitions would be obvious 
   if no new variables were introduced by the translation as the satisfying
   and falsifying partial assignments would follow from the fact that it is
   a representation of a boolean cardinality constraint, however 
   cardinality_cl does introduce new variables. </li>
  </ul>


  \todo Ordering for CNFs with detection of forced assignments via UCP
  <ul>
   <li> The functions, cardinality_cl etc return clause-lists which
   introduce an ordering on the clauses they return, however
   this ordering is not currently specified (explicitly) in the 
   specification of the algorithm or the function. </li>
   <li> The clauses are introduced in a recursive manner in
   cardinality_totalizer_cl, with 2 recursive calls within each call to
   the function (resulting in a binary recursion tree), and so there are
   several ways in which we can order the clauses introduced. </li>
   <li> What is a good order here? </li>
  </ul>


  \todo Representations with detection of forced assignments via r_k reduction
  <ul>
   <li> An algorithm is given in 
   [Efficient CNF Encoding of Boolean Cardinality Constraints] which
   generates a CNF representation of a boolean cardinality constraint
   with detection of forced assignments via UCP. </li>
   <li> The question is, can we generalise this so that there are smaller
   CNF representations with new variables that detect forced assignments 
   using r_k reductions for arbitrary k. </li>
   <li> This would be useful as some solvers such as OKsolver and
   march_pl use r_2 reductions (although march_pl only to some degree) and if 
   the number of literals considered in the constraint is large then the CNF 
   representation with detection via UCP can become rather large as well, and 
   so a smaller representation allowing for slightly more powerful reductions 
   might prove useful. </li>
  </ul>


  \todo Cardinality constraints as active clauses
  <ul>
   <li> As a special case of "Pseudo-boolean constraints as active clauses"
   (see ComputerAlgebra/Satisfiability/Lisp/PseudoBoolean/plans/general.hpp),
   cardinality constraints should yield a very attractive first model of
   "active clauses". </li>
   <li> Their interface as a set of clauses is given by their prime implicates
   representation (see "Direct realisations" below). </li>
  </ul>


  \todo Rename functions related to unary encoding
  <ul>
   <li> These functions realise only special implementations, and so a generic
   name like "cardinality_cl" is inappropriate. </li>
   <li> We should also use English spelling, for example "totaliser". </li>
  </ul>


  \todo Add statistics functions
  <ul>
   <li> These statistics functions rely on precise (combinatorial)
   specifications. </li>
  </ul>
   

  \todo Docus
  <ul>
   <li> The current amount of text one finds in
   ComputerAlgebra/Satisfiability/Lisp/PseudoBoolean/CardinalityConstraints.mac
   is inappropriate --- function specifications should be rather short and
   succinct. </li>
   <li> If appropriate, these texts should be moved to the docus. </li>
  </ul>


  \todo Implement adder-circuit translation
  <ul>
   <li> Also provide the translation using the Tseitin translation of
   the boolean adder circuits. </li>
   <li> See Satisfiability/Transformers/Generators/plans/LinInequal.hpp for 
   a C++ implementation. </li>
   <li> Joost Warners dissertation also describes such a translation; are
   there differences? </li>
  </ul>


  \todo Implement other methods using unary representation
  <ul>
   <li> [Een, Soerensson, 2006, Translating Pseudo-Boolean Constraints into
   SAT] contains another translation. </li>
   <li> And so does [Sinz, 2005, Towards an Optimal Encoding of Boolean
   Cardinality Constraints]. </li>
  </ul>


  \todo DONE Provide complete specifications (related to unary encoding)
  <ul>
   <li> This relates to the algorithm implemented by MG according to
   [Bailleux, Boufkhad, 2003]. </li>
   <li> For cardinality_totalizer_cs, cardinality_comparator_cs and
   cardinality_cl *combinatorial* specifications are needed.
    <ol>
     <li> Currently there are no specifications (which, of course, must
     allow to reconstruct the clause-sets(!)). </li>
     <li> Some properties are mentioned in
     ComputerAlgebra/Satisfiability/Lisp/PseudoBoolean/CardinalityConstraints.mac,
     but these properties shouldn't be there (but possibly in the docus). </li>
    </ol>
   </li>
   <li> Then two levels of tests are needed: One which checks the
   (precise) combinatorial specification, and another one which checks
   the (general) specification as a presentation of some constraint.
    <ol>
     <li> Currently the tests are not specified at all. </li>
     <li> Of course, first the basic functions need to be specified. </li>
    </ol>
   </li>
   <li> This todo has been replaced by
    <ul>
     <li> "Partial assignments for CNFs with detection of forced assignments 
     via UCP" </li>
     <li> "Ordering for CNFs with detection of forced assignments via UCP" 
     </li>
    </ul>
   </li>
   <li> DONE Especially precise information on the added auxiliary variables are
   needed. </li>
  </ul>


  \bug DONE Nonsensical documentation
  <ul>
   <li> In
   ComputerAlgebra/Satisfiability/Lisp/PseudoBoolean/CardinalityConstraints.mac
   two large blocks of text are (exactly??) identical. </li>
   <li> This makes no sense. </li>
   <li> OK started to update the documentation, and the requests posed by OK
   should be answered as soon as possible (both in
   ComputerAlgebra/Satisfiability/Lisp/PseudoBoolean/CardinalityConstraints.mac
   and in
   ComputerAlgebra/Satisfiability/Lisp/PseudoBoolean/tests/CardinalityConstraints.mac
   . </li>
   <li> Also all the bad repetitions need to be removed. </li>
   <li> See 
    <ul>
     <li> "Partial assignments for CNFs with detection of forced assignments 
     via UCP" </li>
     <li> "Ordering for CNFs with detection of forced assignments via UCP" 
     </li>
    </ul>
   </li>
  </ul>


*/

