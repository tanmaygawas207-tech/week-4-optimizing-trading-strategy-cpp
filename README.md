# Week 4 - Optimizing Trading Strategy using C++

## 📌 Project Overview

This project is part of the **YuvaIntern Virtual Internship – Week 4 task**.

The objective of this project is to optimize the trading strategy developed in the previous weeks by testing different **Moving Average window sizes** and selecting the parameter that provides the best trading performance.

The strategy uses:

* Simple Moving Average (SMA)
* Linear Regression Slope
* BUY, SELL and HOLD signals
* Backtesting
* Profit/Loss calculation
* Parameter optimization

---

## 🎯 Objectives

* Optimize the existing trading strategy.
* Test different Moving Average window sizes.
* Compare the performance of each parameter.
* Calculate profit/loss and return.
* Select the best-performing parameter.
* Improve the trading strategy using C++.

---

## 📊 Trading Strategy

The strategy combines two indicators:

### 1. Simple Moving Average

SMA calculates the average price over a specified number of observations.

**Formula:**

```text
SMA = Sum of Prices / Number of Prices
```

### 2. Linear Regression Slope

Linear Regression is used to identify the direction of the price trend.

* Positive slope → Upward trend
* Negative slope → Downward trend

### Trading Rules

```text
If Price > Moving Average AND Slope > 0
        → BUY

If Price < Moving Average AND Slope < 0
        → SELL

Otherwise
        → HOLD
```

---

## ⚙️ Optimization Method

The program tests Moving Average window sizes from:

```text
3 to 10
```

For every window, the program performs a backtest and calculates:

* Total Trades
* Winning Trades
* Losing Trades
* Total Profit
* Total Loss
* Net Profit/Loss
* Return Percentage

The parameter with the **highest net profit** is selected as the best parameter.

---

## 📈 Optimization Results

| Window | Trades | Wins | Losses | Net Profit | Return |
| -----: | -----: | ---: | -----: | ---------: | -----: |
|      3 |      3 |    2 |      1 |     Rs. 18 |  0.18% |
|      4 |      2 |    2 |      0 |     Rs. 18 |  0.18% |
|      5 |      2 |    2 |      0 |     Rs. 10 |  0.10% |
|      6 |      2 |    1 |      1 |      Rs. 8 |  0.08% |
|      7 |      2 |    1 |      1 |      Rs. 2 |  0.02% |
|      8 |      2 |    1 |      1 |      Rs. 0 |  0.00% |
|      9 |      2 |    0 |      2 |     Rs. -5 | -0.05% |
|     10 |      2 |    1 |      1 |     Rs. -6 | -0.06% |

### 🏆 Best Parameter

```text
Best Moving Average Window: 3
Initial Balance: Rs. 10,000
Final Balance: Rs. 10,018
Net Profit: Rs. 18
Win Rate: 66.67%
Return: 0.18%
```

Window 3 was selected because it was the **first parameter achieving the highest net profit**.

---

## 💻 Technologies Used

* **Programming Language:** C++
* **Compiler:** GCC / MinGW / Code::Blocks / Visual Studio
* **Concepts:** Arrays, Functions, Loops, Conditional Statements, Linear Regression and Backtesting

---

## 📁 Project Files

```text
week-4-optimizing-trading-strategy-cpp/
│
├── optimized_trading_strategy.cpp
└── README.md
```

---

## ▶️ How to Run

### Step 1

Download or clone the repository.

### Step 2

Compile the C++ program:

```bash
g++ optimized_trading_strategy.cpp -o trading
```

### Step 3

Run the program:

```bash
./trading
```

On Windows:

```bash
trading.exe
```

---

## 📌 Sample Data

The program uses the same historical-style sample data from Week 3:

```text
100, 102, 101, 103, 105,
107, 106, 108, 110, 112,
111, 109, 107, 105, 103,
104, 106, 108, 111, 114,
116, 115, 117, 119, 121,
120, 118, 116, 114, 117
```

Initial balance:

```text
Rs. 10,000
```

---

## 📚 Learning Outcomes

Through this project, I learned:

* How to optimize trading parameters.
* How Moving Average affects trading signals.
* How Linear Regression can identify trends.
* How to perform backtesting.
* How to compare multiple strategy parameters.
* How to calculate trading performance.
* How C++ can be used for quantitative trading simulations.

---

## ⚠️ Disclaimer

This project is created for **educational and internship purposes only**.

The price data and results are simulated/historical-style sample data. The results should not be considered financial advice or a guarantee of future trading performance.

---

## 👨‍💻 Author

**Tanmay Gawas**

**Bachelor of Computer Applications (BCA)**

**YuvaIntern Virtual Internship – Week 4**
