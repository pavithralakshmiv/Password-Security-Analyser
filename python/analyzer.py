import csv
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DATA_FILE = ROOT / "data" / "analysis_results.csv"

def load_result():
    with DATA_FILE.open("r", newline="", encoding="utf-8") as file:
        return next(csv.DictReader(file))

def print_report(result):
    print("\n========================================")
    print("          PYTHON SECURITY REPORT")
    print("========================================")
    print(f"Score: {result['score']}/100")
    print(f"Strength: {result['strength']}")
    print(f"Entropy: {result['entropy']} bits")
    print("\nCharacter Composition")
    print("----------------------------------------")

    items = [
        ("Lowercase", result["lowercase"]),
        ("Uppercase", result["uppercase"]),
        ("Numbers", result["digits"]),
        ("Special", result["special"])
    ]

    for name, value in items:
        print(f"{name:12} {'Present' if value == '1' else 'Missing'}")

if __name__ == "__main__":
    print_report(load_result())
