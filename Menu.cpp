/* Citation and Sources...
Final Project Milestone 2
Filename: Menu.cpp
Author: Zara Mazhar, StNo: 106537251, Email: zmazhar1@myseneca.ca
Revision History: Done in one sitting (March 13)
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
		m_contents = nullptr;
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
	//allocating their functions
Menu::Menu(const char* menuTitle, const char* exit, size_t indent, size_t isize)
	: m_indent(indent), m_isize(isize), m_numOfItems(0), m_menuTitle(menuTitle, indent, isize, -1), m_exit(exit, indent, isize, 0), m_selectPrompt("> ", indent, isize, -1) {

	for (size_t i = 0; i < MaximumNumberOfMenuItems; i++) {
		m_items[i] = nullptr;	//making sure all pointers are safe
	}
}
Menu::~Menu() {
	for (size_t i = 0; i < MaximumNumberOfMenuItems; i++) {
		delete m_items[i];		// deleting each MenuItem object and resetting pointer 
		m_items[i] = nullptr;
	}
}
void Menu::displayAll() {
	if (m_menuTitle) {
		m_menuTitle.display() << endl;		//first priting menu title
	}
	for (size_t i = 0; i < m_numOfItems; i++) {
		m_items[i]->display() << endl;		//then printeing all added items one at a time
	}
	m_exit.display() << endl;		//printing exit and the end prompt
	m_selectPrompt.display();
}
Menu& Menu::operator<<(const char* content) {
	if (m_numOfItems < MaximumNumberOfMenuItems) {	// checking before adding to make sure array is not full yet
		m_items[m_numOfItems] = new MenuItem(content, m_indent, m_isize, int(m_numOfItems + 1));
		m_numOfItems++;		//row number allocating each next one will be count + 1
	}
	return *this;		//returns that current menu for chaining to work
}
size_t Menu::select() const {
	const_cast<Menu*>(this)->displayAll();		//showing full menu and valid choices 
	return ut.getInt(0, (int)m_numOfItems);
}
size_t operator<<(ostream& ostr, const Menu& menu) {
	if (&ostr == &cout) {
		return menu.select();
	}
	return 0;		//if not cout then do nothing and return 0
}
}
