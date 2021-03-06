// Oliver Kullmann, 15.5.2005 (Swansea)
/* Copyright 2005 - 2007, 2009, 2010 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file OKlib/Combinatorics/Hypergraphs/Generators/VanderWaerden.hpp
  \brief %Tools for generating van der Waerden hypergraphs
*/

#ifndef VANDERWAERDENHYPERGRAPH_77bQMQM_5993KKl
#define VANDERWAERDENHYPERGRAPH_77bQMQM_5993KKl

#include <iterator>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <functional>
#include <list>

#include <OKlib/Concepts/Iterators.hpp>
#include <OKlib/Programming/Utilities/OrderRelations/OrderConstructions.hpp>
#include <OKlib/Structures/Sets/SetAlgorithms/Subsumption.hpp>

namespace OKlib {
 namespace Combinatorics {
  namespace Hypergraphs {
   namespace Generators {
  
     /*!
       \class Iterator_arithmetic_progression
       \brief Iterator to iterate through the elements of an arithmetical progression.
       \todo Make a const random iterator out of it.
     */
  
     template <typename Integer>
     class Iterator_arithmetic_progression : public std::iterator<std::input_iterator_tag, Integer> {
       Integer current_value;
      Integer slope;
    public :
      typedef ::OKlib::Concepts::MultiPassInputIterator_tag concept_tag;
      Iterator_arithmetic_progression(const Integer start_value, const Integer slope) : current_value(start_value), slope(slope) {}
      Integer operator* () const { return current_value; }
      Iterator_arithmetic_progression& operator ++() {
        current_value += slope;
        return *this;
      }
      Iterator_arithmetic_progression operator ++(int) {
        Iterator_arithmetic_progression i(*this);
        operator ++();
        return i;
      }
    };
    
    template <typename Integer>
    inline bool operator ==(const Iterator_arithmetic_progression<Integer>& lhs, const Iterator_arithmetic_progression<Integer>& rhs) {
      return *lhs == *rhs;
    }
    template <typename Integer>
    inline bool operator !=(const Iterator_arithmetic_progression<Integer>& lhs, const Iterator_arithmetic_progression<Integer>& rhs) {
      return not (lhs == rhs);
    }
    
    // -----------------------------------------------------------
    
    /*!
      \class Arithmetic_progression
      \brief An arithmetic progression as a container
  
      \todo Add the concept tag (a special case of a "const collection with begin, end and size; not default-constructible, but copyable, assignable, equality comparable").
  
      \todo See class IteratorHandling::Arithmetical_progression in
     General/IteratorHandling.hpp
  
    */
    
    template <typename Integer>
    class Arithmetic_progression {
      Integer start_, length, slope_;
      Integer finish;
    public :
      Arithmetic_progression(const Integer start, const Integer length, const Integer slope) : start_(start), length(length), slope_(slope), finish(start_ + length * slope_) {
        assert(length >= 0);
      }
      typedef Integer value_type;
      typedef Integer size_type;
      size_type size() const { return length; }
      typedef Iterator_arithmetic_progression<Integer> iterator;
      typedef iterator const_iterator;
      iterator begin() const { return iterator(start_, slope_); }
      iterator end() const { return iterator(finish, 0); }
        friend bool operator ==(const Arithmetic_progression& lhs, const Arithmetic_progression& rhs) {
        return lhs.start == rhs.start and lhs.length == rhs.length and lhs.slope == rhs.slope;
      }
      value_type start() const { return start_; }
      value_type slope() const { return slope_; }
    };
    
    // -----------------------------------------------------------
  
    /*!
      \class Arithprog_finish
      \brief Functor which produces the list of arithmetic progressions of
      length k in {1, ..., n} finishing in n.

      Specified by function arithprog_finish(k,n) in
      ComputerAlgebra/Hypergraphs/Lisp/Generators/VanderWaerden.mac.

      Usage:
      <ul>
       <li> Produce an object "Arithprog_finish ap(k);" or
       "Arithprog_finish ap;". </li>
       <li> The length k of the arithmetic progressions can be re-set by
       ap.set(k) (k >= 1); this is necessary in case of default-construction.
       </li>
       <li> ap(n) returns the set-system of arithmetic progressions of length
       (the current) k in {1, ..., n} (for n >= 1). </li>
       <li> The requirements on template-parameter SetSystem are
        <ol>
         <li> copyable; </li>
         <li> construction SetSystem(begin,end) through a sequence given by
         two iterators, where the value-type of the iterators is Hyperedges.
         </li>
        </ol>
       </li>
       <li> The requirements on template-parameter Hyperedges are
        <ol>
         <li> copyable; </li>
         <li> construction Hyperedges(begin,end) through a sequence given by
         two iterators, where the value-type of the iterators is Int.
         </li>
        </ol>
       </li>
      </ul>
    */
  
    template <class Hyperedges, class SetSystem, typename Int = unsigned int>
    struct Arithprog_finish {
  
      typedef Int int_type;
      typedef Arithmetic_progression<int_type> progression_type;
      typedef Hyperedges hyperedge_type;
      typedef SetSystem set_system_type;
      typedef typename hyperedge_type::value_type vertex_type;
  
      int_type k; // length of arithmetic progression
  
      Arithprog_finish() : k(0) {}
      Arithprog_finish(const int_type k) : k(k) {
        assert(k >= 1);
      }
      void set(const int_type k_new) {
        assert(k_new >= 1);
        k = k_new;
      }
  
      set_system_type operator()(const int_type n) const {
        assert(k >= 1);
        assert(n >= 1);
        typedef std::vector<vertex_type> vector_t;
        vector_t H;
        H.reserve(k);
        typedef std::vector<hyperedge_type> vector2_t;
        vector2_t S;
        if (k == 1) {
          H.push_back(n);
          S.push_back(hyperedge_type(H.begin(), H.end()));
          return set_system_type(S.begin(),S.end());
        }
        typedef long int lib_int_type;
        const int_type q = std::ldiv(lib_int_type(n-1), lib_int_type(k-1)).quot;
        S.reserve(q);
        for (int_type d = 1; d <= q; ++d) {
          const progression_type P(n - (k-1) * d, k, d);
          H.assign(P.begin(), P.end());
          assert(P.size() == k);
          S.push_back(hyperedge_type(H.begin(), H.end()));
        }
        assert(S.size() == q);
        return set_system_type(S.begin(),S.end());
      }
    };
  
    // -----------------------------------------------------------

   /*!
     \brief Computing the number of arithmetic progressions of length k in
     {1,...,n}

     The Maxima-specification is nhyp_arithprog_ohg(k,n) in
     ComputerAlgebra/Hypergraphs/Lisp/Generators/VanderWaerden.mac.
   */
   template <typename UInt>
   inline UInt nhyp_arithprog_hg(const UInt k, const UInt n) {
     if (k == 0) return 1;
     if (k == 1) return n;
     if (n < k) return 0;
     const UInt q = (n-1) / (k-1);
     return q*n - (q*(k - 1)*(q + 1)) / 2;
   }

    /*!
      \class Arithmetical_progressions
      \brief All arithmetical progressions in {1,...,n}, in lexicographical order (in iterator-fashion, without storage)
      \deprecated Old, "quick and dirty" implementation, to be improved (via using a standard output interface).

      \detail

      Usage:
      <ul>
       <li> Construct an object
       <code>Arithmetical_progressions ap(k,n)</code>, where k is the length
       of the arithmetic progressions, to be considered in {1,...,n}. </li>
       <li> In ap.count the total number of ap's is to be found. </li>
       <li> Via calling ap.next() one then obtains the ap's, as vectors, in
       lexicographical order. </li>
       <li> It is an error if ap.next() is called more than ap.count many
       times. </li>
      </ul>

      \todo Integration
      <ul>
       <li> See IteratorHandling::Arithmetical_progression in
       General/IteratorHandling.hpp. </li>
      </ul>
    */

    template <typename Int>
    class Arithmetical_progressions {
    public :
      typedef Int Index;
      const Index n;
      //! size of arithmetic progression in {1, ..., n}
      const Index k;
      //! number of arithmetic progressions of length k in {1, ..., n}
      const Index count;

    private :
      //! first element in current arithmetic progression
      Index current_element;
      //! slope of current arithmetic progression
      Index current_distance;

