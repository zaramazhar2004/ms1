/* Citation and Sources...
Final Project Milestone 3
Filename: Billable.h
Author: Zara Mazhar, StNo: 106537251, Email: zmazhar1@myseneca.ca
Revision History:
Billable.h is done in one sitting.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
*/

#ifndef SENECA_BILLABLE_H
#define SENECA_BILLABLE_H
#include <iostream>
#include <fstream>
namespace seneca {
	class Billable {
		char* m_name{};
		double m_price{};
	protected:
		void price(double value);
		void name(const char* name);
	public:
		Billable();
		Billable(const Billable& src);
		Billable& operator=(const Billable& src);
		virtual ~Billable();
		virtual double price() const;
		virtual std::ostream& print(std::ostream& ostr = std::cout) const = 0;
		virtual bool order() = 0;
		virtual bool ordered() const = 0;
		virtual std::ifstream& read(std::ifstream& file) = 0;
		operator const char* () const;
		
	};

	double operator +(double totalMoney, const Billable& B);
	double& operator+=(double& totalMoney, const Billable & B);
	std::ostream& operator<<(std::ostream& ostr, const Billable& B);

}
#endif // !SENECA_BILLABLE_H