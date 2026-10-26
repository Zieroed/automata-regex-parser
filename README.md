# Regex-Based Arithmetic Expression Parser (C++)

A command-line application developed as a group final project for **Automata Theory and Formal Languages**.

The program demonstrates basic lexical token classification, regular-expression-based syntax validation, integer arithmetic evaluation, and variable storage using C++17.

## Features
- Classifies tokens such as identifiers, integers, operators, and keywords using regular expressions.
- Validates simple variable assignments and arithmetic expressions.
- Evaluates addition, subtraction, multiplication, and integer division.
- Stores and updates variables using `std::unordered_map`.
- Rejects unsupported expressions and detects undefined variables and division by zero.

## Example
```text
x = 5
y = 7 / 5
z = x + y
```
The program stores `x = 5`, `y = 1`, and `z = 6`.

## Build and Run
Requires a C++17-compatible compiler.
```bash
g++ -std=c++17 -Wall -Wextra -pedantic automatafinals_final.cpp -o automata
./automata
```
On Windows, run `automata.exe` instead.

## Known Limitations
- Expressions must contain whitespace between tokens.
- Supports basic single-line assignments and arithmetic expressions.
- Does not support parentheses, operator precedence, or compound expressions.
- Floating-point arithmetic is unsupported.
- Division uses integer arithmetic.
- This is a regex-based educational parser/evaluator, not a full compiler or explicit DFA/NFA implementation.
- Comprehensive automated testing and handling of all numeric edge cases have not been established.

## Project Contributions
This was a five-member academic group project.

**My role: Lead Developer**

I primarily implemented the tokenization, regex-based expression validation, arithmetic evaluation, and variable storage logic.
Other team members contributed to project coordination, CLI interface design, documentation, diagrams, testing, and presentation.

## Project History
**Original Development:** July 8–14, 2025  
**Recovery and Maintenance:** October 26, 2026  
**Team Size:** 5 members  
**Collaboration Platform:** Discord

Originally developed as a group final project for Automata Theory and Formal Languages. Team coordination, development discussions, and project updates were managed through Discord rather than Git-based version control.

In October 2026, the original C++ source was recovered, reviewed, and placed under Git version control. Bounded correctness fixes were applied to address token counting, floating-point token recognition, and arithmetic error handling.

The October 2026 Git history represents the recovered and maintained version, not the original July 2025 development history.