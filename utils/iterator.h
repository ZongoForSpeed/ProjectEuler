#pragma once

#include <iterator>

namespace iterator {

    template<class Iterator>
    constexpr Iterator next(Iterator it, size_t n) {
        advance(it, static_cast<typename std::iterator_traits<Iterator>::difference_type>(n));
        return it;
    }

    template<typename InputIterator>
    size_t distance(InputIterator first, InputIterator last, std::input_iterator_tag) {
        //__glibcxx_function_requires(_InputIteratorConcept < InputIterator > )
        size_t result = 0;
        while (first != last) {
            ++first;
            ++result;
        }

        return result;
    }

    template<typename RandomAccessIterator>
    size_t distance(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag) {
        //__glibcxx_function_requires(_RandomAccessIteratorConcept < RandomAccessIterator > )
        return static_cast<size_t>(std::abs(last - first));
    }

    template<typename InputIterator>
    size_t distance(InputIterator first, InputIterator last) {
        return distance(first, last, typename std::iterator_traits<InputIterator>::iterator_category());
    }

    template<class InputIt1, class InputIt2, class BinaryOperation>
    constexpr void for_each2(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryOperation binary_op) {
        while (first1 != last1) {
            binary_op(*first1++, *first2++);
        }
    }

}
