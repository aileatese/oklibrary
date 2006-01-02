// Oliver Kullmann, 26.5.2005

/*!
  \file Variables_Tests.hpp
  \brief Generic tests for models of variable concepts
*/

#ifndef VARIABLESTESTS_kkgFre3

#define VARIABLESTESTS_kkgFre3

#include "TestBaseClass.hpp"
#include "TestExceptions.hpp"

#include "LibraryBasics.hpp"
#include "Basics_Tests.hpp"

#include "TypeTraits.hpp"
#include "index_type.hpp"

#include "Variables.hpp"

namespace OKlib {

  namespace Concepts {

    template <typename Var>
    struct Variables_Axiom_singular_variables_identity : OKlib::TestSystem::Test {
      typedef Variables_Axiom_singular_variables_identity test_type;
      Variables_Axiom_singular_variables_identity(const Var& v, const Var& w) : v(v), w(w) {
        assert(not v);
        assert(not w);
      }
    private :
      const Var& v; const Var& w;
      void perform_test_trivial() {
        if (v != w)
          OKLIB_THROW("v != w");
      }
    };

    template <typename Var>
    struct Variables_Axiom_singular_variables_false : OKlib::TestSystem::Test {
      typedef Variables_Axiom_singular_variables_false test_type;
    private :
      void perform_test_trivial() {
        if (Var())
          OKLIB_THROW("not not bool(Var())");
      }
    };

    template <typename Var>
    struct Variables_basic_test : OKlib::TestSystem::TestBase {
      typedef Variables_basic_test test_type;
      Variables_basic_test() {
        insert(this);
      }
    private :
      void perform_test_trivial() {
        OKLIB_MODELS_CONCEPT_REQUIRES(Var, Variables);
        OKLIB_TESTTRIVIAL_RETHROW(LinearOrder_basic_test_one_object<Var>(Var()));
        OKLIB_TESTTRIVIAL_RETHROW(Variables_Axiom_singular_variables_false<Var>());
      }
    };

    // ---------------------------------------------------------------------------------------------------------------------

    template <typename Var>
    struct VariablesWithIndex_Axiom_index_nonnegative : OKlib::TestSystem::Test {
      typedef VariablesWithIndex_Axiom_index_nonnegative test_type;
      VariablesWithIndex_Axiom_index_nonnegative(const Var& v) : v(v) {}
    private :
      const Var& v;
      typedef typename OKlib::Concepts::index_type<Var>::type index_type;
      void perform_test_trivial() {
        if (index_type(v) < 0)
          OKLIB_THROW("index(v) < 0");
      }
    };
  
    template <typename Var>
    struct VariablesWithIndex_Axiom_index_zero_positive : OKlib::TestSystem::Test {
      typedef VariablesWithIndex_Axiom_index_zero_positive test_type;
      VariablesWithIndex_Axiom_index_zero_positive(const Var& v) : v(v) {
        assert(not v);
      }
    private :
      const Var& v;
      typedef typename OKlib::Concepts::index_type<Var>::type index_type;
      void perform_test_trivial() {
        if (index_type(v) != 0)
          OKLIB_THROW("index(v) != 0");
      }
    };

    template <typename Var>
    struct VariablesWithIndex_Axiom_index_zero_negative : OKlib::TestSystem::Test {
      typedef VariablesWithIndex_Axiom_index_zero_negative test_type;
      VariablesWithIndex_Axiom_index_zero_negative(const Var& v) : v(v) {
        typedef typename OKlib::Concepts::index_type<Var>::type index_type;
        assert(index_type(v) == 0);
      }
    private :
      const Var& v;
      void perform_test_trivial() {
        if (bool(v))
          OKLIB_THROW("not not bool(v)");
      }
    };

    template <typename Var>
    struct VariablesWithIndex_Axiom_index_identity : OKlib::TestSystem::Test {
      typedef VariablesWithIndex_Axiom_index_identity test_type;
      VariablesWithIndex_Axiom_index_identity(const Var& v, const Var& w) : v(v), w(w) {
        typedef typename OKlib::Concepts::index_type<Var>::type index_type;
        assert(index_type(v) == index_type(w));
      }
    private :
      const Var& v; const Var& w;
      void perform_test_trivial() {
        if (v != w)
          OKLIB_THROW("v != w");
      }
    };
    // ToDo: This axiom should go into a refinement (variables with equal indices can be different, for example when used in different contexts).

    template <typename Var>
    struct VariablesWithIndex_basic_test : OKlib::TestSystem::TestBase {
      typedef VariablesWithIndex_basic_test test_type;
      VariablesWithIndex_basic_test() {
        insert(this);
      }
    private :
      void perform_test_trivial() {
        OKLIB_MODELS_CONCEPT_REQUIRES(Var, VariablesWithIndex);
        OKLIB_TESTTRIVIAL_RETHROW(Variables_basic_test<Var>());
        OKLIB_TESTTRIVIAL_RETHROW(VariablesWithIndex_Axiom_index_zero_positive<Var>(Var()));
      }
    };

    // ---------------------------------------------------------------------------------------------------------------------

    /*!
      \class VariablesAsIndex_Axiom
      \brief Checks construction of a variable from an index
    */

    namespace TestIndex {
      template <typename index_type, bool is_signed>
      struct assert_index {
        assert_index(const index_type& i) {}
      };
      template <typename index_type>
      struct assert_index<index_type, true> {
        assert_index(const index_type& i) {
          assert(i >= 0);
        }
      };
      template <typename index_type>
      void assert_ge0(const index_type& i) {
        (assert_index<index_type, OKlib::MetaProgramming::is_signed_integral<index_type>::value>(i));
      }
    }
    
    template <typename Var>
    struct VariablesAsIndex_Axiom : OKlib::TestSystem::Test {
      typedef VariablesAsIndex_Axiom test_type;
      typedef typename OKlib::Concepts::index_type<Var>::type index_type;
      VariablesAsIndex_Axiom(const index_type& i) : i(i) {
        TestIndex::assert_ge0(i);
      }
    private :
      const index_type& i;
      void perform_test_trivial() {
        if (index_type(Var(i)) != i)
          OKLIB_THROW("index(Var(i)) != i");
      }
    };

    template <typename Var>
    struct VariablesAsIndex_basic_test : OKlib::TestSystem::TestBase {
      typedef VariablesAsIndex_basic_test test_type;
      VariablesAsIndex_basic_test() {
        insert(this);
      }
    private :
      typedef typename OKlib::Concepts::index_type<Var>::type index_type;
      void perform_test_trivial() {
        OKLIB_MODELS_CONCEPT_REQUIRES(Var, VariablesAsIndex);
        OKLIB_TESTTRIVIAL_RETHROW(VariablesWithIndex_basic_test<Var>());
        {
          const index_type max_index = 2;
          for (index_type i = 0; i <= max_index; ++i)
            OKLIB_TESTTRIVIAL_RETHROW(VariablesAsIndex_Axiom<Var>(i));
        }
        // ToDo: With the creation power now also testing all other axioms.
      }
    };

  }

}

#endif
