#include "PasswordAnalyzer.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <conio.h>
#endif

std::string readPassword() {
    std::string password;

#ifdef _WIN32
    char ch;

    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b";
            }
        } else if (ch >= 32 && ch <= 126) {
            password += ch;
            std::cout << '*';
        }
    }

    std::cout << '\n';
#else
    std::getline(std::cin, password);
#endif

    return password;
}

void printCheck(const std::string& name, bool value) {
    std::cout << std::left << std::setw(24) << name
              << (value ? "YES" : "NO") << '\n';
}

void saveResult(const PasswordResult& result) {
    std::ofstream file("data/analysis_results.csv");

    file << "length,uppercase,lowercase,digits,special,repeated,sequential,common_pattern,score,entropy,strength\n";
    file << result.length << ','
         << result.hasUpper << ','
         << result.hasLower << ','
         << result.hasDigit << ','
         << result.hasSpecial << ','
         << result.hasRepeated << ','
         << result.hasSequential << ','
         << result.hasCommonPattern << ','
         << result.score << ','
         << std::fixed << std::setprecision(2) << result.entropy << ','
         << result.strength << '\n';
}

int main() {
    std::cout << "========================================\n";
    std::cout << "       PASSWORD SECURITY ANALYZER\n";
    std::cout << "========================================\n\n";

    std::cout << "Enter password: ";
    std::string password = readPassword();

    if (password.empty()) {
        std::cout << "\nPassword cannot be empty.\n";
        return 1;
    }

    PasswordAnalyzer analyzer;
    PasswordResult result = analyzer.analyze(password);

    std::cout << "\nPassword Analysis\n";
    std::cout << "----------------------------------------\n";
    std::cout << std::left << std::setw(24) << "Length" << result.length << '\n';

    printCheck("Uppercase", result.hasUpper);
    printCheck("Lowercase", result.hasLower);
    printCheck("Numbers", result.hasDigit);
    printCheck("Special Characters", result.hasSpecial);
    printCheck("Repeated Characters", result.hasRepeated);
    printCheck("Sequential Pattern", result.hasSequential);
    printCheck("Common Pattern", result.hasCommonPattern);

    std::cout << "\nSecurity Score          : " << result.score << "/100\n";
    std::cout << "Strength                : " << result.strength << '\n';
    std::cout << "Estimated Entropy       : " << std::fixed << std::setprecision(2)
              << result.entropy << " bits\n";

    std::cout << "\nRecommendations\n";
    std::cout << "----------------------------------------\n";

    if (result.length < 12)
        std::cout << "- Use a password with at least 12 characters.\n";
    if (!result.hasUpper)
        std::cout << "- Add uppercase letters.\n";
    if (!result.hasLower)
        std::cout << "- Add lowercase letters.\n";
    if (!result.hasDigit)
        std::cout << "- Add numbers.\n";
    if (!result.hasSpecial)
        std::cout << "- Add special characters.\n";
    if (result.hasRepeated)
        std::cout << "- Avoid long repeated character sequences.\n";
    if (result.hasSequential)
        std::cout << "- Avoid sequential characters such as abc or 123.\n";
    if (result.hasCommonPattern)
        std::cout << "- Avoid common password words and patterns.\n";

    if (result.score >= 70)
        std::cout << "- Good password structure.\n";

    saveResult(result);

    std::cout << "\nAnalysis saved to data/analysis_results.csv\n";

    return 0;
}
