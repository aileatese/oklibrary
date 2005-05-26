// Oliver Kullmann, 25.5.2005 (Swansea)

#ifndef BASICSTESTOBJECTS_pFgR554e

#define BASICSTESTOBJECTS_pFgR554e

#include "LibraryBasics_Tests.hpp"

#include "Basics.hpp"
#include "Basics_Tests.hpp"

namespace OKlib {

  namespace Concepts {

      OKLIB_BASIC_CONCEPT_TEST_TAG(FullyEqualityComparable);
      OKLIB_BASIC_CONCEPT_TEST_ARCHETYPE(FullyEqualityComparable);

      OKLIB_BASIC_CONCEPT_TEST_TAG(FullyLessThanComparable);
      OKLIB_BASIC_CONCEPT_TEST_ARCHETYPE(FullyLessThanComparable);

      OKLIB_BASIC_CONCEPT_TEST_TAG(LinearOrder);
      OKLIB_BASIC_CONCEPT_TEST_ARCHETYPE(LinearOrder);

      OKLIB_BASIC_CONCEPT_TEST_TAG(FullyConstructible);
      OKLIB_BASIC_CONCEPT_TEST_ARCHETYPE(FullyConstructible);

      OKLIB_BASIC_CONCEPT_TEST_TAG(EqualitySubstitutable);
      OKLIB_BASIC_CONCEPT_TEST_ARCHETYPE(EqualitySubstitutable);

      OKLIB_BASIC_CONCEPT_TEST_TAG(ConstCorrect);
      OKLIB_BASIC_CONCEPT_TEST_ARCHETYPE(ConstCorrect);

  }

}

#endif
