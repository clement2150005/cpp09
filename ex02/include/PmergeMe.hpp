#pragma once

#include <vector>
#include <deque>
#include <utility>

class PmergeMe
{
private:
    PmergeMe();
    PmergeMe(const PmergeMe &);
    PmergeMe &operator=(const PmergeMe &);
    ~PmergeMe();

public:
    static void sort(std::vector<int> &data);
    static void sort(std::deque<int> &data);
};
