/* Citation and Sources...
Final Project Milestone 5_3
Filename: Ordering.h
Author: Zara Mazhar, StNo: 106537251, Email: zmazhar1@myseneca.ca
Revision History:
Ordering.h is done in one sitting.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
*/


#ifndef SENECA_ORDERING_H
#define SENECA_ORDERING_H
#include <iostream>
#include "Billable.h"
#include "Food.h"
#include "Drink.h"
#include "constants.h"
namespace seneca {
	class Ordering {
		unsigned int m_noOfFoodItems{};
		unsigned int m_noOfDrinkItems{};
		unsigned int m_noOfBillItems{};
		unsigned int m_currentBillNumber{};
		Food* m_foodItems{};
		Drink* m_drinkItems{};
		Billable* m_billItems[MaximumNumberOfBillItems]{};

		void printBillTitle(std::ostream& outputStream)const;
		void printTotals(std::ostream& outputStream, double currentBillSubTotal) const;
		size_t countRecords(const char* dataFileName)const;
		public:
			Ordering(const char* drinkDataFileName, const char* foodDataFileName);
			~Ordering();
			Ordering(const Ordering&) = delete;
			Ordering& operator=(const Ordering&) = delete;
			operator bool() const;
			unsigned int noOfBillItems() const;
			bool hasUnsavedBill() const;
			void listFoods() const;
			void listDrinks() const;
			void orderFood();
			void orderDrink();
			void printBill(std::ostream& outputStream)const;
			void resetBill();
	};
}




#endif