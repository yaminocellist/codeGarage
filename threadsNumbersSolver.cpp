#include <iostream>
#include <cmath>
#include <vector>

long long f(long long x) {
    return (x + 1) * x * (2 * x + 1) / 6;
}

long long solve_ni(long long n, long long prev_ni) {
    long long target = f(prev_ni) + (n + 1) * n * (2 * n + 1) / 48;
    long long left = prev_ni, right = n;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        long long value = f(mid);
        
        if (value == target) {
            return mid;
        } else if (value < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    // If we didn't find an exact match, return the closest value
    return (abs(f(left) - target) < abs(f(right) - target)) ? left : right;
}

std::vector<long long> solve_all_ni(long long n, int count) {
    std::vector<long long> result(count);
    result[0] = solve_ni(n, 0);  // Special case for n1
    
    for (int i = 1; i < count; ++i) {
        result[i] = solve_ni(n, result[i-1]);
    }
    
    return result;
}

int main() {
    long long n;
    int divider;
    std::cout << "Enter the value of n: ";
    std::cin >> n;
    std::cout << "Enter the number of dividers to calculate:";
    std::cin >> divider;
    
    std::vector<long long> solutions = solve_all_ni(n, 7);
    
    for (int i = 0; i < solutions.size(); ++i) {
        std::cout << "The closest integer solution for n" << i+1 << " is: " << solutions[i] << std::endl;
    }
    
    return 0;
}