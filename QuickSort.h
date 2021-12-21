#pragma once
#ifndef __QS_H_INCLUDED__
#define __QS_H_INCLUDED__
#include <functional>
#include <algorithm>
#include <iterator>


/*!
\brief Hoare sorting to quickly find a priority goal*/
template< typename BidirectionalIterator, typename Compare >
void quick_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp) {
    if (first != last) {
        BidirectionalIterator left = first;
        BidirectionalIterator right = last;
        BidirectionalIterator pivot = left++;

        while (left != right) {
            if (cmp(*left, *pivot)) {
                ++left;
            }
            else {
                while ((left != --right) && cmp(*pivot, *right))
                    ;
                std::iter_swap(left, right);
            }
        }

        --left;
        std::iter_swap(first, left);

        quick_sort(first, left, cmp);
        quick_sort(right, last, cmp);
    }
}
// для вещественных

int partition(float* a, int p, int r)

{
    float x = *(a + r);
    int i = p - 1;
    int j;
    float tmp;
    for (j = p; j < r; j++)
    {
        if (*(a + j) <= x)
        {
            i++;
            tmp = *(a + i);
            *(a + i) = *(a + j);
            *(a + j) = tmp;
        }
    }
    tmp = *(a + r);
    *(a + r) = *(a + i + 1);
    *(a + i + 1) = tmp;
    return i + 1;
}

void quicksort(float* a, int p, int r)
{
    int q;
    if (p < r)
    {
        q = partition(a, p, r);
        quicksort(a, p, q - 1);
        quicksort(a, q + 1, r);
    }
}
template< typename BidirectionalIterator >
inline void quick_sort(BidirectionalIterator first, BidirectionalIterator last) {
    quick_sort(first, last,
        std::less_equal< typename std::iterator_traits< BidirectionalIterator >::value_type >()
    );
};
#endif