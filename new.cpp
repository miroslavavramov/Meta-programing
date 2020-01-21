#include <iostream>

////////////////////////////////////////////////////////////////////////////
// Pure compile-time calculations using meta programming with C++ templates.
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
// Calculates N!
// The generic version calls recursively until terminated
// by the specialized version for N=0.
template<int N>
struct X {
	enum {
		value = N * X<N-1>::value
	};
};

template<>
struct X<0> {
	enum {
		value = 1
	};
};

////////////////////////////////////////////////////////////////////////////
// Calculates Fibonacci(N)
// Here we have two specializations: one for N=0 and one for N=1.
template<int N>
struct Y {
	enum {
		value = Y<N-1>::value + Y<N-2>::value
	};
};

template<>
struct Y<0> {
	enum {
		value = 0
	};
};

template<>
struct Y<1> {
	enum {
		value = 1
	};
};

////////////////////////////////////////////////////////////////////////////
// Task 1: Finish the following template struct so that
// it will calculate if an integer is a prime number.
//
// The main() function will call this template with the
// values from 2 to 20.
//
// The Ì template argument is a hint :)

template <int p, int i> struct is_prime {
//	std::cout << "p= " << p<<"i= "<<i << std::endl;
	enum {
		prim = (p == 2) ||(p% i) && is_prime <(i> 2? p: 0), i-1> :: prim
	};
};

template <> 
struct is_prime <0,0> {
	enum {
		prim = 1
	}; 
};
template <>
struct is_prime <0,1> {
	enum {
		prim = 1
	}; 
};

template<int N>
struct P {
	enum {
		value = is_prime <N, N-1> :: prim
	};
};
template<>
struct P<2> {
	enum {
		value = 2
	};
};


////////////////////////////////////////////////////////////////////////////
// Combined compile-time and run-time calculation, used just to show how
// weird C++ can be.
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Generates a class that writes the numbers from 1 to N to stdout, one
// number per line.
template<int N>
struct C : public C<N-1> {
	C() : C<N-1>() {
		std::cout << N << std::endl;
	}
};

template<>
struct C<0> {
	C() {
	}
};

////////////////////////////////////////////////////////////////////////////
// Task 2: Write a combined compile-time and run-time meta struct that
// will find the prime numbers between 1 and 30 and print them to stdout,
// one prime number per line.
//
template<unsigned N>
struct PP : public PP<N-1>{
	PP() : PP<N-1>(){
		if(P<N>::value)
			std::cout<< "prime N = "<< N << std::endl;// finish me
	}

	enum {
		value = is_prime <N, N-1> :: prim
	};
};

template<>
struct PP<1> {
	PP() {
	}
	enum {
		value = 1
	};
};

////////////////////////////////////////////////////////////////////////////
// Task 3: Write the numbers from 1 to N to stdout, one number per line.
// If the number is a multiple of 3, write "T" instead.
// If the number is a multiple of 5, write "F" instead.
// If the number is a multiple of both 3 and 5, write "TF" instead.

template<int N>
struct Z : public Z <N-1>{
	Z() : Z <N-1>(){
		if(Z<N>::value3 ==0 && Z<N>::value5 ==0)
			std::cout<< "prime N = "<< N <<"TF"<< std::endl;// finish me
		else if(Z<N>::value3==0)
			std::cout<< "prime N = "<< N <<"T"<< std::endl;// finish me
		else if(Z<N>::value5 ==0)
			std::cout<< "prime N = "<< N <<"F"<< std::endl;// finish me
	}
	enum{
		value3 = N % 3,
		value5 = N % 5
	};
};

template <> 
struct Z <0> {
	enum {
		value = 0
	}; 
};

////////////////////////////////////////////////////////////////////////////

int
main( void )
{
	// Calculate 12!
	std::cout << "4! = " << X<4>::value << std::endl << std::endl;

	// Calculate Fibonacci(22)
	std::cout << "Fibonacci(22) = " << Y<22>::value << std::endl << std::endl;

	// (Task 1) Test prime number calculation from 2 to 20
	std::cout << "2, " << ( P<2>::value ? "true" : "false" ) << std::endl;
	std::cout << "3, " << ( P<3>::value ? "true" : "false" ) << std::endl;
	std::cout << "4, " << ( P<4>::value ? "true" : "false" ) << std::endl;
	std::cout << "5, " << ( P<5>::value ? "true" : "false" ) << std::endl;
	std::cout << "6, " << ( P<6>::value ? "true" : "false" ) << std::endl;
	std::cout << "7, " << ( P<7>::value ? "true" : "false" ) << std::endl;
	std::cout << "8, " << ( P<8>::value ? "true" : "false" ) << std::endl;
	std::cout << "9, " << ( P<9>::value ? "true" : "false" ) << std::endl;
	std::cout << "10, " << ( P<10>::value ? "true" : "false" ) << std::endl;
	std::cout << "11, " << ( P<11>::value ? "true" : "false" ) << std::endl;
	std::cout << "12, " << ( P<12>::value ? "true" : "false" ) << std::endl;
	std::cout << "13, " << ( P<13>::value ? "true" : "false" ) << std::endl;
	std::cout << "14, " << ( P<14>::value ? "true" : "false" ) << std::endl;
	std::cout << "15, " << ( P<15>::value ? "true" : "false" ) << std::endl;
	std::cout << "16, " << ( P<16>::value ? "true" : "false" ) << std::endl;
	std::cout << "17, " << ( P<17>::value ? "true" : "false" ) << std::endl;
	std::cout << "18, " << ( P<18>::value ? "true" : "false" ) << std::endl;
	std::cout << "19, " << ( P<19>::value ? "true" : "false" ) << std::endl;
	std::cout << "20, " << ( P<20>::value ? "true" : "false" ) << std::endl;

	std::cout << std::endl;

	// Run C from 1 to 10
	C<10> c;

	std::cout << std::endl;

	// Run PP from 1 to 30
	PP<30> pp;

	std::cout << std::endl;

	// Run Z from 1 to 32
	Z<15> z;

	return 0;
}
