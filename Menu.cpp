/* Citation and Sources...
Final Project Milestone 1
Filename: Menu.cpp
Author: Zara Mazhar, StNo: 106537251, Email: zmazhar1@myseneca.ca
Revision History: Done in one sitting 
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
*/

#include "Menu.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
using namespace std;

namespace seneca {
	//setting objects to safe empty states so they dont fail the checks
	void MenuItem::setEmpty() {
		m_contents =nullptr;
		m_indent = 0;
		m_isize = 0;
		m_row = -1;
	}
	//same cosntructor 
	MenuItem::MenuItem(const char* contents, size_t indent, size_t isize, int row) {
		setEmpty();	//start object but safe state
		bool valid = true;	//assuming for loop 
		// if/else statemts to invalid liek whitespaces or null pointers or side exceeding 4 and according to MaximumNumberOfMenuItems
	
		if (contents == nullptr) {
			valid = false;
		}
		else if (ut.isspace(contents)) {
			valid = false;
		}
		else if (indent > 4 || isize > 4) {
			valid = false;
		}
		else if (row > (int)MaximumNumberOfMenuItems) {
			valid = false;
		}
		//If evrything passes then store the vakues
		if (valid) {
			ut.alocpy(m_contents, contents);	// using the provided function
			m_indent = indent;
			m_isize = isize;
			m_row = row;
		}
	}
		//destructor releases memory 
	MenuItem::~MenuItem() {
		delete[] m_contents;
	}
	// usinga  bool conversion operator to see if content is existing then object becomes valid 
	MenuItem::operator bool() const {
		return m_contents != nullptr;
	}
	// print statements 
	ostream& MenuItem::display(ostream& ostr)const {
		if (!m_contents) {
			ostr << "??????????";
		}
		else {
			for (size_t i = 0; i < m_indent * m_isize; i++) {
				ostr << ' ';
			}
			if (m_row >= 0) {
				ostr << setw(2) << m_row << "- ";

			}
			const char* p = m_contents;
			while (*p && ut.isspace(*p)) {	// this is to not add any whitepace characters 
				p++;
			}
			ostr << p;
		}
		return ostr;   // returning stream to allow confiscading
	}

}
