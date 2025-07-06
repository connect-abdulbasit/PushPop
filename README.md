# 🧮 PushPop – A Pushdown Automata Simulator

**PushPop** is a C++ console application built to simulate various **Pushdown Automata (PDA)** for different context-free languages. Built around a **stack-based computation model**, it supports multiple language patterns like `aⁿbⁿ`, `a²ⁿbⁿ`, `aⁿb²ⁿ`, and more.

This simulator is designed to help students, instructors, and enthusiasts **understand PDA operations** through an interactive and visual approach.

---

## 🚀 Features

- ✅ **10 predefined PDA configurations** for different CFL patterns.
- 📥 Stack-based transitions with **epsilon (ε) support**.
- 🧠 Interactive **menu-driven interface** for testing input strings.
- 🧪 Accepts strings using both **final state** and **empty stack** criteria.
- 🧾 Clean output showing real-time stack operations and state transitions.

---

## 📦 Installation & Compilation

### Clone the Repository

```bash
git clone https://github.com/connect-abdulbasit/Push-Down-Automata.git
cd pushdown-automata-simulator
````

### Compile the Program (Linux/macOS)

```bash
g++ -o pushpop pushpop.cpp
```

### Run the Simulator

```bash
./pushpop
```

For Windows (MinGW):

```bash
g++ -o pushpop.exe pushpop.cpp
pushpop.exe
```

---

## 🧪 Available PDA Modes

| Option | Language Recognized           | Pattern  |
| ------ | ----------------------------- | -------- |
| 1      | Equal `a` and `b`             | aⁿbⁿ     |
| 2      | Double `a` than `b`           | a²ⁿbⁿ    |
| 3      | Triple `a` than `b`           | a³ⁿbⁿ    |
| 4      | Double `b` than `a`           | aⁿb²ⁿ    |
| 5      | Triple `b` than `a`           | aⁿb³ⁿ    |
| 6      | Equal doubled a's and b's     | a²ⁿb²ⁿ   |
| 7      | More a’s than b’s (n > m > 0) | aⁿbᵐ     |
| 8      | Balanced triple sequence      | aⁿbᵐcⁿ⁺ᵐ |
| 9      | Dual equal subsequences       | aⁿbⁿcᵐdᵐ |
| 10     | Symmetric dual pattern        | aⁿbᵐcᵐdⁿ |

---

## 🔍 How It Works

1. Select a PDA configuration (1–10).
2. Input your test string (e.g., `aaabbb`).
3. Watch the simulator:

   * Apply transitions and stack operations.
   * Show push/pop actions and epsilon moves.
   * Determine whether the string is accepted or rejected.

---

## 👨‍💻 Contributors

* **Abdul Basit**
* *(Your collaborator names if any)*

---

## 🤝 Contributing

Contributions are welcome!
To contribute:

1. Fork the repository.
2. Create a new branch.
3. Commit and push your changes.
4. Open a Pull Request.

---

## 📄 License

This project is licensed under the **MIT License** – free to use, modify, and distribute.

---

## 📬 Contact

For feature requests or bug reports, open an [issue](https://github.com/connect-abdulbasit/Push-Down-Automata/issues) or reach out to the **project maintainer**.



