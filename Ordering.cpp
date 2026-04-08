/* Citation and Sources...
Final Project Milestone 5_3
Filename: Ordering.cpp
Author: Zara Mazhar, StNo: 106537251, Email: zmazhar1@myseneca.ca
Revision History:
Ordering.cpp is done in one sitting.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
*/


#include "Ordering.h"
#include "Menu.h"
#include "Utils.h"
#include <fstream>
#include <iomanip>
using namespace std;
namespace seneca {
	void Ordering::printBillTitle(std::ostream& outputStream)const {
		outputStream << "Bill # " << setw(3) << setfill('0') << m_currentBillNumber << " =============================" << endl;
		outputStream << setfill(' ');


	}
	void Ordering::printTotals(std::ostream& outputStream, double currentBillSubTotal) const {
		double calculatedTax = currentBillSubTotal * Tax;
		double totalWithTax = currentBillSubTotal + calculatedTax;
		outputStream << fixed << setprecision(2);
		outputStream << "                     Total: " << setw(12) << currentBillSubTotal << endl;
		outputStream << "                     Tax:  " << setw(12) << calculatedTax << endl;
		outputStream << "                     Total+Tax:" << setw(9) << totalWithTax << endl;
		outputStream << "========================================" << endl;
	}
	size_t Ordering::countRecords(const char* dataFileName) const {
		size_t newLineCounter = 0;
		char currentCharacter{};
		ifstream openedDataFile(dataFileName);
		while (openedDataFile) {
			openedDataFile.get(currentCharacter);
			if (openedDataFile && currentCharacter == '\n') {
				newLineCounter++;
			}
		}return newLineCounter;
	}
	Ordering::Ordering(const char* drinkDataFileName, const char* foodDataFileName) :m_noOfFoodItems(0),
		m_noOfDrinkItems(0)
		, m_noOfBillItems(0)
		, m_currentBillNumber(1)
		, m_foodItems(nullptr)
		, m_drinkItems(nullptr) {
		for (size_t i = 0; i < MaximumNumberOfBillItems; i++) {
			m_billItems[i] = nullptr;
		}
		size_t countedDrinkRecords = countRecords(drinkDataFileName);
		size_t countedFoodRecords = countRecords(foodDataFileName);
		ifstream drinkFileStream(drinkDataFileName);
		ifstream foodFileStream(foodDataFileName);
		if (drinkFileStream && foodFileStream && countedDrinkRecords > 0 && countedFoodRecords > 0) {
			m_drinkItems = new Drink[countedDrinkRecords];
			m_foodItems = new Food[countedFoodRecords];
			size_t successfullyLoadedDrinks = 0;
			size_t successfullyLoadedFoods = 0;

			while (successfullyLoadedDrinks < countedDrinkRecords && m_drinkItems[successfullyLoadedDrinks].read(drinkFileStream))
			{
				successfullyLoadedDrinks++;
			}
			while (successfullyLoadedFoods < countedFoodRecords && m_foodItems[successfullyLoadedFoods].read(foodFileStream)) {
				successfullyLoadedFoods++;
			}
			if (successfullyLoadedDrinks == countedDrinkRecords && successfullyLoadedFoods == countedFoodRecords) {
				m_noOfDrinkItems = (unsigned int)successfullyLoadedDrinks;
				m_noOfFoodItems = (unsigned int)successfullyLoadedFoods;
			}
			else {
				delete[] m_drinkItems;
				delete[] m_foodItems;
				m_drinkItems = nullptr;
				m_foodItems = nullptr;
			}
		}
	} Ordering::~Ordering() {
		delete[] m_foodItems;
		delete[] m_drinkItems;
		for (unsigned int i = 0; i < m_noOfBillItems; i++) {
			delete m_billItems[i];
			m_billItems[i] = nullptr;
		}
	}
	Ordering::operator bool() const {
		return m_foodItems != nullptr && m_drinkItems != nullptr;
	}
	
