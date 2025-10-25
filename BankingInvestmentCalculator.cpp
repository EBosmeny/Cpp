#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

class InvestmentCalculator {
private:
	double m_initialInvestment;
	double m_monthlyDeposit;
	double m_annualInterest;
	int m_numYears;

	//validates positive numeric input
	double getPositiveDouble(const string& prompt) {
		double value;
		while (true) {
			cout << prompt;
			cin >> value;

			if (cin.fail() || value < 0) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a positive number." << endl;
			}
			else {
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				return value;
			}
		}
	}

	//validates positive integer input
	int getPositiveInt(const string& prompt) {
		int value;
		while (true) {
			cout << prompt;
			cin >> value;

			if (cin.fail() || value < 0) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a positive whole number." << endl;
			}
			else {
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				return value;
			}
		}
	}

	//method to calculate and display investment growth
	void displayReport(bool withMonthlyDeposits) {
		double balance = m_initialInvestment;
		int totalMonths = m_numYears * 12;

		//display header
		cout << endl;
		if (withMonthlyDeposits) {
			cout << "Balance and Interest With Additional Monthly Deposits" << endl;
		}
		else {
			cout << "Balance and Interest Without Additional Monthly Deposits" << endl;
		}
		cout << string(65, '=') << endl;
		cout << setw(10) << "Year"
			<< setw(30) << "Year End Balance"
			<< setw(25) << "Year End Interest" << endl;
		cout << string(65, '-') << endl;

		// Calculate for each year
		for (int year = 1; year <= m_numYears; year++) {
			double yearInterest = 0.0;

			//calculate every month in the year
			for (int month = 1; month <= 12; month++) {
				double deposit = withMonthlyDeposits ? m_monthlyDeposit : 0.0;
				double monthlyInterest = (balance + deposit) * ((m_annualInterest / 100.0) / 12.0);

				yearInterest += monthlyInterest;
				balance += deposit + monthlyInterest;
			}
			cout << fixed << setprecision(2);
			cout << setw(10) << year
				<< setw(20) << "$" << setw(8) << balance
				<< setw(15) << "$" << setw(8) << yearInterest << endl;
		}
		cout << endl;
	}

public:
	//constructor
	InvestmentCalculator() : m_initialInvestment(0), m_monthlyDeposit(0),
		m_annualInterest(0), m_numYears(0) {}

	//gathering user input
	void getUserInput(){
		cout << string(40, '*') << endl;
		cout << "********** Data Input **********" << endl;

		m_initialInvestment = getPositiveDouble("Initial Investment Amount: $");
		m_monthlyDeposit = getPositiveDouble("Monthly Deposit: $");
		m_annualInterest = getPositiveDouble("Annual Interest Rate (%): ");
		m_numYears = getPositiveInt("Number of Years: ");

		//display entered values
		cout << endl;
		cout << string(40, '*') << endl;
		cout << "********** Investment Summary **********" << endl;
		cout << fixed << setprecision(2);
		cout << "Initial Investment Amount: $" << m_initialInvestment << endl;
		cout << "Monthly Deposit: $" << m_monthlyDeposit << endl;
		cout << "Annual Interest Rate: " << m_annualInterest << "%" << endl;
		cout << "Number of Years: " << m_numYears << endl;
		cout << string(40, '*') << endl;
	}

	//method to generate both reports
	void generateReport() {
		cout << "\nPress any key to continue..." << endl;
		cin.get();

		//displays report without monthly deposits
		displayReport(false);

		// Displays report WITH monthly deposits
		displayReport(true);
	}

	//method to see if user wishes to run another calculation
	bool runAgain() {
		char choice;
		cout << "Would you like to test different values? (y/n): ";
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return (choice == 'y' || choice == 'Y');
	}
};

int main() {
	InvestmentCalculator calculator;
	bool continueRunning = true;

	cout << "===================================" << endl;
	cout << "   Airgead Banking Investment      " << endl;
	cout << "   Growth Calculator               " << endl;
	cout << "===================================" << endl;
	cout << endl;

	while (continueRunning) {
		//ger user input
		calculator.getUserInput();

		//generate and display reports;
		calculator.generateReport();

		//ask if user wants to run again
		continueRunning = calculator.runAgain();

		if (continueRunning) {
			cout << endl << endl;
		}
	}

	cout << "\nThank you for using Airgead Banking's Investment Calculator!" << endl;

	return 0;
}