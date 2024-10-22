#include <iostream>
#include <vector>
#include "complex.h"
#include "sort.h"

int main() {
    std::vector<Complex> numbers = {
        Complex(3, 4),
        Complex(1, 1),
        Complex(2, 2),
        Complex(0, 5),
        Complex(-1, -1)
    };

    std::cout << "Before sorting:\n";
    for (const auto& num : numbers) {
        std::cout << num << "\n";
    }

    sortComplexNumbers(numbers);

    std::cout << "\nAfter sorting by absolute value:\n";
    for (const auto& num : numbers) {
        std::cout << num << "\n";
    }

    return 0;
}
