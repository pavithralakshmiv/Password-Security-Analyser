#include "PasswordAnalyzer.h"
#include <algorithm>
#include <cmath>
#include <cctype>
#include <string>

PasswordResult PasswordAnalyzer::analyze(const std::string& password) {
    PasswordResult result{};

    result.length = static_cast<int>(password.length());

    for (char ch : password) {
        unsigned char value = static_cast<unsigned char>(ch);

        if (std::isupper(value))
            result.hasUpper = true;
        else if (std::islower(value))
            result.hasLower = true;
        else if (std::isdigit(value))
            result.hasDigit = true;
        else
            result.hasSpecial = true;
    }

    result.hasRepeated = hasRepeatedCharacters(password);
    result.hasSequential = hasSequentialCharacters(password);
    result.hasCommonPattern = hasCommonPattern(password);
    result.score = calculateScore(result);
    result.entropy = calculateEntropy(result);
    result.strength = getStrength(result.score);

    return result;
}

bool PasswordAnalyzer::hasRepeatedCharacters(const std::string& password) {
    if (password.empty())
        return false;

    int repeated = 1;

    for (size_t i = 1; i < password.length(); ++i) {
        if (password[i] == password[i - 1]) {
            ++repeated;
            if (repeated >= 3)
                return true;
        } else {
            repeated = 1;
        }
    }

    return false;
}

bool PasswordAnalyzer::hasSequentialCharacters(const std::string& password) {
    if (password.length() < 3)
        return false;

    std::string value = password;
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });

    for (size_t i = 0; i + 2 < value.length(); ++i) {
        int first = static_cast<unsigned char>(value[i]);
        int second = static_cast<unsigned char>(value[i + 1]);
        int third = static_cast<unsigned char>(value[i + 2]);

        if (second == first + 1 && third == second + 1)
            return true;

        if (second == first - 1 && third == second - 1)
            return true;
    }

    return false;
}

bool PasswordAnalyzer::hasCommonPattern(const std::string& password) {
    std::string value = password;

    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });

    const std::string patterns[] = {
        "password",
        "admin",
        "welcome",
        "qwerty",
        "letmein",
        "iloveyou",
        "abc123",
        "password123",
        "admin123"
    };

    for (const std::string& pattern : patterns) {
        if (value.find(pattern) != std::string::npos)
            return true;
    }

    return false;
}

int PasswordAnalyzer::calculateScore(const PasswordResult& result) {
    int score = 0;

    if (result.length >= 8)
        score += 20;
    if (result.length >= 12)
        score += 15;
    if (result.length >= 16)
        score += 10;

    if (result.hasUpper)
        score += 10;
    if (result.hasLower)
        score += 10;
    if (result.hasDigit)
        score += 10;
    if (result.hasSpecial)
        score += 15;

    if (result.hasRepeated)
        score -= 10;
    if (result.hasSequential)
        score -= 10;
    if (result.hasCommonPattern)
        score -= 25;

    if (score < 0)
        score = 0;
    if (score > 100)
        score = 100;

    return score;
}

double PasswordAnalyzer::calculateEntropy(const PasswordResult& result) {
    int pool = 0;

    if (result.hasLower)
        pool += 26;
    if (result.hasUpper)
        pool += 26;
    if (result.hasDigit)
        pool += 10;
    if (result.hasSpecial)
        pool += 32;

    if (pool == 0 || result.length == 0)
        return 0.0;

    return result.length * std::log2(static_cast<double>(pool));
}

std::string PasswordAnalyzer::getStrength(int score) {
    if (score >= 85)
        return "VERY STRONG";
    if (score >= 70)
        return "STRONG";
    if (score >= 50)
        return "MODERATE";
    if (score >= 30)
        return "WEAK";
    return "VERY WEAK";
}
