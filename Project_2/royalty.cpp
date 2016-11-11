#include <iostream>
#include <string>
using namespace std;

int main(){


	//Initialize the variables and take user inputs

	int unitsSold;
	cout << "Units sold: ";
	cin >> unitsSold;
	cin.ignore(10000, '\n');

	string title;
	cout << "Title: ";
	getline(cin, title);

	double salesPrice;
	cout << "Sales price: ";
	cin >> salesPrice;
		
	double expense;
	cout << "Expense: ";
	cin >> expense;
	cin.ignore(10000, '\n');
	
	string premium;
	cout <<	"Premium item? (y/n): ";
	getline(cin, premium);

	cout << "---" << endl;


	//Check for errors with the inputs and print out error message if an error is found

	if(unitsSold < 0){
		cout << "The number of units sold must be nonnegative." << endl;
		return 1;
	}

	if(title == ""){
		cout << "You must enter a title." << endl;
		return 1;
	}

	if(expense < 0){
		cout << "The expense must be nonnegative." << endl;
		return 1;
	}

	if(salesPrice < expense){
		cout << "The sales price must not be less than the expense." << endl;
		return 1;
	}

	if(premium != "y" && premium != "n"){
		cout << "You must enter y or n." << endl;
		return 1;
	}
	

	//Calculate the royalties with the given prices, unitsSold, and premiums

	int unitsLeft = unitsSold;
	double royalties = 0;
	double sellingPrice = salesPrice - expense;
	
	if(unitsLeft >= 300){		//Find royalty for first 300 units or less
		royalties += 300 * .08 * sellingPrice;
		unitsLeft -= 300;
	}
	else{
		royalties += unitsSold * .08 * sellingPrice;
		unitsLeft = 0;
	}

	double percent;				//Find percent of royalty based on if it is premium
	if(premium == "y")
		percent = .14;
	else
		percent = .11;

	if(unitsLeft >=	700){		//Find royalty for next 700 units or less
		royalties += 700 * percent * sellingPrice;
		unitsLeft -= 700;
	}
	else{
		royalties += unitsLeft * percent * sellingPrice;
		unitsLeft = 0;
	}

	if(unitsLeft > 0){			//Find royalty for the rest of the units
		royalties += unitsLeft * .14 * sellingPrice;
		unitsLeft = 0;
	}


	//Set royalties to precision 2 and print out solution.

	cout.setf(ios::fixed);
	cout.precision(2);

	cout << title << " earned $" << royalties << " in royalties." << endl;
}