#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Calculate Simple Moving Average
double calculateSMA(double prices[], int start, int window)
{
    double sum = 0;

    for (int i = start; i < start + window; i++)
    {
        sum += prices[i];
    }

    return sum / window;
}

// Calculate Linear Regression Slope
double calculateSlope(double prices[], int start, int window)
{
    double sumX = 0;
    double sumY = 0;
    double sumXY = 0;
    double sumX2 = 0;

    for (int i = 0; i < window; i++)
    {
        double x = i + 1;
        double y = prices[start + i];

        sumX += x;
        sumY += y;
        sumXY += x * y;
        sumX2 += x * x;
    }

    double denominator =
        window * sumX2 - sumX * sumX;

    if (denominator == 0)
    {
        return 0;
    }

    return (window * sumXY - sumX * sumY) /
           denominator;
}

// Generate BUY, SELL or HOLD signal
string generateSignal(double currentPrice,
                      double movingAverage,
                      double slope)
{
    if (currentPrice > movingAverage && slope > 0)
    {
        return "BUY";
    }
    else if (currentPrice < movingAverage && slope < 0)
    {
        return "SELL";
    }
    else
    {
        return "HOLD";
    }
}

// Backtest one Moving Average window
double backtest(double prices[],
                int n,
                int window,
                int &totalTrades,
                int &winningTrades,
                int &losingTrades,
                double &totalProfit,
                double &totalLoss)
{
    double initialBalance = 10000;
    double balance = initialBalance;

    bool holding = false;
    double buyPrice = 0;

    totalTrades = 0;
    winningTrades = 0;
    losingTrades = 0;
    totalProfit = 0;
    totalLoss = 0;

    for (int i = window - 1; i < n; i++)
    {
        double movingAverage =
            calculateSMA(
                prices,
                i - window + 1,
                window
            );

        double slope =
            calculateSlope(
                prices,
                i - window + 1,
                window
            );

        string signal =
            generateSignal(
                prices[i],
                movingAverage,
                slope
            );

        // BUY
        if (signal == "BUY" && !holding)
        {
            holding = true;
            buyPrice = prices[i];
        }

        // SELL
        else if (signal == "SELL" && holding)
        {
            double profitLoss =
                prices[i] - buyPrice;

            totalTrades++;

            if (profitLoss > 0)
            {
                winningTrades++;
                totalProfit += profitLoss;
            }
            else
            {
                losingTrades++;
                totalLoss += profitLoss;
            }

            balance += profitLoss;
            holding = false;
        }
    }

    // Close remaining position
    if (holding)
    {
        double profitLoss =
            prices[n - 1] - buyPrice;

        totalTrades++;

        if (profitLoss > 0)
        {
            winningTrades++;
            totalProfit += profitLoss;
        }
        else
        {
            losingTrades++;
            totalLoss += profitLoss;
        }

        balance += profitLoss;
    }

    return balance;
}

int main()
{
    // Same historical data used in Week 3
    const int n = 30;

    double prices[n] =
    {
        100, 102, 101, 103, 105,
        107, 106, 108, 110, 112,
        111, 109, 107, 105, 103,
        104, 106, 108, 111, 114,
        116, 115, 117, 119, 121,
        120, 118, 116, 114, 117
    };

    double initialBalance = 10000;

    // Parameters to optimize
    int minimumWindow = 3;
    int maximumWindow = 10;

    double bestBalance = initialBalance;
    double bestProfit = -999999;
    int bestWindow = 0;

    int bestTrades = 0;
    int bestWinningTrades = 0;
    int bestLosingTrades = 0;

    double bestTotalProfit = 0;
    double bestTotalLoss = 0;

    cout << "============================================================\n";
    cout << "        WEEK 4 - TRADING STRATEGY OPTIMIZATION\n";
    cout << "============================================================\n";

    cout << "\nInitial Balance: Rs. "
         << fixed << setprecision(2)
         << initialBalance << endl;

    cout << "\nTesting Moving Average Windows: "
         << minimumWindow << " to "
         << maximumWindow << endl;

    cout << "\n------------------------------------------------------------\n";

    cout << left
         << setw(10) << "Window"
         << setw(15) << "Trades"
         << setw(15) << "Wins"
         << setw(15) << "Losses"
         << setw(18) << "Net Profit"
         << setw(15) << "Return"
         << endl;

    cout << "------------------------------------------------------------\n";

    // Test every Moving Average window
    for (int window = minimumWindow;
         window <= maximumWindow;
         window++)
    {
        int totalTrades;
        int winningTrades;
        int losingTrades;

        double totalProfit;
        double totalLoss;

        double finalBalance =
            backtest(
                prices,
                n,
                window,
                totalTrades,
                winningTrades,
                losingTrades,
                totalProfit,
                totalLoss
            );

        double netProfit =
            finalBalance - initialBalance;

        double returnPercentage =
            (netProfit / initialBalance) * 100;

        cout << left
             << setw(10) << window
             << setw(15) << totalTrades
             << setw(15) << winningTrades
             << setw(15) << losingTrades
             << "Rs. "
             << setw(13) << netProfit
             << returnPercentage << "%"
             << endl;

        // Select best parameter
        if (netProfit > bestProfit)
        {
            bestProfit = netProfit;
            bestBalance = finalBalance;
            bestWindow = window;

            bestTrades = totalTrades;
            bestWinningTrades = winningTrades;
            bestLosingTrades = losingTrades;

            bestTotalProfit = totalProfit;
            bestTotalLoss = totalLoss;
        }
    }

    // Calculate best strategy metrics
    double bestWinRate = 0;

    if (bestTrades > 0)
    {
        bestWinRate =
            ((double)bestWinningTrades / bestTrades) * 100;
    }

    double bestReturn =
        ((bestBalance - initialBalance)
         / initialBalance) * 100;

    // Display optimization results
    cout << "\n============================================================\n";
    cout << "              OPTIMIZATION RESULTS\n";
    cout << "============================================================\n";

    cout << "Best Moving Average Window : "
         << bestWindow << endl;

    cout << "Initial Balance            : Rs. "
         << initialBalance << endl;

    cout << "Best Final Balance         : Rs. "
         << bestBalance << endl;

    cout << "Total Trades               : "
         << bestTrades << endl;

    cout << "Winning Trades             : "
         << bestWinningTrades << endl;

    cout << "Losing Trades              : "
         << bestLosingTrades << endl;

    cout << "Total Profit               : Rs. "
         << bestTotalProfit << endl;

    cout << "Total Loss                 : Rs. "
         << bestTotalLoss << endl;

    cout << "Best Net Profit/Loss       : Rs. "
         << bestProfit << endl;

    cout << "Win Rate                   : "
         << bestWinRate << "%" << endl;

    cout << "Return                     : "
         << bestReturn << "%" << endl;

    cout << "============================================================\n";

    cout << "\nOptimization Method:\n";
    cout << "The program tested Moving Average windows from "
         << minimumWindow << " to "
         << maximumWindow << ".\n";

    cout << "The window producing the highest net profit "
         << "was selected as the best parameter.\n";

    cout << "\nNote: This optimization is for educational purposes only.\n";
    cout << "Past or simulated performance does not guarantee future results.\n";

    return 0;
}
