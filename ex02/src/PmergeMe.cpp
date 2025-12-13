#include "PmergeMe.hpp"
#include <algorithm>
#include <deque>
#include <vector>

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &) {}
PmergeMe &PmergeMe::operator=(const PmergeMe &) { return *this; }
PmergeMe::~PmergeMe() {}

void PmergeMe::sort(std::vector<int> &v)
{
    if (v.size() <= 1) return;

    std::vector<int> larger;
    std::vector<int> smaller;

    for (size_t i = 0; i + 1 < v.size(); i += 2)
    {
        if (v[i] < v[i + 1])
        {
            smaller.push_back(v[i]);
            larger.push_back(v[i + 1]);
        }
        else
        {
            smaller.push_back(v[i + 1]);
            larger.push_back(v[i]);
        }
    }
    if (v.size() % 2 != 0)
        larger.push_back(v.back());

    sort(larger);

    for (size_t i = 0; i < smaller.size(); ++i)
    {
        std::vector<int>::iterator it = std::upper_bound(larger.begin(), larger.end(), smaller[i]);
        larger.insert(it, smaller[i]);
    }

    v = larger;
}

void PmergeMe::sort(std::deque<int> &d)
{
    if (d.size() <= 1) return;

    std::deque<int> larger;
    std::deque<int> smaller;

    for (size_t i = 0; i + 1 < d.size(); i += 2)
    {
        if (d[i] < d[i + 1])
        {
            smaller.push_back(d[i]);
            larger.push_back(d[i + 1]);
        }
        else
        {
            smaller.push_back(d[i + 1]);
            larger.push_back(d[i]);
        }
    }
    if (d.size() % 2 != 0)
        larger.push_back(d.back());

    sort(larger);

    for (size_t i = 0; i < smaller.size(); ++i)
    {
        std::deque<int>::iterator it = std::upper_bound(larger.begin(), larger.end(), smaller[i]);
        larger.insert(it, smaller[i]);
    }

    d = larger;
}
