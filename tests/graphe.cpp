#include <boost/test/unit_test.hpp>

#include "graphe.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"

BOOST_AUTO_TEST_SUITE(test_graphe)

    BOOST_AUTO_TEST_CASE(test_segment_tree_sum) {
        std::vector<size_t> array = {1, 2, 1, 8, 7};

        graphe::SegmentTree<size_t> tree(array, std::plus<size_t>{});

        BOOST_CHECK_EQUAL(tree.get(1, 4), 11);
        BOOST_CHECK_EQUAL(tree.get(1, 5), 18);
    }

    BOOST_AUTO_TEST_CASE(test_segment_tree_max) {
        std::vector<size_t> array = {1, 2, 1, 8, 7};

        graphe::SegmentTree<size_t> tree(array, [](size_t a, size_t b) {
            return std::max(a, b);
        });

        BOOST_CHECK_EQUAL(tree.get(0, 3), 2);
        BOOST_CHECK_EQUAL(tree.get(1, 4), 8);
        BOOST_CHECK_EQUAL(tree.get(1, 5), 8);
    }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop
