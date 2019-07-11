/*
 * BlackCat_IO.h
 *
 *  Created on: Dec 21, 2017
 *      Author: joseph
 */

#ifndef BLACKCAT_IO_H_
#define BLACKCAT_IO_H_

#include <string>
#include <iostream>
#include <cstdio>

namespace BC {
	namespace Printer {
		struct Print;
		struct PrintHandler;
		struct NewLine;
		struct NewLine {
			operator char() {
				return '\n';
			}
			operator std::string() {
				return "\n";
			}
		};

		struct PrintHandler {

			template<class str_cast>
			const PrintHandler& operator ,(const str_cast& string) const {
				std::cout << (string);
				return *this;
			}
			const PrintHandler& operator ,(const NewLine& nl) const {
				std::cout << std::endl;
				return *this;
			}

		};
		struct Print {

			PrintHandler ph;

			template<class str_cast>
			const PrintHandler& operator -(const str_cast& string) const {
				std::cout << static_cast<std::string>(string);
				return ph;
			}
			const PrintHandler& operator -(const NewLine& nl) const {
				std::cout << std::endl;
				return ph;
			}
		};

		static constexpr Print print = Print();
		static constexpr NewLine nl = NewLine();

	}
}
using namespace BC::Printer;

/*
 * This is a simple header that showcases a way to manipulate strings in a manner easier than std::cout
 * It is optimized (not purposed for industrial use) -- This is a class of synctatic sugar
 */


#endif /* BLACKCAT_IO_H_ */
