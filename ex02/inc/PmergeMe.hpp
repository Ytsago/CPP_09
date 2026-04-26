#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class PmergeMe {
public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    void parseInput(int argc, char** argv);
    void sort();
    void printResults() const;

private:
    std::vector<int> _vec;
    std::deque<int>  _deq;
    double           _vecTime;
    double           _deqTime;

    // Ford-Johnson for vector
    void mergeInsertSort(std::vector<int>& arr);
    void insertIntoSorted(std::vector<int>& arr, int value);

    // Ford-Johnson for deque
    void mergeInsertSort(std::deque<int>& arr);
    void insertIntoSorted(std::deque<int>& arr, int value);

    // Jacobsthal sequence for insertion order
    std::vector<size_t> jacobsthalOrder(size_t n) const;
};

#endif
