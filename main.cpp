
/* Citation and Sources...
Final Project Milestone 5_2
Filename: main.cpp
Author: Zara Mazhar, StNo: 106537251, Email: zmazhar1@myseneca.ca
Revision History:
main.cpp is done in one sitting.
-----------------------------------------------------------
I have done all the coding by myself.
*/

#include <iostream>
#include "Menu.h"
#include "Ordering.h"
using namespace std;
using namespace seneca;
int main() {
	Ordering orderSystem("drinks.csv", "foods.csv");
	if (!orderSystem) {

		cout << "Failed to open data files or the data files are corrupted!" << endl;
		return 1;
	}
Menu mainMenu("Seneca Restaurant ", "End Program");
mainMenu << "Order";
mainMenu << "Print Bill";
mainMenu << "Start a New Bill";
mainMenu << "List Foods";
mainMenu << "List Drinks";
Menu orderingMenu("Order Menu", "Back to main menu", 1);
orderingMenu << "Food";
orderingMenu << "Drink";
Menu menuExit("You have bills that are not saved, are you sue you want to exit?", "No");
menuExit << "Yes";

size_t menuSelection{};
while (true){
	menuSelection = mainMenu.select();
	switch (menuSelection) {
	case 1: {
		size_t orderselection{};
		while ((orderselection = orderingMenu.select()) != 0) {
			if (orderselection == 2) {
				orderSystem.orderDrink();
			}
		}
		break;
	}
	case 0:
		if (orderSystem.hasUnsavedBill()) {
			if (menuExit.select() == 1) {
				return 0;
			}
		}
		else {
			return 0;
		}
		break;

	case 4:
		orderSystem.listFoods();
		break;
	case 5: 
		orderSystem.listDrinks();
		break;

	}
}
return 0;
}

