/* Citation and Sources...
Final Project Milestone 5_3
Filename: Drink.cpp
Author: Zara Mazhar, StNo: 106537251, Email: zmazhar1@myseneca.ca
Revision History:
Drink.cpp is done in one sitting.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
*/

#include "Drink.h"
#include "Menu.h"
#include <iomanip>
using namespace std;
namespace seneca {
	Drink::Drink() :m_size('\0') {
	}
	ostream& Drink::print(ostream& output) const {
		if ((const char*)(*this)) {
			output << left << setw(28) << setfill('.') << (const char*)(*this);

			if (ordered()) {
				switch (m_size) {
				case 'S':
					output << "SML..";
					break;
				case 'M':
					output << "MID..";
					break;
				case 'L':
					output << "LRG..";
					break;
				case 'X':
					output << "XLR..";
					break;
				}
			}
			else {
				output << ".....";
			}

			output << right << setw(7) << setfill(' ') << fixed << setprecision(2) << price();
		}
		return output;
	}
	bool Drink::order() {
		Menu drinkMenu("Drink Size Selection", "Back", 3);
		drinkMenu << "Small" << "Medium" << "Larg" << "Extra Large";
		size_t choice = drinkMenu.select();
		switch (choice) {
		case 1:
			m_size = 'S';
			break;
		case 2:
			m_size = 'M';
			break;
		case 3:
			m_size = 'L';
			break;
		case 4:
			m_size = 'X';
			break;
		default:
			m_size = '\0';
		}
		return ordered();
	}
	bool Drink::ordered() const {
	return m_size != '\0';
}
	ifstream& Drink::read(ifstream& input) {
		char tempName[256]{};
		double tempPrice{};
		input.getline(tempName, 256, ',');
		input >> tempPrice;
		input.ignore(1000, '\n');
		if (input) {
			Billable::name(tempName);
			Billable::price(tempPrice);
			m_size = '\0';
		}
		return input;

	}

	double Drink::price() const {
		double originalPrice = Billable::price();
		switch (m_size) {
		case'S':
			return originalPrice / 2;
		case'M':
			return originalPrice * 0.75;
		case'X':
			return originalPrice * 1.5;
		default:
			return originalPrice;
		}
	}
}
