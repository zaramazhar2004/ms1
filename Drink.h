/* Citation and Sources...
Final Project Milestone 5_6
Filename: Drink.h
Author: Zara Mazhar, StNo: 106537251, Email: zmazhar1@myseneca.ca
Revision History:
Drink.h is done in one sitting.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
*/
#ifndef SENECA_DRINK_H
#define SENECA_DRINK_H
#include "Billable.h"
namespace seneca {
	class Drink :public Billable {
		char m_size{};
	public: Drink();
		  virtual std::ostream& print(std::ostream& output = std::cout) const override;
		  virtual bool order() override;
		  virtual bool ordered() const override;
		  virtual std::ifstream& read(std::ifstream& input) override;
		  virtual double price()const override;
	
	
	};
}
#endif 