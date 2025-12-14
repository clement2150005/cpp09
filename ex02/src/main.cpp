#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <climits>
#include <ctime>

int main(int argc, char **argv)
{
	if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return 0;
    }

	std::vector<int> vec;
	std::deque<int> deq;

	clock_t start = clock();
	for (int i = 1; i < argc; ++i)
	{
		const char *s = argv[i];
		if (*s == '\0')
		{
			std::cerr << "Error" << std::endl;
			return 1;
		}
		for (; *s; ++s)
		{
			if (!isdigit(*s))
			{
				std::cerr << "Error" << std::endl;
				return 1;
			}
		}

		long val = std::strtol(argv[i], NULL, 10);
		if (val <= 0 || val > INT_MAX)
		{
			std::cerr << "Error" << std::endl;
			return 1;
		}

		vec.push_back(static_cast<int>(val));
	}

	PmergeMe::sort(vec);
	clock_t end = clock();

	std::cout << "Before: ";
	for (int i = 1; i < argc; ++i)
		std::cout << argv[i] << (i + 1 < argc ? " " : "\n");

	std::cout << "After: ";
	for (size_t i = 0; i < vec.size(); ++i)
		std::cout << vec[i] << (i + 1 < vec.size() ? " " : "\n");

	double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
	std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << duration << " us" << std::endl;

	start = clock();
	for (int i = 1; i < argc; ++i)
	{
		long val = std::strtol(argv[i], NULL, 10);
		deq.push_back(static_cast<int>(val));
	}
	PmergeMe::sort(deq);
	end = clock();

	duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
	std::cout << "Time to process a range of " << deq.size() << " elements with std::deque : " << duration << " us" << std::endl;

	return 0;
}

// #include <iostream>
// #include <vector>
// #include <cstdlib>
// #include <climits>

// int main(int argc, char **argv)
// {
// 	if (argc < 2)
// 		return 0;

// 	std::vector<int> vec;
// 	for (int i = 1; i < argc; ++i)
// 		vec.push_back(std::atoi(argv[i]));

// 	bool sorted = true;
// 	for (size_t i = 1; i < vec.size(); ++i)
// 	{
// 		if (vec[i - 1] > vec[i])
// 		{
// 			sorted = false;
// 			break;
// 		}
// 	}

// 	if (sorted)
// 		std::cout << "Sorted" << std::endl;
// 	else
// 		std::cout << "Not sorted" << std::endl;

// 	return 0;
// }

// for i in {1..3000}; do echo -n "$((RANDOM % 4000 + 1)) "; done; echo
