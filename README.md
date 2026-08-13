# Password Security Analyzer

A desktop command-line mini project built with C++ and Python to analyze password strength.

## Features

- Checks password length
- Detects uppercase and lowercase characters
- Detects numbers and special characters
- Detects repeated characters
- Detects common weak patterns
- Detects sequential characters
- Calculates a password strength score
- Calculates estimated entropy
- Generates a Python-based visual report
- Stores analysis results in CSV format

## Technologies

- C++
- Python
- C++ STL
- Python standard library
- Matplotlib

## Project Structure

```text
password-security-analyzer/
├── cpp/
│   ├── main.cpp
│   ├── PasswordAnalyzer.cpp
│   └── PasswordAnalyzer.h
├── python/
│   ├── analyzer.py
│   └── report.py
├── data/
│   └── analysis_results.csv
├── output/
├── run.bat
└── README.md
```

## Requirements

- Windows
- C++ compiler such as MinGW g++
- Python 3
- Matplotlib

Install Matplotlib with:

```text
pip install matplotlib
```

## Run

Double-click `run.bat` or run:

```text
run.bat
```

The C++ program analyzes the password and saves the result. Python then creates a visual report inside the `output` folder.

## Note

The project is intended for educational use. It does not attempt to crack passwords or connect to external services.
