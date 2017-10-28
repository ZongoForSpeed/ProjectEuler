#pragma once

#include "gtest/gtest.h"

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

template<typename LeftIter, typename RightIter>
::testing::AssertionResult CheckEqualCollections(LeftIter left_begin,
                                                 LeftIter left_end,
                                                 RightIter right_begin) {
    bool equal(true);
    std::string message;
    std::size_t index(0);
    while (left_begin != left_end) {
        if (*left_begin++ != *right_begin++) {
            equal = false;
            message += "\n\tMismatch at index " + std::to_string(index);
        }
        ++index;
    }
    if (message.size())
        message += "\n\t";
    return equal ? ::testing::AssertionSuccess() :
           ::testing::AssertionFailure() << message;
}

#define EXPECT_EQ_COLLECTIONS(left_begin, left_end, right_begin, right_end) \
    EXPECT_TRUE(CheckEqualCollections(left_begin, left_end, right_begin));
