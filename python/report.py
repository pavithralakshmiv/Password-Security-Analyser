import csv
from pathlib import Path
import matplotlib.pyplot as plt

ROOT = Path(__file__).resolve().parent.parent
DATA_FILE = ROOT / "data" / "analysis_results.csv"
OUTPUT_DIR = ROOT / "output"

def load_result():
    with DATA_FILE.open("r", newline="", encoding="utf-8") as file:
        return next(csv.DictReader(file))

def create_report(result):
    OUTPUT_DIR.mkdir(exist_ok=True)

    labels = ["Lowercase", "Uppercase", "Numbers", "Special"]
    values = [
        int(result["lowercase"]),
        int(result["uppercase"]),
        int(result["digits"]),
        int(result["special"])
    ]

    plt.figure(figsize=(8, 5))
    plt.bar(labels, values)
    plt.ylim(0, 1.2)
    plt.ylabel("Detected")
    plt.title(f"Password Security: {result['strength']}")
    plt.tight_layout()
    plt.savefig(OUTPUT_DIR / "character_composition.png", dpi=150)
    plt.close()

    score = int(result["score"])

    plt.figure(figsize=(8, 5))
    plt.bar(["Security Score"], [score])
    plt.ylim(0, 100)
    plt.ylabel("Score")
    plt.title("Password Security Score")
    plt.tight_layout()
    plt.savefig(OUTPUT_DIR / "security_score.png", dpi=150)
    plt.close()

    report = OUTPUT_DIR / "security_report.txt"

    with report.open("w", encoding="utf-8") as file:
        file.write("PASSWORD SECURITY REPORT\n")
        file.write("========================\n\n")
        file.write(f"Length: {result['length']}\n")
        file.write(f"Security Score: {result['score']}/100\n")
        file.write(f"Strength: {result['strength']}\n")
        file.write(f"Estimated Entropy: {result['entropy']} bits\n")

    print("\nPython report created successfully.")
    print(f"Output folder: {OUTPUT_DIR}")

if __name__ == "__main__":
    create_report(load_result())
