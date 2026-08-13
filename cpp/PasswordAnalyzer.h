#ifndef PASSWORD_ANALYZER_H
#define PASSWORD_ANALYZER_H

#include <string>

struct PasswordResult {
    int length;
    bool hasUpper;
    bool hasLower;
    bool hasDigit;
    bool hasSpecial;
    bool hasRepeated;
    bool hasSequential;
    bool hasCommonPattern;
    int score;
    double entropy;
    std::string strength;
};

class PasswordAnalyzer {
public:
    PasswordResult analyze(const std::string& password);

private:
    bool hasSequentialCharacters(const std::string& password);
    bool hasCommonPattern(const std::string& password);
    bool hasRepeatedCharacters(const std::string& password);
    int calculateScore(const PasswordResult& result);
    double calculateEntropy(const PasswordResult& result);
    std::string getStrength(int score);
};

#endif
