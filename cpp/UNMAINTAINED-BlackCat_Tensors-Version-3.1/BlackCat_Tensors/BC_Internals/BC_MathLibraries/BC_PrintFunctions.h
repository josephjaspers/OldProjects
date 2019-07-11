/*
 * BC_PrintFunctions.h
 *
 *  Created on: Jan 8, 2018
 *      Author: joseph
 */

#ifndef BC_PRINTFUNCTIONS_H_
#define BC_PRINTFUNCTIONS_H_

#include <string>
#include <iostream>

namespace BC {

template<typename T, class int_ranks>
static void printHelper(const T ary, const int_ranks ranks, int order, std::string indent, int printSpace) {
	--order;

	if (order > 1) {
		std::cout << indent << "--- --- --- --- --- " << order << " --- --- --- --- ---" << std::endl;
		auto adj_indent = indent + "    "; //add a tab to the index

		for (int i = 0; i < ranks[order]; ++i) {
			printHelper(&ary[i * ranks[order - 1]], ranks, order, adj_indent, printSpace);
		}

		auto gap = std::to_string(order);
		auto str = std::string(" ", gap.length());
		std::cout << indent << "--- --- --- --- --- " << order << " --- --- --- --- ---" << std::endl;

	} else if (order == 1) {
		std::cout << indent << "--- --- --- --- --- " << order << " --- --- --- --- ---" << std::endl;

		for (int j = 0; j < ranks[order - 1]; ++j) {
			std::cout << indent + indent + "[ ";

			for (int i = 0; i < ranks[order]; ++i) {
				//convert to string --- seems to not be working with long/ints?
				auto str = std::to_string(ary[i * ranks[order - 1] + j]);

				//if the string is longer than the printspace truncate it
				str = str.substr(0, str.length() < printSpace ? str.length() : printSpace);

				//if its less we add blanks (so all numbers are uniform in size)
				if (str.length() < printSpace)
					str += std::string(" ", printSpace - str.length());

				//print the string
				std::cout << str;

				//add some formatting fluff
				if (i < ranks[order] - 1)
					std::cout << " | ";

			}
			std::cout << " ]";
			std::cout << std::endl;
		}
	} else {
		std::cout << "[ ";
		for (int i = 0; i < ranks[order]; ++i) {
			//convert to string --- seems to not be working with long/ints?
			auto str = std::to_string(ary[i]);

			//if the string is longer than the printspace truncate it
			str = str.substr(0, str.length() < printSpace ? str.length() : printSpace);

			//if its less we add blanks (so all numbers are uniform in size)
			if (str.length() < printSpace)
				str += std::string(" ", printSpace - str.length());

			//print the string
			std::cout << str;

			//add some formatting fluff
			if (i < ranks[order] - 1)
				std::cout << " | ";
		}
		std::cout << " ]";
	}
}

template<typename T, class RANKS>
static void print(const T ary, const RANKS ranks, int order, int print_length) {
	if (order == 0) {
		std::cout << "[" << ary[0]  << "]" << std::endl;
		return;
	} else if (order == 1) {
		std::cout << "[ ";
		for (int i = 0; i < ranks[0]; ++i) {
			std::cout << ary[i];
			if (i != ranks[0] - 1) {
				std::cout << " | ";
			}
		}
		std::cout << " ]" << std::endl;
		return;
	}

	std::string indent = "";
	printHelper(ary, ranks, order, indent, print_length);
	std::cout << std::endl;
}
template<typename T>
static void print(const T ary, int size, int printSpace) {
	std::cout << "[ ";
	for (int i = 0; i < size; ++i) {
		auto str = std::to_string(ary[i]);
		str = str.substr(0, str.length() < printSpace ? str.length() : printSpace);
		std::cout << str;

		if (i < size - 1) {
			std::cout << " | ";
		}

	}
	std::cout << " ]" << std::endl;

}
template<typename T>
static void print(T ary, int size) {
	print(ary, size, 5);
}
//00000000000000000000000000000000000000000000000000000000
template<typename T, class int_ranks>
static void printHelperSparse(const T ary, const int_ranks ranks, int order, std::string indent, int printSpace) {
	--order;

	if (order > 1) {
		std::cout << indent << "--- --- --- --- --- " << order << " --- --- --- --- ---" << std::endl;
		auto adj_indent = indent + "    "; //add a tab to the index

		for (int i = 0; i < ranks[order]; ++i) {
			printHelperSparse(&ary[i * ranks[order - 1]], ranks, order, adj_indent, printSpace);
		}

		auto gap = std::to_string(order);
		auto str = std::string(" ", gap.length());
		std::cout << indent << "--- --- --- --- --- " << order << " --- --- --- --- ---" << std::endl;

	} else if (order == 1) {
		std::cout << indent << "--- --- --- --- --- " << order << " --- --- --- --- ---" << std::endl;

		for (int j = 0; j < ranks[order - 1]; ++j) {
			std::cout << indent + indent + "[ ";

			for (int i = 0; i < ranks[order]; ++i) {
				//convert to string --- seems to not be working with long/ints?
				auto str = std::to_string(ary[i * ranks[order - 1] + j]);

				//if the string is longer than the printspace truncate it
				str = str.substr(0, str.length() < printSpace ? str.length() : printSpace);

				//if its less we add blanks (so all numbers are uniform in size)
				if (str.length() < printSpace)
					str += std::string(" ", printSpace - str.length());

				//print the string
				if (ary[i * ranks[order - 1] + j] < .0001) {
					for (int x= 0; x < str.length(); ++x) {
						std::cout << " ";
					}
				} else  {
					std::cout << str;
				}

				//add some formatting fluff
				if (i < ranks[order] - 1)
					std::cout << " | ";

			}
			std::cout << " ]";
			std::cout << std::endl;
		}
	} else {
		std::cout << "[ ";
		for (int i = 0; i < ranks[order]; ++i) {
			//convert to string --- seems to not be working with long/ints?
			auto str = std::to_string(ary[i]);

			//if the string is longer than the printspace truncate it
			str = str.substr(0, str.length() < printSpace ? str.length() : printSpace);

			//if its less we add blanks (so all numbers are uniform in size)
			if (str.length() < printSpace)
				str += std::string(" ", printSpace - str.length());

			//print the string
			if (ary[i] < .0001) {
				for (int x= 0; x < str.length(); ++x) {
						std::cout << " ";
					}
			} else
			std::cout << str;

			//add some formatting fluff
			if (i < ranks[order] - 1)
				std::cout << " | ";
		}
		std::cout << " ]";
	}
}

template<typename T, class RANKS>
static void printSparse(const T ary, const RANKS ranks, int order, int print_length) {
	if (order == 0) {
		std::cout << "[" << ary[0]  << "]" << std::endl;
		return;
	} else if (order == 1) {
		std::cout << "[ ";
		for (int i = 0; i < ranks[0]; ++i) {
			if (ary[i] > .0001)
			std::cout << ary[i];
			else {
				std::cout << " ";
			}
			if (i != ranks[0] - 1) {
				std::cout << " | ";
			}
		}
		std::cout << " ]" << std::endl;
		return;
	}

	std::string indent = "";
	printHelperSparse(ary, ranks, order, indent, print_length);
	std::cout << std::endl;
}
template<typename T>
static void printSparse(const T ary, int size, int printSpace) {
	std::cout << "[ ";
	for (int i = 0; i < size; ++i) {
		auto str = std::to_string(ary[i]);
		str = str.substr(0, str.length() < printSpace ? str.length() : printSpace);

		if (ary[i] > .0001)
		std::cout << str;
		else {
			for (int x = 0; x < str.length(); ++x) {
				std::cout << " ";
			}
		}

		if (i < size - 1) {
			std::cout << " | ";
		}

	}
	std::cout << " ]" << std::endl;

}
template<typename T>
static void printSparse(T ary, int size) {
	printSparse(ary, size, 5);
}



}


#endif /* BC_PRINTFUNCTIONS_H_ */
