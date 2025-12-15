#pragma once

#include <vector>
#include <deque>
#include <utility>

struct Pending
{
	int value;
	int max;
};

class PmergeMe
{
private:
    PmergeMe();
    PmergeMe(const PmergeMe &);
    PmergeMe &operator=(const PmergeMe &);
    ~PmergeMe();

    static size_t jacobsthal(size_t n);

    template <typename Iterator, typename T>
    static Iterator binarySearch(Iterator begin, Iterator end, const T &value)
    {
        Iterator left = begin;
        Iterator right = end;
        while (left < right)
        {
            Iterator mid = left + (right - left) / 2;
            if (*mid <= value)
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }

public:
    static void sort(std::vector<int> &data);
    static void sort(std::deque<int> &data);
};
