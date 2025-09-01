#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "json.hpp" // Make sure this file is in the same directory

using json = nlohmann::json;

// Convert string from given base to decimal
long long base_to_decimal(const std::string &num_str, int base) {
    long long result = 0;
    for (char c : num_str) {
        int digit;
        if (std::isdigit(c)) digit = c - '0';
        else digit = std::tolower(c) - 'a' + 10;
        result = result * base + digit;
    }
    return result;
}

// Compute polynomial coefficients from roots using Vieta's formula
void print_coefficients(const std::vector<long long> &roots) {
    int k = roots.size(); // degree = k-1
    std::vector<long long> coeffs(k + 1, 0);
    coeffs[0] = 1;
    for (int i = 0; i < k; ++i) {
        for (int j = i + 1; j > 0; --j)
            coeffs[j] -= roots[i] * coeffs[j - 1];
    }
    std::cout << "Polynomial coefficients (from highest degree):\n";
    for (int i = 0; i <= k; ++i)
        std::cout << "a_" << k - i << " = " << coeffs[i] << std::endl;
}

int main() {
    std::ifstream infile("input.json");
    if (!infile.is_open()) {
        std::cerr << "Failed to open input.json\n";
        return 1;
    }
    json data;
    infile >> data;

    int k = data["keys"]["k"];
    std::vector<long long> roots;
    for (int i = 1; i <= k; ++i) {
        int base = std::stoi(data[std::to_string(i)]["base"].get<std::string>());
        std::string value = data[std::to_string(i)]["value"].get<std::string>();
        roots.push_back(base_to_decimal(value, base));
    }

    print_coefficients(roots);
    return 0;
}
