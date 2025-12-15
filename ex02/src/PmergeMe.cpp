#include "PmergeMe.hpp"
#include <algorithm>
#include <deque>
#include <vector>

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &) {}
PmergeMe &PmergeMe::operator=(const PmergeMe &) { return *this; }
PmergeMe::~PmergeMe() {}

size_t	PmergeMe::jacobsthal(size_t n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;
	size_t a = 0, b = 1, c;
	for (size_t i = 2; i <= n; ++i)
	{
		c = b + 2 * a;
		a = b;
		b = c;
	}
	return b;
}

void PmergeMe::sort(std::vector<int> &v)
{
	if (v.size() <= 1)
		return; // Vector with 0 or 1 element is already sorted.

	// Build pairs. Each pair stores the larger element first, smaller second.
	std::vector<std::pair<int,int> > pairs;
	size_t i = 0;
	for (; i + 1 < v.size(); i += 2)
	{
		if (v[i] < v[i + 1])
			pairs.push_back(std::make_pair(v[i + 1], v[i]));
		else
			pairs.push_back(std::make_pair(v[i], v[i + 1]));
	}

	// Track leftover element if vector size is odd.
	bool hasOdd = (i < v.size());
	int odd = hasOdd ? v[i] : 0;

	// Initialize main chain with the first element of each pair (the larger elements).
	std::vector<int> mainChain;
	for (size_t j = 0; j < pairs.size(); ++j)
		mainChain.push_back(pairs[j].first);

	// Sort main chain to allow binary search insertion for the second elements of the pairs.
	sort(mainChain);

	// Precompute Jacobsthal sequence for pend element insertion order.
	size_t JacobsthalArray[] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923,
	                            21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203,
	                            5592405, 11184811, 22369621, 44739243, 89478485, 178956971,
	                            357913941, 715827883, 1431655765};
	size_t jac_idx = 1;
	std::vector<std::pair<int,int> >::iterator last_jacob_it = pairs.begin();

	while (true)
	{
		// Determine current Jacobsthal number, using precomputed array if available; otherwise, compute dynamically.
		size_t jac_number;
		if (static_cast<size_t>(jac_idx) < sizeof(JacobsthalArray)/sizeof(JacobsthalArray[0]))
			jac_number = JacobsthalArray[jac_idx];
		else
			jac_number = jacobsthal(jac_idx);

		// Stop loop if Jacobsthal number exceeds number of pairs.
		if (jac_number > pairs.size())
			break;

		// Locate the pair corresponding to current Jacobsthal number.
		std::vector<std::pair<int,int> >::iterator it = pairs.begin() + (jac_number - 1);
		last_jacob_it = it;

		// Insert pend elements from this slice into the main chain until previous Jacobsthal number is reached.
		int inserted_count = 0;
		size_t prev_jac_number = (jac_idx == 0) ? 0 :
			(static_cast<size_t>(jac_idx - 1) < sizeof(JacobsthalArray)/sizeof(JacobsthalArray[0]) ? JacobsthalArray[jac_idx - 1] : jacobsthal(jac_idx - 1));

        while (jac_number - inserted_count > prev_jac_number)
        {
			// Find the position of the first element in main chain to limit search range for second element.
			std::vector<int>::iterator slice_it = std::find(mainChain.begin(), mainChain.end(), it->first);
			// Use binary search to find correct insertion point for second element.
			std::vector<int>::iterator pos = PmergeMe::binarySearch(mainChain.begin(), slice_it, it->second);
			mainChain.insert(pos, it->second); // Insert second element maintaining sorted order.
			it--;
			inserted_count++;
        }

		jac_idx++; // Move to next Jacobsthal number.
	}

	// Insert remaining pend elements not covered by Jacobsthal sequence.
	if (last_jacob_it != pairs.end())
	{
		std::vector<std::pair<int,int> >::iterator it = pairs.end();
		it--;
		while (it != last_jacob_it)
		{
			std::vector<int>::iterator slice_it = std::find(mainChain.begin(), mainChain.end(), it->first);
			std::vector<int>::iterator pos = PmergeMe::binarySearch(mainChain.begin(), slice_it, it->second);
			mainChain.insert(pos, it->second);
			it--;
		}
	}

	// Insert odd element if it exists.
	if (hasOdd)
	{
		std::vector<int>::iterator pos = PmergeMe::binarySearch(mainChain.begin(), mainChain.end(), odd);
		mainChain.insert(pos, odd);
	}

	v = mainChain; // Copy sorted main chain back to original vector.
}

void PmergeMe::sort(std::deque<int> &d)
{
	if (d.size() <= 1)
		return;

	std::deque<std::pair<int,int> > pairs;
	size_t i = 0;
	for (; i + 1 < d.size(); i += 2)
	{
		if (d[i] < d[i + 1])
			pairs.push_back(std::make_pair(d[i + 1], d[i]));
		else
			pairs.push_back(std::make_pair(d[i], d[i + 1]));
	}

	bool hasOdd = (i < d.size());
	int odd = hasOdd ? d[i] : 0;

	std::deque<int> mainChain;
	for (size_t j = 0; j < pairs.size(); ++j)
		mainChain.push_back(pairs[j].first);

	sort(mainChain);

	size_t JacobsthalArray[] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923,
	                            21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203,
	                            5592405, 11184811, 22369621, 44739243, 89478485, 178956971,
	                            357913941, 715827883, 1431655765};
	size_t jac_idx = 1;
	std::deque<std::pair<int,int> >::iterator last_jacob_it = pairs.begin();

	while (true)
	{
		size_t jac_number;
		if (jac_idx < sizeof(JacobsthalArray)/sizeof(JacobsthalArray[0]))
			jac_number = JacobsthalArray[jac_idx];
		else
			jac_number = jacobsthal(jac_idx);

		if (jac_number > pairs.size())
			break;

		std::deque<std::pair<int,int> >::iterator it = pairs.begin() + (jac_number - 1);
		last_jacob_it = it;

		int inserted_count = 0;
		size_t prev_jac_number = (jac_idx == 0) ? 0 :
			(jac_idx - 1 < sizeof(JacobsthalArray)/sizeof(JacobsthalArray[0]) ? JacobsthalArray[jac_idx - 1] : jacobsthal(jac_idx - 1));

        while (jac_number - inserted_count > prev_jac_number)
        {
            std::deque<int>::iterator slice_it = std::find(mainChain.begin(), mainChain.end(), it->first);
            std::deque<int>::iterator pos = PmergeMe::binarySearch(mainChain.begin(), slice_it, it->second);
            mainChain.insert(pos, it->second);
            it--;
            inserted_count++;
        }

		jac_idx++;
	}

    if (last_jacob_it != pairs.end())
    {
        std::deque<std::pair<int,int> >::iterator it = pairs.end();
        it--;
        while (it != last_jacob_it)
        {
            std::deque<int>::iterator slice_it = std::find(mainChain.begin(), mainChain.end(), it->first);
            std::deque<int>::iterator pos = PmergeMe::binarySearch(mainChain.begin(), slice_it, it->second);
            mainChain.insert(pos, it->second);
            it--;
        }
    }

    if (hasOdd)
    {
        std::deque<int>::iterator pos = PmergeMe::binarySearch(mainChain.begin(), mainChain.end(), odd);
        mainChain.insert(pos, odd);
    }

	d = mainChain;
}