    public :

      Arithmetical_progressions(const Index k, const Index n) :
          n(n), k(k),
          count(nhyp_arithprog_hg(k,n)),
          current_element(1),
          current_distance(1) {
        assert(k >= 1);
        assert(n >= 2);
        assert(n >= k);
      }
      std::string static message() {
        return "Iterating through the arithmetic progressions in lexicographical order.";
      }

      typedef std::vector<Index> Arithmetical_progression;

      Arithmetical_progression next() {
        Arithmetical_progression ap;
        ap.reserve(k);
        for (Index i = 0; i < k; ++i)
	  ap.push_back(current_element + i * current_distance);
        if (current_element + (k-1) * (current_distance + 1) <= n and k >= 2)
	  ++current_distance;
        else {
	  ++current_element; current_distance = 1;
        }
        return ap;
      }
    };


    /*!
      \class Arithmetical_progressions_colex
      \brief All arithmetical progressions in {1,...,n}, in colexicographical order (in iterator-fashion, without storage)
      \deprecated To be improved (via using a standard output interface).

      \detail

      Usage:
      <ul>
       <li> Construct an object
       <code>Arithmetical_progressions_colex ap(k,n)</code>, where k is the
       length of the arithmetic progressions, to be considered in {1,...,n}.
       </li>
       <li> In ap.count the total number of ap's is to be found. </li>
       <li> Via calling ap.next() one then obtains the ap's, as vectors, in
       colexicographical order. </li>
       <li> ap.next() can be called arbitrarily often, and runs through all
       arithmetic progressions of length k in {1,...}. </li>
      </ul>

      \todo Integration
      <ul>
       <li> See classes in
       Combinatorics/Hypergraphs/Generators/plans/VanderWaerden.hpp and
       General/IteratorHandling.hpp. </li>
      </ul>
    */

    template <typename Int>
    class Arithmetical_progressions_colex {
    public :
      typedef Int Index;
      const Index n;
      //! size of arithmetic progression in {1, ..., n}
      const Index k;
      //! number of arithmetic progressions of length k in {1, ..., n}
      const Index count;

    private :
      //! last element in current arithmetic progression
      Index current_element;
      //! slope of current arithmetic progression
      Index current_distance;

    public :

      Arithmetical_progressions_colex(const Index k, const Index n) :
          n(n), k(k),
          count(nhyp_arithprog_hg(k,n)),
          current_element(k),
          current_distance(1) {
        assert(k >= 2);
        assert(n >= 2);
        assert(n >= k);
      }
      std::string static message() {
        return "Iterating through the arithmetic progressions in colexicographical order.";
      }

      typedef std::vector<Index> Arithmetical_progression;

      Arithmetical_progression next() {
        Arithmetical_progression ap;
        ap.reserve(k);
        const Index first_element = current_element - (k-1) * current_distance;
        for (Index i = 0; i < k; ++i)
	  ap.push_back(first_element + i * current_distance);
        if (current_distance > 1) --current_distance;
        else
          current_distance = current_element++ / (k-1);
        return ap;
      }
    };

    // -----------------------------------------------------------

    /*!
      \class Pd_arithmetical_progressions
      \brief All palindromised arithmetical progressions in {1,...,n} (in iterator-fashion, without storage)
      \deprecated Old, "quick and dirty" implementation, to be improved (via using a standard output interface).

      \detail

      Usage:
      <ul>
       <li> Construct an object
       <code>Pd_arithmetical_progressions ap(k,n)</code>, where k is the length
       of the arithmetic progressions, to be considered in {1,...,n}. </li>
       <li> In ap.count the total number of ap's is to be found. </li>
       <li> Via calling ap.next() one then obtains the ap's, as vectors, in
       lexicographical order. </li>
       <li> It is an error if ap.next() is called more than ap.count many
       times. </li>
       <li> "Palindromised" means that elements v > (n+1)/2 are mapped to their
       "mirror image" n-v+1. </li>
       <li> The order is lexicographical order, however regarding the order on
       the original arithmetic progressions, before transformation. </li>
       <li> Arithmetic progressions where all elements would be mapped are
       ignored (since they have been already obtained). </li>
       <li> Nevertheless, in general the sequence of vectors contains
       duplicates (and subsumed elements). </li>
       <li> All palindromised progressions are ascendingly sorted and without
       duplicates. </li>
       <li> For example for k=3, n=6 from
         (1,2,3),(1,3,5),(2,3,4),(2,4,6),(3,4,5),(4,5,6)
       we obtain
         (1,2,3),(1,2,3),(2,3),  (1,2,3),(2,3).
       </li>
      </ul>

      \todo Integration
      <ul>
       <li> Compare Arithmetical_progressions above. </li>
      </ul>
    */

