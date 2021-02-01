/**************************************************/
/*                                                */
/*  Lab 1 Starter file                            */
/*                                                */
/*  Name: Omri Golan                              */
/*  Student number: 101160166                     */
/*                                                */
/**************************************************/

//takes an integer, calculates the nth factorial of the number and returns it
unsigned int factorial (unsigned int n){

	unsigned int factorialValue = 1; //final value of factorial (initial start at 1)

	//find factorial of 'n' by multiplying the factorial value in a loop 
	//and decreasing 'n' until 1 is reached
	while(n>=2) // 1(n-1) -> n-1
	{
		factorialValue = factorialValue * n; // 2(n-1)
		n--; // 1(n-1) -> n-1
	}
	return factorialValue; // 1
}

//takes a double as the base value and an integer as the exponent value
//calculates and returns the result of the base raised to the nth exponent
double power (double base, unsigned int n){
	double result = 1; // (1) updated base value (start at 1 for multiplication)

	//returns 1 for an exponent of 0
	if (n == 0) // 1
		return result; // 1
	
	//the result is continuously multipled by the base until the exponent value reaches n
	for (int exponent = 1; exponent <= n; exponent++) // 1 + n + n
	{ 
		result = result * base; // 2n
	}
	return result; // 1
}

//takes an integer as number of fibonacci terms to calculate
//calculates and returns nth fibonacci term
unsigned int fibonacci (unsigned int n){

	unsigned int currentTerm = 1, firstPrev=0, secondPrev=0; // 1+1+1

	//return n if it's 0 for the first term in the sequence
	if (n == 0) // 1
		return n; // 1

	
	//n-> number of terms to calculate in fibonacci sequence
	/*first previous, second previous and current terms swap places
	and then first and second previous terms added together to make new
	current term. Loop starts at 2 from which terms begin increasing and 
	continues until 1 less than nth fibonacci term is reached*/
	for (int i = 2; i <= n; i++) // 1+1(n-1)+1(n-1)
	{
		secondPrev = firstPrev; // 1(n-1)
		firstPrev = currentTerm; // 1(n-1)
		currentTerm = firstPrev + secondPrev; //2(n-1)
	}
	return currentTerm; // 1
}