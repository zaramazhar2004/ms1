/* Citation and Sources...
Final Project Milestone 5_5
Filename: Food.h
Author: Zara Mazhar, StNo: 106537251, Email: zmazhar1@myseneca.ca
Revision History:
Food.h is done in one sitting.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
*/
#ifndef SENECA_FOOD_H
#define SENECA_FOOD_H
#include "Billable.h"
namespace seneca {
	class Food :public Billable {
		bool m_ordered{};
		bool m_child{};
		char* m_customize{};
	public: Food();
		  Food(const Food& source);
		  Food& operator=(const Food& source);
		  virtual ~Food();
		  virtual std::ostream& print(std::ostream& output = std::cout) const override;
		  virtual bool order() override;
		  virtual bool ordered() const override;
		  virtual std::ifstream& read(std::ifstream& input) override;
		  virtual double price()const override;
	};
}
#endif