# Pushdown Automata Simulator

## 🧠 Introduction

The **Pushdown Automata (PDA) Simulator** is a C++ program designed to simulate various context-free languages using a **stack-based computation model**. It supports multiple PDA configurations for different types of languages involving patterns like `aⁿbⁿ`, `a²ⁿbⁿ`, `aⁿb²ⁿ`, etc.

This simulator helps students and researchers test and understand PDA logic through a **menu-driven console interface**.

---

## 🚀 Features

* ✅ Supports **10 different predefined PDA configurations**.
* 🧮 Simulates **stack-based transitions** with `e` (epsilon) support.
* 🔁 Interactive, menu-driven interface for user input and testing.
* 🧪 Tests membership of an input string in a selected language.
* 📚 Accepts strings by **final state and empty stack**.

---

## 📦 Installation & Compilation

### Clone the Repository

```bash
git clone https://github.com/connect-abdulbasit/Push-Down-Automata.git
cd pushdown-automata-simulator
```

### Compile the Program (Linux/macOS)

```bash
g++ -o pda_simulator pda_simulator.cpp
```

### Run the Simulator

```bash
./pda_simulator
```

For Windows (MinGW):

```bash
g++ -o pda_simulator.exe pda_simulator.cpp
pda_simulator.exe
```

---

## 🧪 Available PDA Options

| Option | Language Recognized           | Pattern                  |
| ------ | ----------------------------- | ------------------------ |
| 1      | Equal `a` and `b`             | aⁿbⁿ                     |
| 2      | Double `a` than `b`           | a²ⁿbⁿ                    |
| 3      | Triple `a` than `b`           | a³ⁿbⁿ                    |
| 4      | Double `b` than `a`           | aⁿb²ⁿ                    |
| 5      | Triple `b` than `a`           | aⁿb³ⁿ                    |
| 6      | Equal doubled a's and b's     | a²ⁿb²ⁿ                   |
| 7      | More a's than b's (n > m > 0) | aⁿbᵐ                     |
| 8      | aⁿbᵐcⁿ⁺ᵐ                      | Balanced triple sequence |
| 9      | aⁿbⁿcᵐdᵐ                      | Dual equal subsequences  |
| 10     | aⁿbᵐcᵐdⁿ                      | Symmetric dual pattern   |

---

## 👨‍💻 How It Works

1. Choose an option (1–10) from the language list.
2. Enter the input string (e.g., `aaabbb`).
3. The simulator checks if the input is accepted based on:

   * Transitions defined for the selected PDA.
   * Stack operations including push, pop, and epsilon handling.
   * Final state and empty stack condition.

---


## 🤝 Contributing

Contributions are welcome! To get started:

1. Fork the repository.
2. Make your changes.
3. Submit a Pull Request with a clear description.

---

## 📄 License

This project is licensed under the **MIT License** – feel free to use, modify, and distribute.

---

## 📬 Contact

For issues or feature requests, open an [issue](https://github.com/your-repo/pushdown-automata-simulator/issues) or reach out to the **project maintainer**.

---

🚀 **Happy simulating with Pushdown Automata!** 🚀

---
