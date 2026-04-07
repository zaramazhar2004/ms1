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
Menu mainMenu("Seneca Restaurant", "End Program");
mainMenu << "Order";
mainMenu << "Print Bill";
mainMenu << "Start a New Bill";
mainMenu << "List Foods";
mainMenu << "List Drinks";
size_t menuSelection{};
while ((menuSelection = mainMenu.select()) != 0) {
	switch (menuSelection) {
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

