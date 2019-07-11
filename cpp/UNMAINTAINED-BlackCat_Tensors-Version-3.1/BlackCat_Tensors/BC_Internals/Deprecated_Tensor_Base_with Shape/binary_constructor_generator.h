///*
// * binary_constructor_generator.h
// *
// *  Created on: Jan 3, 2018
// *      Author: joseph
// */
//
//#ifndef BINARY_CONSTRUCTOR_GENERATOR_H_
//#define BINARY_CONSTRUCTOR_GENERATOR_H_
//
//namespace BC {
//
//
///*
// * Get param at index
// */
//template<int, class...>
//struct get_param;
//
//template<int index, class front, class... list> struct get_param<index, front, list...> {
//	using type = typename get_param<index - 1, list...>::type;
//};
//
//template< 			class front, class... list> struct get_param<0, front, list...> {
//	using type = front;
//};
//
//template<class> struct useDefault;
//template< template<class...> class list, class... T> struct useDefault<list<T...>> { static constexpr bool value = sizeof...(T) == 0; };
////0 if false, 1 if true
//template<int, int>
//struct one_if_equal {
//	static constexpr int value = 0;
//};
//template<int A>
//struct one_if_equal<A, A> {
//	static constexpr int value = 1;
//};
//
//template<int, int>
//struct isEqual {
//	static constexpr int value = false;
//};
//template<int A>
//struct isEqual<A, A> {
//	static constexpr int value = true;
//};
//
//class EMPTY {};
//
//template<class param_listA, class param_listB, int param_A_num, int param_B_num, class parentA, class parentB, bool terminate = false, class left_default = void, class right_default = void>
//struct binary_constructor_generator;
//
//template<
//	template<class...>
//	class param_listA, class... A,
//
//	template<class...>
//	class param_listB, class... B,
//
//	int param_posA, int param_posB,
//	class parentA,  class parentB, bool terminate>
//
//struct binary_constructor_generator<param_listA<A...>, param_listB<B...>, param_posA, param_posB, parentA, parentB, terminate>
//	:	virtual public parentA, virtual public parentB, //Inherit from parent A and parent B
//
//	 	public binary_constructor_generator<param_listA<A...>,
//	 									    param_listB<B...>,
//	 									    param_posA + (one_if_equal<param_posB + 1, sizeof...(B)>::value), //if B is at its last element increment the position of A
//	 									    (param_posB + 1) % sizeof...(B),							      //if B is at its last element reset B to its first position
//
//	 									    parentA, parentB,
//
//	 	isEqual<param_posA, sizeof...(A) - 1>::value && isEqual<param_posB, sizeof...(B) - 1>::value>		//if we are at the end of both lists terminate = true (end the loop)
//{
//
//	using parent = binary_constructor_generator<param_listA<A...>, param_listB<B...>,
//			param_posA + (one_if_equal<param_posB + 1, sizeof...(B)>::value), (param_posB + 1) % sizeof...(B), parentA, parentB,
//			isEqual<param_posA, sizeof...(A) - 1>::value && isEqual<param_posB, sizeof...(B) - 1>::value>;
//
//	//inherit all the constructors of binary_constructor_generator
//	using parent::parent;
//
//	binary_constructor_generator(typename get_param<param_posA, A...>::type pA, typename get_param<param_posB, B...>::type pB)
//			: parentA(pA), parentB(pB) {
//
//	}
//
//};
//
//
////Left side specialization for default --------------------------------------------------------
//template<
//	template<class...>
//	class param_listA, class... A,
//
//	template<class...>
//	class param_listB, class... B,
//
//	int param_posA, int param_posB,
//	class parentA,  class parentB, bool terminate, class anyB>
//
//struct binary_constructor_generator<param_listA<A...>, param_listB<B...>, param_posA, param_posB, parentA, parentB, terminate,
//std::enable_if<useDefault<param_listA<A...>>::type, anyB>
//>
//	:	virtual public parentA, virtual public parentB, //Inherit from parent A and parent B
//
//	 	public binary_constructor_generator<param_listA<A...>,
//	 									    param_listB<B...>,
//	 									    param_posA + (one_if_equal<param_posB + 1, sizeof...(B)>::value), //if B is at its last element increment the position of A
//	 									    (param_posB + 1) % sizeof...(B),							      //if B is at its last element reset B to its first position
//
//	 									    parentA, parentB,
//
//	 	isEqual<param_posA, sizeof...(A) - 1>::value && isEqual<param_posB, sizeof...(B) - 1>::value>		//if we are at the end of both lists terminate = true (end the loop)
//{
//
//	using parent = binary_constructor_generator<param_listA<A...>, param_listB<B...>,
//			param_posA + (one_if_equal<param_posB + 1, sizeof...(B)>::value), (param_posB + 1) % sizeof...(B), parentA, parentB,
//			isEqual<param_posA, sizeof...(A) - 1>::value && isEqual<param_posB, sizeof...(B) - 1>::value>;
//
//	//inherit all the constructors of binary_constructor_generator
//	using parent::parent;
//
//	binary_constructor_generator(typename get_param<param_posB, B...>::type pB)
//			: parentB(pB) {
//
//	}
//
//};
//
////Right side specialization for default
//
//template<
//	template<class...>
//	class param_listA, class... A,
//
//	template<class...>
//	class param_listB, class... B,
//
//	int param_posA, int param_posB,
//	class parentA,  class parentB, bool terminate, class anyA>
//
//struct binary_constructor_generator<param_listA<A...>, param_listB<B...>, param_posA, param_posB, parentA, parentB, terminate, anyA,
//std::enable_if<useDefault<param_listB<B...>>::type>
//>
//	:	virtual public parentA, virtual public parentB, //Inherit from parent A and parent B
//
//	 	public binary_constructor_generator<param_listA<A...>,
//	 									    param_listB<B...>,
//	 									    param_posA + (one_if_equal<param_posB + 1, sizeof...(B)>::value), //if B is at its last element increment the position of A
//	 									    (param_posB + 1) % sizeof...(B),							      //if B is at its last element reset B to its first position
//
//	 									    parentA, parentB,
//
//	 	isEqual<param_posA, sizeof...(A) - 1>::value && isEqual<param_posB, sizeof...(B) - 1>::value>		//if we are at the end of both lists terminate = true (end the loop)
//{
//
//	using parent = binary_constructor_generator<param_listA<A...>, param_listB<B...>,
//			param_posA + (one_if_equal<param_posB + 1, sizeof...(B)>::value), (param_posB + 1) % sizeof...(B), parentA, parentB,
//			isEqual<param_posA, sizeof...(A) - 1>::value && isEqual<param_posB, sizeof...(B) - 1>::value>;
//
//	//inherit all the constructors of binary_constructor_generator
//	using parent::parent;
//
//	binary_constructor_generator(typename get_param<param_posA, A...>::type pA)
//			: parentA(pA){
//
//	}
//
//};
//
////RIGHT LEFT Special
//
//
//template<
//	template<class...>
//	class param_listA, class... A,
//
//	template<class...>
//	class param_listB, class... B,
//
//	int param_posA, int param_posB,
//	class parentA,  class parentB, bool terminate>
//
//struct binary_constructor_generator<param_listA<A...>, param_listB<B...>, param_posA, param_posB, parentA, parentB, terminate,
//std::enable_if<useDefault<param_listA<A...>>::type>, std::enable_if<useDefault<param_listB<B...>>::type>
//>
//	:	virtual public parentA, virtual public parentB, //Inherit from parent A and parent B
//
//	 	public binary_constructor_generator<param_listA<A...>,
//	 									    param_listB<B...>,
//	 									    param_posA + (one_if_equal<param_posB + 1, sizeof...(B)>::value), //if B is at its last element increment the position of A
//	 									    (param_posB + 1) % sizeof...(B),							      //if B is at its last element reset B to its first position
//
//	 									    parentA, parentB,
//
//	 	isEqual<param_posA, sizeof...(A) - 1>::value && isEqual<param_posB, sizeof...(B) - 1>::value>		//if we are at the end of both lists terminate = true (end the loop)
//{
//
//	using parent = binary_constructor_generator<param_listA<A...>, param_listB<B...>,
//			param_posA + (one_if_equal<param_posB + 1, sizeof...(B)>::value), (param_posB + 1) % sizeof...(B), parentA, parentB,
//			isEqual<param_posA, sizeof...(A) - 1>::value && isEqual<param_posB, sizeof...(B) - 1>::value>;
//
//	//inherit all the constructors of binary_constructor_generator
//	using parent::parent;
//
//	binary_constructor_generator() = default;
//
//};
//
//
////terminate specialization
//
//template<
//	template<class...>
//	class param_listA, class... A,
//
//	template<class...>
//	class param_listB, class... B,
//
//	int param_posA, int param_posB,
//	class parentA,  class parentB>
//
//struct binary_constructor_generator<param_listA<A...>, param_listB<B...>, param_posA, param_posB, parentA, parentB, true>
//	:	virtual public parentA, virtual public parentB
//{
//
//	//if terminated (have generated all the constructors possible inherit from this now empty class //
//
//};
//
//}
//
//
//#endif /* BINARY_CONSTRUCTOR_GENERATOR_H_ */