	unsigned int Ordering::noOfBillItems() const {
		return m_noOfBillItems;
	}
	bool Ordering::hasUnsavedBill() const {
		return m_noOfBillItems > 0;
	}

	void Ordering::listFoods() const {

		cout << "List Of Avaiable Meals" << endl;
		cout << "========================================" << endl;
		for (unsigned int currentFoodIndex = 0; currentFoodIndex < m_noOfFoodItems; currentFoodIndex++) {
			m_foodItems[currentFoodIndex].print(cout) << endl;
		}
		cout << "========================================" << endl;
	}
	void Ordering::listDrinks() const {
		cout << "List Of Avaiable Drinks" << endl;
		cout << "========================================" << endl;
		for (unsigned int currentDrinkIndex = 0; currentDrinkIndex < m_noOfDrinkItems; currentDrinkIndex++) {
			m_drinkItems[currentDrinkIndex].print(cout) << endl;
		}
		cout << "========================================" << endl;
	}
	void Ordering::orderFood() {
		if (!*this || m_noOfBillItems >= MaximumNumberOfBillItems) return;
		Menu foodSelectionMenu("Food Menu", "Back to Order", 2);
		for (unsigned int currentFoodIndex = 0; currentFoodIndex < m_noOfFoodItems; currentFoodIndex++) {
			foodSelectionMenu << (const char*)m_foodItems[currentFoodIndex];
		}
		size_t selectedFoodIndex = foodSelectionMenu.select();
		if (selectedFoodIndex != 0) {
			Billable* newlyCreatedFoodOrder = new Food(m_foodItems[selectedFoodIndex - 1]);
			if (newlyCreatedFoodOrder->order()) {
				m_billItems[m_noOfBillItems] = newlyCreatedFoodOrder;
				m_noOfBillItems++;
			}
			else {
				delete newlyCreatedFoodOrder;
			}
		}
	}
	void Ordering::orderDrink() {
		if (!*this || m_noOfBillItems >= MaximumNumberOfBillItems) return;
		Menu drinkSelectionMenu("Drink Menu", "Back to Order", 2);
		for (unsigned int currentDrinkIndex = 0; currentDrinkIndex < m_noOfDrinkItems; currentDrinkIndex++) {
			drinkSelectionMenu << (const char*)m_drinkItems[currentDrinkIndex];
		}
		size_t selectedDrinkIndex = drinkSelectionMenu.select();
		if (selectedDrinkIndex != 0) {
			Billable* newlyCreatedDrinkOrder = new Drink(m_drinkItems[selectedDrinkIndex - 1]);
			if (newlyCreatedDrinkOrder->order()) {
				m_billItems[m_noOfBillItems] = newlyCreatedDrinkOrder;
				m_noOfBillItems++;
			}
			else {
				delete newlyCreatedDrinkOrder;
			}
		}
	}
	void Ordering::printBill(std::ostream& outputStream)const {
		double currentBillSubTotal = 0.0;
		printBillTitle(outputStream);
		for (unsigned int currentBillItemIndex = 0; currentBillItemIndex < m_noOfBillItems; currentBillItemIndex++) {
			m_billItems[currentBillItemIndex]->print(outputStream) << endl;
			currentBillSubTotal += m_billItems[currentBillItemIndex]->price();
		}
		printTotals(outputStream, currentBillSubTotal);

	}
	void Ordering::resetBill() {
		char generatedBillFileName[21]{};
		ut.makeBillFileName(generatedBillFileName, m_currentBillNumber);
		ofstream savedBillFile(generatedBillFileName);
		printBill(savedBillFile);
		cout << "Saved bill number " << m_currentBillNumber << endl;
		cout << "Starting bill number " << (m_currentBillNumber + 1) << endl;
		for (unsigned int currentBillItemIndex = 0; currentBillItemIndex < m_noOfBillItems; currentBillItemIndex++) {
			delete m_billItems[currentBillItemIndex];
			m_billItems[currentBillItemIndex] = nullptr;
		}
		m_currentBillNumber++;
		m_noOfBillItems = 0;
	}
}