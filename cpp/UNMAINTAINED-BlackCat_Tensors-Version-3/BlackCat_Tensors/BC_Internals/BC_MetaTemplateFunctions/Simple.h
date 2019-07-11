/*
 * BC_MetaTemplate_Simple.h
 *
 *  Created on: Dec 12, 2017
 *      Author: joseph
 */

#ifndef SIMPLE_H_
#define SIMPLE_H_
namespace BC {
namespace MTF {

		template<bool iff, class THEN, class ELSE>
		struct IF_ELSE {
			using type = THEN;
		};
		template<class THEN, class ELSE>
		struct IF_ELSE<false, THEN, ELSE> {
			using type = ELSE;
		};


		//EQUIVALENT OF ENABLE IF
		template<bool iff, class THEN>
		struct IF;
		template<class THEN>
		struct IF<true, THEN> {
			using type = THEN;
		};

		template<bool iff, class THEN, class ELSE>
		struct IF_NOT_ELSE {
			using type = THEN;
		};
		template<class THEN, class ELSE>
		struct IF_NOT_ELSE<true, THEN, ELSE> {
			using type = ELSE;
		};


namespace INT {
	template<bool iff, int THEN, int ELSE>
	struct IF_ELSE {
		static constexpr int value = THEN;
	};
	template<int THEN, int ELSE>
	struct IF_ELSE<false, THEN, ELSE> {
		static constexpr int value = ELSE;
	};


	//EQUIVALENT OF ENABLE IF
	template<bool iff, int THEN>
	struct IF;
	template<int THEN>
	struct IF<true, THEN> {
		static constexpr int value = THEN;
	};

	template<bool iff, int THEN, int ELSE>
	struct IF_NOT_ELSE {
		static constexpr int value = THEN;
	};
	template<int THEN, int ELSE>
	struct IF_NOT_ELSE<true, THEN, ELSE> {
		static constexpr int value  = ELSE;
	};
}
	template<int...> struct max;
	template<int...> struct min;

	template<int a> struct max<a> { static constexpr int value = a; };
	template<int a> struct min<a> { static constexpr int value = a; };

	template<int a, int... b> struct max<a, b...> { static constexpr int value = a > max<b...>::value ? a : max<b...>::value; };
	template<int a, int... b> struct min<a, b...> { static constexpr int value = a < min<b...>::value ? a : min<b...>::value; };

	template<int ... dims> 		  struct first;
	template<int f, int ... dims> struct first<f, dims...> { static constexpr int value = f; };

	template<bool con> struct isFalse { static constexpr bool conditional = !con;  };
	template<bool con> struct isTRUE  { static constexpr bool conditional = con;  };

	//AND
	template<bool... statements> struct AND;
	template<bool statement> struct AND<statement> { static constexpr bool conditional = statement; };
	template<bool front, bool... statements> struct AND<front, statements...> {
		static constexpr bool conditional = front && AND<statements...>::conditional;
	};

	//OR
	template<bool... statements> struct OR;
	template<bool statement> struct OR<statement> { static constexpr bool conditional = statement; };
	template<bool front, bool... statements> struct OR<front, statements...> {
		static constexpr bool conditional = front || OR<statements...>::conditional;
	};

	//AND IF
	template<class T, bool... statements> struct AND_IF;
	template<class T, bool front, bool... statements> struct AND_IF<T, front, statements...> {
		static constexpr bool conditional = front && sizeof...(statements) == 0 ? true : AND<statements...>::conditional;
		using type = typename IF<conditional, T>::type;
	};
	//OR IF
	template<class T, bool... statements> struct OR_IF;
	template<class T, bool front, bool... statements> struct OR_IF<T, front, statements...> {
		static constexpr bool conditional = front || sizeof...(statements) == 0 ? true : OR<statements...>::conditional;
		using type = typename IF<conditional, T>::type;
	};


	//AND IF ELSE
	template<class T, class U, bool... statements> struct AND_IF_ELSE;
	template<class T, class U, bool front, bool... statements> struct AND_IF_ELSE<T, U, front, statements...> {
		static constexpr bool conditional = front && sizeof...(statements) == 0 ? true : AND<statements...>::conditional;
		using type = typename IF<conditional, T>::type;
	};
	//OR IF ELSE
	template<class T, class U, bool... statements> struct OR_IF_ELSE;
	template<class T, class U, bool front, bool... statements> struct OR_IF_ELSE<T, U, front, statements...> {
		static constexpr bool conditional = front || sizeof...(statements) == 0 ? true : OR<statements...>::conditional;
		using type = typename IF<conditional, T>::type;
	};


	template<int a, int b> struct isEqual 		  {	static constexpr bool conditional = a == b; };
	template<int a, int b> struct isGreaterThan   {	static constexpr int  value = a > b ? a : b;
												 	static constexpr bool conditional = a > b ? true : false; };
	template<int a, int b> struct isLessThan      { static constexpr int  value = a < b ? a : b;
													static constexpr bool conditional = a < b ? true : false; };

	template<class>struct front;

	template<template<class...> class list, class... set, class first>
	struct front<list<first, set...>>
	{ using type = first; };

	template<class> struct isPrimitive 					{ static constexpr bool conditional = false; };
	template<> struct isPrimitive<bool> 				{ static constexpr bool conditional = true; };
	template<> struct isPrimitive<short> 				{ static constexpr bool conditional = true; };
	template<> struct isPrimitive<unsigned short> 		{ static constexpr bool conditional = true; };
	template<> struct isPrimitive<int> 					{ static constexpr bool conditional = true; };
	template<> struct isPrimitive<unsigned> 			{ static constexpr bool conditional = true; };
	template<> struct isPrimitive<long> 				{ static constexpr bool conditional = true; };
	template<> struct isPrimitive<unsigned long> 		{ static constexpr bool conditional = true; };
	template<> struct isPrimitive<long long> 			{ static constexpr bool conditional = true; };
	template<> struct isPrimitive<unsigned long long> 	{ static constexpr bool conditional = true; };
	template<> struct isPrimitive<char> 				{ static constexpr bool conditional = true; };
	template<> struct isPrimitive<unsigned char>		{ static constexpr bool conditional = true; };
	template<> struct isPrimitive<float> 				{ static constexpr bool conditional = true; };
	template<> struct isPrimitive<double> 				{ static constexpr bool conditional = true; };
	template<> struct isPrimitive<long double> 			{ static constexpr bool conditional = true; };
	template<> struct isPrimitive<wchar_t> 				{ static constexpr bool conditional = true; };

	//Remove modifiers
	template<class T> struct remove_mods 	  { using type = T; };
	template<class T> struct remove_mods<T&>  { using type = typename remove_mods<T>::type; };
	template<class T> struct remove_mods<T&&> { using type = typename remove_mods<T>::type; };
	template<class T> struct remove_mods<T*>  { using type = typename remove_mods<T>::type; };

	template<int...> struct sum;
	template<int first			  > struct sum<first		> { static constexpr int value = first; };
	template<int first, int... set> struct sum<first, set...> { static constexpr int value = first + sum<set...>::value; };
	}
}
#endif /* SIMPLE_H_ */
