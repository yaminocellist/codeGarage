#include <iostream>
#include <cmath>

long long f(long long x) {
    return (x + 1) * x * (2 * x + 1) / 6;
}

long long solve_n1(long long n) {
    long long target = (n + 1) * n * (2 * n + 1) / 48;
    long long left = 0, right = n;  // Assuming x is not larger than 2n
    
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
    if (abs(f(left) - target) < abs(f(right) - target)) {
        return left;
    } else {
        return right;
    }
}

long long solve_n2(long long n, long long n1) {
    long long target = f(n1) + (n + 1) * n * (2 * n + 1) / 48;
    long long left = n1, right = n;  // Assuming y is not smaller than x and not larger than 3n
    
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
    if (abs(f(left) - target) < abs(f(right) - target)) {
        return left;
    } else {
        return right;
    }
}

long long solve_n3(long long n, long long n1, long long n2) {
    long long target = f(n2) + (n + 1) * n * (2 * n + 1) / 48;
    long long left = n2, right = n;  // Assuming n3 is not smaller than y and not larger than 4n
    
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
    if (abs(f(left) - target) < abs(f(right) - target)) {
        return left;
    } else {
        return right;
    }
}

long long solve_n4(long long n, long long n3) {
    long long target = f(n3) + (n + 1) * n * (2 * n + 1) / 48;
    long long left = n3, right = n;  // Assuming n3 is not smaller than y and not larger than 4n
    
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
    if (abs(f(left) - target) < abs(f(right) - target)) {
        return left;
    } else {
        return right;
    }
}

long long solve_n5(long long n, long long n4) {
    long long target = f(n4) + (n + 1) * n * (2 * n + 1) / 48;
    long long left = n4, right = n;  // Assuming n3 is not smaller than y and not larger than 4n
    
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
    if (abs(f(left) - target) < abs(f(right) - target)) {
        return left;
    } else {
        return right;
    }
}

long long solve_n6(long long n, long long n5) {
    long long target = f(n5) + (n + 1) * n * (2 * n + 1) / 48;
    long long left = n5, right = n;  // Assuming n3 is not smaller than y and not larger than 4n
    
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
    if (abs(f(left) - target) < abs(f(right) - target)) {
        return left;
    } else {
        return right;
    }
}

long long solve_n7(long long n, long long n6) {
    long long target = f(n6) + (n + 1) * n * (2 * n + 1) / 48;
    long long left = n6, right = n;  // Assuming n3 is not smaller than y and not larger than 4n
    
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
    if (abs(f(left) - target) < abs(f(right) - target)) {
        return left;
    } else {
        return right;
    }
}

int main() {
    long long n;
    std::cout << "Enter the value of n: ";
    std::cin >> n;
    
    long long n1 = solve_n1(n);
    long long n2 = solve_n2(n, n1);
    long long n3 = solve_n3(n, n1, n2);
    long long n4 = solve_n4(n, n3);
    long long n5 = solve_n4(n, n4);
    long long n6 = solve_n4(n, n5);
    long long n7 = solve_n4(n, n6);
    
    std::cout << "The closest integer solution for n1 is: " << n1 << std::endl;
    std::cout << "The closest integer solution for n2 is: " << n2 << std::endl;
    std::cout << "The closest integer solution for n3 is: " << n3 << std::endl;
    std::cout << "The closest integer solution for n4 is: " << n4 << std::endl;
    std::cout << "The closest integer solution for n5 is: " << n5 << std::endl;
    std::cout << "The closest integer solution for n6 is: " << n6 << std::endl;
    std::cout << "The closest integer solution for n7 is: " << n7 << std::endl;
    
    return 0;
}