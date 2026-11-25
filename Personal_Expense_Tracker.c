/*
Project: Personal Expense Tracker
University: UPES, Dehradun
Course: C Programming Lab
Batch: 35
Faculty: Arti Bahuguna Ma'am

Team Members:
Adil Pandole  - 590037391
Srishti Gupta - 590037151
Pulkit Garg   - 590040463
*/

#include <stdio.h>
#include <math.h>

#define MAX 100
#define CATEGORIES 4

struct Expense {
    int category;
    double amount;
};

struct Expense expenses[MAX];

const char *categories[CATEGORIES] = {
    "Food",
    "Travel",
    "Books",
    "Entertainment"
};

double budget = 0;
int count = 0;
int budgetSet = 0;

// Clear invalid input
void clearInput() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// Read a valid positive amount
int readAmount(double *amount) {
    if (scanf("%lf", amount) != 1) {
        clearInput();
        return 0;
    }

    if (!isfinite(*amount) || *amount <= 0 ||
        *amount > 1000000000.0) {
        clearInput();
        return 0;
    }

    return 1;
}

// Calculate total spending
double totalExpenses() {
    double total = 0;

    for (int i = 0; i < count; i++) {
        total += expenses[i].amount;
    }

    return total;
}

// Set monthly budget
void setBudget() {
    double amount;

    printf("\nEnter your monthly budget: Rs. ");

    if (!readAmount(&amount)) {
        printf("Invalid budget amount!\n");
        return;
    }

    budget = amount;
    budgetSet = 1;

    printf("\nBudget set successfully!\n");
}

// Add multiple expenses
void addExpenses() {
    int n, category;
    double amount;

    if (!budgetSet) {
        printf("\nPlease set your budget first!\n");
        return;
    }

    if (count >= MAX) {
        printf("\nExpense storage is full!\n");
        return;
    }

    printf("\nHow many expenses do you want to add? ");

    if (scanf("%d", &n) != 1 ||
        n <= 0 || n > MAX - count) {
        printf("Invalid number of expenses!\n");
        clearInput();
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("\n--------- EXPENSE %d ---------\n", i + 1);

        for (int j = 0; j < CATEGORIES; j++) {
            printf("%d. %s\n", j + 1, categories[j]);
        }

        printf("Select category (1-4): ");

        if (scanf("%d", &category) != 1 ||
            category < 1 || category > CATEGORIES) {
            printf("Invalid category! Try again.\n");
            clearInput();
            i--;
            continue;
        }

        printf("Enter amount: Rs. ");

        if (!readAmount(&amount)) {
            printf("Invalid amount! Try again.\n");
            i--;
            continue;
        }

        expenses[count].category = category - 1;
        expenses[count].amount = amount;
        count++;

        printf("Expense added successfully!\n");

        if (totalExpenses() > budget) {
            printf("WARNING: Budget exceeded!\n");
        }
    }
}

// Display complete expense report
void viewReport() {
    double totals[CATEGORIES] = {0};
    double spent = totalExpenses();
    double remaining = budget - spent;
    int highest = 0;

    if (!budgetSet) {
        printf("\nPlease set your budget first!\n");
        return;
    }

    printf("\n====================================\n");
    printf("           EXPENSE HISTORY\n");
    printf("====================================\n");

    if (count == 0) {
        printf("No expenses recorded yet.\n");
    } else {
        printf("%-6s %-18s %-12s\n",
               "No.", "Category", "Amount");

        for (int i = 0; i < count; i++) {
            printf("%-6d %-18s Rs. %.2f\n",
                   i + 1,
                   categories[expenses[i].category],
                   expenses[i].amount);

            totals[expenses[i].category] += expenses[i].amount;
        }
    }

    printf("\n====================================\n");
    printf("        CATEGORY-WISE SPENDING\n");
    printf("====================================\n");

    for (int i = 0; i < CATEGORIES; i++) {
        printf("%-18s : Rs. %.2f\n",
               categories[i], totals[i]);

        if (totals[i] > totals[highest]) {
            highest = i;
        }
    }

    printf("\n====================================\n");
    printf("            BUDGET SUMMARY\n");
    printf("====================================\n");

    printf("Monthly Budget   : Rs. %.2f\n", budget);
    printf("Total Spending   : Rs. %.2f\n", spent);
    printf("Remaining Budget : Rs. %.2f\n", remaining);
    printf("Budget Used      : %.2f%%\n",
           (spent / budget) * 100);

    if (count > 0) {
        printf("Highest Spending : %s\n",
               categories[highest]);
    } else {
        printf("Highest Spending : None\n");
    }

    printf("------------------------------------\n");

    if (spent > budget) {
        printf("STATUS: BUDGET EXCEEDED!\n");
    } else if (spent == budget) {
        printf("STATUS: BUDGET FULLY USED!\n");
    } else {
        printf("STATUS: WITHIN BUDGET\n");
    }

    printf("====================================\n");
}

// Main function
int main() {
    int choice;

    do {
        printf("\n====================================\n");
        printf("       PERSONAL EXPENSE TRACKER\n");
        printf("====================================\n");

        printf("1. Set Monthly Budget\n");
        printf("2. Add Expenses\n");
        printf("3. View Expense Report\n");
        printf("4. Exit\n");

        printf("------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Enter a number.\n");
            clearInput();
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                setBudget();
                break;

            case 2:
                addExpenses();
                break;

            case 3:
                viewReport();
                break;

            case 4:
                printf("\nThank you for using Expense Tracker!\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 4);

    return 0;
}