    template <typename Int>
    class Pd_arithmetical_progressions {
    public :
      typedef Int Index;
      const Index n;
      //! size of arithmetic progression in {1, ..., n}
      const Index k;
      //! midpoint of {1, ..., n}
      const Index mp;

    private :
      typedef Arithmetical_progressions<Index> AP;
      //! object for ordinary arithmetic progressions
      AP ap_;

    public :
      //! number of palindromised arithmetic progressions of length k in {1, ..., n}
      const Index count;

    public :

      Pd_arithmetical_progressions(const Index k, const Index n) :
          n(n), k(k), mp((n+1)/2),
          ap_(k,n),
          count(ap_.count - nhyp_arithprog_hg(k,n-mp)) {
        assert(k >= 1);
        assert(n >= 2);
        assert(n >= k);
      }
      static std::string message() {
        return "Iterating through the palindromised arithmetic progressions in lexicographical order.";
      }

      Index mirror_image(const Index v) {
        assert(1 <= v);
        assert(v <= n);
        return n-v+1;
      }
      typedef typename AP::Arithmetical_progression sequence_type;
      sequence_type next() {
        sequence_type ap(ap_.next());
        {typedef typename sequence_type::iterator iterator;
         const iterator begin(ap.begin()), end(ap.end());
         for (iterator i = begin; i != end; ++i)
           if (*i > mp) *i = mirror_image(*i);
         std::sort(begin, end);
         ap.resize(std::unique(begin, end) - begin);
        }
        return ap;
      }

    };

    /*!
      \class Pd_arithprog_ohg
      \brief Functor for creating palindromic vdW-hypergraphs

      Pd_arithprog_ohg()(k,n) computes the colexicographically sorted
      hypergraph of palindromised arithmetic progressions of size k over
      n vertices, as vector of vectors.

      The Maxima-specification is palindromise_vdw_ohg(arithprog_ohg(k,n)) in
      ComputerAlgebra/Hypergraphs/Lisp/Generators/VanderWaerden.mac.

      \todo Update concepts
      \todo Write tests
      \todo Improve implementation
    */

    template <typename Int = unsigned int>
    class Pd_arithprog_ohg {
    public :
      typedef Int vertex_type;
    private :
      typedef Pd_arithmetical_progressions<vertex_type> Pd_ap;
    public :
      typedef typename Pd_ap::sequence_type hyperedge_type;
      typedef std::vector<hyperedge_type> set_system_type;
      typedef typename set_system_type::size_type size_type;

      set_system_type operator()(const vertex_type k, const vertex_type n) const {
        Pd_ap ap(k,n);
        set_system_type g;
        g.reserve(ap.count);
        for (vertex_type i = 0; i < ap.count; ++i) g.push_back(ap.next());
        std::sort(g.begin(),g.end(),OKlib::Programming::Utilities::OrderRelations::SizeLessThan<std::less<hyperedge_type> >());
        g.resize(std::unique(g.begin(),g.end()) - g.begin());
        {
         typedef std::list<hyperedge_type> list_type;
         list_type gl(g.begin(),g.end());
         OKlib::SetAlgorithms::Subsumption_elimination<list_type, OKlib::SetAlgorithms::SubsumptionsTags::hyperedges_are_unique, OKlib::SetAlgorithms::SubsumptionsTags::hyperedges_sorted_by_size>()(gl);
         g.assign(gl.begin(),gl.end());
        }
        std::sort(g.begin(),g.end(),OKlib::Programming::Utilities::OrderRelations::Colexicographical_comparison<hyperedge_type>());
        return g;
      }
    
    };
    
   }
  }
 }
}

#endif
