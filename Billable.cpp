/* Citation and Sources...
Final Project Milestone 3
Filename: Billable.cpp
Author: Zara Mazhar, StNo: 106537251, Email: zmazhar1@myseneca.ca
Revision History:
Billable.cpp is done in one sitting.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
*/
#include "Billable.h"
#include "Utils.h"
namespace seneca {
	Billable::Billable() :m_name(nullptr), m_price(0) {
	}
	Billable::Billable(const Billable& src) :m_name(nullptr), m_price(src.m_price) {
		ut.alocpy(m_name, src.m_name);
		}
	Billable& Billable::operator=(const Billable& src){
		if (this != &src) {
			ut.alocpy(m_name, src.m_name);
			m_price = src.m_price;
		}
		return *this;
	}
	Billable::~Billable() {
		delete[]m_name;
	}
		void Billable::price(double p) {
			m_price = p;
		}
		void Billable::name(const char* itemName) {
			ut.alocpy(m_name, itemName);
		}
		double Billable::price()const {
			return m_price;
		}
		Billable::operator const char* ()const {
			return m_name;

		}
		double operator+(double total, const Billable& obj) {
			return total + obj.price();
		}
		double& operator+=(double& total, const Billable& obj) {
			total += obj.price();
			return total;

		}
		std::ostream& operator<<(std::ostream& out, const Billable& obj) {
			return out << (const char*)obj;
		}
	}




