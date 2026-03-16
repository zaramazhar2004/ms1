/* Citation and Sources...
Final Project Milestone 1
Filename: Menu.h
Author: Zara Mazhar, StNo: 106537251, Email: zmazhar1@myseneca.ca
Revision History: Done in one sitting
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
*/

#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include <iostream>
#include "constants.h"

namespace seneca {
	class Menu;
	class MenuItem {
		friend class Menu;
		char* m_contents{}; //pointer for dynamic memory 
		size_t m_indent{};  //indetation levels controlling 
		size_t m_isize{};	//spaces per indentation
		int m_row{};		//row numbers as int
		void setEmpty();	// using standard helper function for safe empty space

	public:
		MenuItem(const char* contents, size_t indent, size_t isize, int row);	//cosntructor to receive all properties
		~MenuItem();	//freeing dynamic memory according to the rule of three 
		MenuItem(const MenuItem&) = delete;	//preventing copy constructor-end of three rule 
		MenuItem& operator=(const MenuItem&) = delete; //no copy assignment 

		operator bool() const;	//using bool checks for valid and invalid checks
		std::ostream& display(std::ostream& ostr = std::cout) const;	// prints formatted 
	
	};
	class Menu {
		size_t m_indent{};
		size_t m_isize{};
		size_t m_numOfItems{};
		MenuItem m_menuTitle;
		MenuItem m_exit;
		MenuItem m_selectPrompt;
		MenuItem* m_items[MaximumNumberOfMenuItems]{};
		void displayAll();
	public:
		Menu(const char* menuTitle, const char* exit = "Exit", size_t indent = 0, size_t isize = 3);
		~Menu();
		Menu(const Menu&) = delete;
		Menu& operator=(const Menu&) = delete;
		Menu& operator<<(const char* content);
		size_t select() const;
	};
	size_t operator<<(std::ostream& ostr, const Menu& menu);



}
#endif // SENECA_MENU_H
