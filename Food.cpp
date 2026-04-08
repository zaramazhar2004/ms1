/* Citation and Sources...
Final Project Milestone 5_5
Filename: Food.cpp
Author: Zara Mazhar, StNo: 106537251, Email: zmazhar1@myseneca.ca
Revision History:
Food.cpp is done in one sitting.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
*/

#include "Food.h"
#include "Menu.h"
#include "Utils.h"
#include <iomanip>
using namespace std;
namespace seneca {
Food::Food() {
	m_ordered = false;
	m_child = false;
	m_customize = nullptr;
	}
Food::Food(const Food& copiedFood) : Billable(copiedFood) {
	m_ordered = copiedFood.m_ordered;
	m_child = copiedFood.m_child;
	m_customize = nullptr;
	ut.alocpy(m_customize, copiedFood.m_customize);
}

Food& Food::operator=(const Food& copiedFood) {
	if (this != &copiedFood) {
		Billable::operator=(copiedFood);
		m_ordered = copiedFood.m_ordered;
		m_child = copiedFood.m_child;
		ut.alocpy(m_customize, copiedFood.m_customize);
	}
	return *this;

}
Food::~Food() {
	delete[] m_customize;

}
std::ostream& Food::print(std::ostream& displayStream) const {
	if ((const char*)(*this)) {
		displayStream << left << setw(28) << setfill('.') << (const char*)(*this);
		if (ordered()) {
			if (m_child)
				displayStream << "Child";
			else displayStream << "Adult";

		}
		else {
			displayStream << ".....";
		}
		displayStream << right << setw(7) << setfill(' ') << fixed << setprecision(2) << price();
		if (&displayStream == &cout && m_customize) {
			displayStream << " >> " << m_customize;

		}


	}
	return displayStream;
}
bool Food::order() {
	Menu portionSelectionMenu("Food Size Selection", "Back", 3);
	portionSelectionMenu << "Adult" << "Child";
	size_t selectedPortion= portionSelectionMenu.select();
	if (selectedPortion == 1) {
		m_child = false;
		m_ordered = true;
	}
	else if (selectedPortion == 2) {
		m_child = true;
		m_ordered = true;
	}
	else {
		m_ordered = false;
		delete[] m_customize;
		m_customize = nullptr;
	}
	if (m_ordered) {
		char specialRequestBuffer[256]{};
		cout << "Special instructions" << endl;
		cout << "> ";
		cin.getline(specialRequestBuffer, 256);
		if (specialRequestBuffer[0] != '\0') {
			ut.alocpy(m_customize, specialRequestBuffer);
		}
		else {
			delete[] m_customize;
			m_customize = nullptr;
		}


	}
	return ordered();


}
bool Food::ordered() const {
	return m_ordered;
}
ifstream& Food::read(ifstream& foodDataFile) {
	char parsedFoodName[256]{};
	double parsedBasedPrice{};
	foodDataFile.getline(parsedFoodName, 256, ',');
	foodDataFile >> parsedBasedPrice;
	foodDataFile.ignore(1000, '\n');
	if (foodDataFile) {
		name(parsedFoodName);
		Billable::price(parsedBasedPrice);
		m_child = false;
		m_ordered = false;
		delete[] m_customize;
		m_customize = nullptr;
	}
	return foodDataFile;

}
double Food::price() const {
	double originalBasePrice = Billable::price();
	if (ordered() && m_child) {
		return originalBasePrice / 2;
	}
	return originalBasePrice;
}



}