#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//pass in space-delimited arguments when you call the executable
//Example: ./a.out 1 2 3.3
int main( int argc, char * argv[] )
{
	if (argc > 4) 
	{
		cout << "Too many arguments. Cannot pass in more than three." << endl;
		return -1;
	}

	int i = 1;
	double loan_amount, yearly_interest_rate, monthly_payment;

	double arguments [3];

	if (argc > 1)
	{
		while ( i < argc )
		{

			try
			{
				arguments[i-1] = stod(argv[i]);
			}
			catch(const std::invalid_argument&)
			{
				if(i==1)
					cout << "(Invalid loan amount): " << argv[i] << endl;
				else if (i==2)
					cout << "(Invalid interest rate): " << argv[i-1] << " " << argv[i] << endl;
				else
					cout << "(Invalid payment): " << argv[i-2] << " " << argv[i-1] << " " << argv[i] << endl;
				return -2;
			}
			i++;
		}
	}
	if (argc ==1){
		cout << "Loan Amount: ";
		cin >> arguments[0];

		cout << "Interest Rate (% per year): ";
		cin >> arguments[1];

		cout << "Monthly Payments: ";
		cin >> arguments[2];
	}
	loan_amount = arguments[0];
	yearly_interest_rate = arguments[1];
	monthly_payment = arguments[2];
/////////////
//Check for invalid values here (make sure int and positive)
//
//if there is an unexpected value, cout a message and return 0
////////////
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	cout << loan_amount << " " << yearly_interest_rate << " " << monthly_payment << endl;

	double balance = loan_amount;
	double monthly_interest_rate = yearly_interest_rate/12;
	double monthly_interest_paid = 0.0; //money toward interest per month
	double monthly_princicle_paid = 0.0; //money remaining for principle
	
	double total_month = 0; // total month count
	double total_interest_paid = 0.0; // total interest paid for the whole duration of the loan

	const int col1 = 10;
    const int col2 = 15;
    const int col3 = 10;
	const int col4 = 10;
    const int col5 = 10;
    const int col6 = 10;

	//check if monthly payment is enough to cover interest
if ((loan_amount * (monthly_interest_rate/100.0)) > monthly_payment){
	cout << "Generational Debt Type" << endl;
	cout << "monthly interest would be " << (loan_amount * (monthly_interest_rate/100.0)) << endl;
	return 0;
}

////////////////
//Output the beginning of the program


cout << "****************************************************************"<<endl;
cout << "                       Amortization Table"<<endl;
cout << "****************************************************************"<<endl;
std::cout << std::left 
            	<< std::setw(col1) << "Month" 
              	<< std::setw(col2) << "Balance" 
              	<< std::setw(col3) << "Payment"
				<< std::setw(col4) << "Rate" 
              	<< std::setw(col5) << "Interest" 
              	<< std::setw(col6) << "Principal" << "\n";
std::cout << std::left 
            	<< std::setw(col1) << total_month 
              	<< std::setw(col2) << balance 
              	<< std::setw(col3) << "N/A"
				<< std::setw(col4) << "N/A" 
              	<< std::setw(col5) << "N/A" 
              	<< std::setw(col6) << "N/A" << "\n";
///////////////

	while (balance > 0){
		total_month++;
		// get monthly interest pay
		double raw_interest = balance * (monthly_interest_rate/100.0);
		monthly_interest_paid = std::round(raw_interest * 100.0) / 100.0;


		
		double current_payment = monthly_payment;
		if ((balance + monthly_interest_paid) <= current_payment) {
			//Final month
			current_payment = balance + monthly_interest_paid;
			monthly_princicle_paid = balance; // Clamps principal perfectly to remaining balance
			balance = 0.0;
		} else {
			//Regular case
			monthly_princicle_paid = current_payment - monthly_interest_paid;
			balance -= monthly_princicle_paid;
			

			balance = std::round(balance * 100.0) / 100.0;
			if (balance < 0){ balance = 0.0; }
		}

		total_interest_paid += monthly_interest_paid;

		std::cout << std::left 
            	<< std::setw(col1) << total_month 
              	<< std::setw(2) << "$" << std::setw(col2) << balance
              	<< std::setw(2) << "$" << std::setw(col3) << monthly_payment
				<< std::setw(col4) << monthly_interest_rate
              	<< std::setw(2) << "$" << std::setw(col5) << monthly_interest_paid
              	<< std::setw(2) << "$" << std::setw(col6) << monthly_princicle_paid << "\n";
		
	}
	return 0;
}
