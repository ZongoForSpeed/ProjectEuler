#pragma once

#include <boost/test/unit_test.hpp>

//template<typename T, typename V, size_t size>
//::testing::AssertionResult ArraysMatch(const T (&expected)[size],
//                                       const V (&actual)[size]) {
//    for (size_t i(0); i < size; ++i) {
//        if (expected[i] != actual[i]) {
//            return ::testing::AssertionFailure() << "array[" << i
//                                                 << "] (" << actual[i] << ") != expected[" << i
//                                                 << "] (" << expected[i] << ")";
//        }
//    }
//
//    return ::testing::AssertionSuccess();
//}
