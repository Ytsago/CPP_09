#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <ctime>

PmergeMe::PmergeMe() : _vecTime(0), _deqTime(0) {}

PmergeMe::PmergeMe(const PmergeMe& other)
    : _vec(other._vec), _deq(other._deq),
      _vecTime(other._vecTime), _deqTime(other._deqTime) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        _vec = other._vec;
        _deq = other._deq;
        _vecTime = other._vecTime;
        _deqTime = other._deqTime;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::parseInput(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        std::istringstream iss(argv[i]);
        long val;
        char leftover;
        if (!(iss >> val) || iss.get(leftover))
            throw std::runtime_error("Error");
        if (val <= 0)
            throw std::runtime_error("Error");
        _vec.push_back(static_cast<int>(val));
        _deq.push_back(static_cast<int>(val));
    }
    if (_vec.empty())
        throw std::runtime_error("Error");
}

// ─── Jacobsthal sequence ────────────────────────────────────────────────────
// Returns indices into the "pending" array in the order they should be inserted
std::vector<size_t> PmergeMe::jacobsthalOrder(size_t n) const {
    // Build Jacobsthal numbers up to n
    std::vector<size_t> jac;
    jac.push_back(0);
    jac.push_back(1);
    while (true) {
        size_t next = jac[jac.size()-1] + 2 * jac[jac.size()-2];
        if (next >= n) break;
        jac.push_back(next);
    }

    // Build insertion order from Jacobsthal groups
    std::vector<size_t> order;
    std::vector<bool>   inserted(n, false);

    size_t prev = 1;
    for (size_t k = 2; k < jac.size(); ++k) {
        size_t cur = jac[k];
        if (cur > n) cur = n;
        // Insert from cur down to prev (exclusive) in decreasing order
        for (size_t idx = cur; idx > prev; --idx) {
            size_t i = idx - 1; // 0-based
            if (i < n && !inserted[i]) {
                order.push_back(i);
                inserted[i] = true;
            }
        }
        prev = cur;
    }
    // Remaining elements not yet inserted
    for (size_t i = 0; i < n; ++i) {
        if (!inserted[i])
            order.push_back(i);
    }
    return order;
}

// ─── VECTOR ─────────────────────────────────────────────────────────────────

void PmergeMe::insertIntoSorted(std::vector<int>& arr, int value) {
    // Binary search insertion
    int lo = 0, hi = static_cast<int>(arr.size());
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (arr[mid] < value) lo = mid + 1;
        else                  hi = mid;
    }
    arr.insert(arr.begin() + lo, value);
}

void PmergeMe::mergeInsertSort(std::vector<int>& arr) {
    size_t n = arr.size();
    if (n <= 1) return;

    // 1. Pair up elements; keep track of larger/smaller of each pair
    bool hasStraggler = (n % 2 != 0);
    int  straggler    = hasStraggler ? arr.back() : 0;

    std::vector<int> larger, smaller;
    for (size_t i = 0; i + 1 < n; i += 2) {
        if (arr[i] >= arr[i + 1]) {
            larger.push_back(arr[i]);
            smaller.push_back(arr[i + 1]);
        } else {
            larger.push_back(arr[i + 1]);
            smaller.push_back(arr[i]);
        }
    }

    // 2. Recursively sort the "larger" sequence
    mergeInsertSort(larger);

    // 3. Build the main chain: start with sorted largers,
    //    then insert the smallest of the "smaller" elements (index 0)
    //    which pairs with the smallest larger (already at front).
    std::vector<int> mainChain(larger);

    // Insert the first pending element (smaller[0] pairs with larger[0])
    if (!smaller.empty())
        insertIntoSorted(mainChain, smaller[0]);

    // 4. Insert remaining smaller elements using Jacobsthal order
    if (smaller.size() > 1) {
        std::vector<size_t> order = jacobsthalOrder(smaller.size());
        for (size_t k = 0; k < order.size(); ++k) {
            size_t idx = order[k];
            if (idx == 0) continue; // already inserted
            insertIntoSorted(mainChain, smaller[idx]);
        }
    }

    // 5. Insert straggler if any
    if (hasStraggler)
        insertIntoSorted(mainChain, straggler);

    arr = mainChain;
}

// ─── DEQUE ──────────────────────────────────────────────────────────────────

void PmergeMe::insertIntoSorted(std::deque<int>& arr, int value) {
    int lo = 0, hi = static_cast<int>(arr.size());
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (arr[mid] < value) lo = mid + 1;
        else                  hi = mid;
    }
    arr.insert(arr.begin() + lo, value);
}

void PmergeMe::mergeInsertSort(std::deque<int>& arr) {
    size_t n = arr.size();
    if (n <= 1) return;

    bool hasStraggler = (n % 2 != 0);
    int  straggler    = hasStraggler ? arr.back() : 0;

    std::deque<int> larger, smaller;
    for (size_t i = 0; i + 1 < n; i += 2) {
        if (arr[i] >= arr[i + 1]) {
            larger.push_back(arr[i]);
            smaller.push_back(arr[i + 1]);
        } else {
            larger.push_back(arr[i + 1]);
            smaller.push_back(arr[i]);
        }
    }

    mergeInsertSort(larger);

    std::deque<int> mainChain(larger);

    if (!smaller.empty())
        insertIntoSorted(mainChain, smaller[0]);

    if (smaller.size() > 1) {
        std::vector<size_t> order = jacobsthalOrder(smaller.size());
        for (size_t k = 0; k < order.size(); ++k) {
            size_t idx = order[k];
            if (idx == 0) continue;
            insertIntoSorted(mainChain, smaller[idx]);
        }
    }

    if (hasStraggler)
        insertIntoSorted(mainChain, straggler);

    arr = mainChain;
}

// ─── Public sort + timing ────────────────────────────────────────────────────

void PmergeMe::sort() {
    struct timespec start, end;

    // Vector
    clock_gettime(CLOCK_MONOTONIC, &start);
    mergeInsertSort(_vec);
    clock_gettime(CLOCK_MONOTONIC, &end);
    _vecTime = (end.tv_sec  - start.tv_sec)  * 1e6
             + (end.tv_nsec - start.tv_nsec) * 1e-3;

    // Deque
    clock_gettime(CLOCK_MONOTONIC, &start);
    mergeInsertSort(_deq);
    clock_gettime(CLOCK_MONOTONIC, &end);
    _deqTime = (end.tv_sec  - start.tv_sec)  * 1e6
             + (end.tv_nsec - start.tv_nsec) * 1e-3;
}

void PmergeMe::printResults() const {
    // Before (stored in deq before sort — but we sorted it,
    // so we reconstructed from sorted; show sorted here per spec)
    // NOTE:  "Before" is printed in main before sort(); "After" here.
    std::cout << "After:  ";
    for (size_t i = 0; i < _vec.size(); ++i) {
        std::cout << _vec[i];
        if (i + 1 < _vec.size()) std::cout << ' ';
    }
    std::cout << '\n';

    std::cout << std::fixed;
    std::cout.precision(5);
    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << _vecTime << " us\n";
    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : " << _deqTime << " us\n";
}
