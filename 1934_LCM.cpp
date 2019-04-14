#include <iostream>

int main()
{
	static int TC = 0;
	static int itr = 0;

	static int inputA = 0;
	static int inputB = 0;
	static int a = 0;
	static int b = 0;
	static int tmp = 0;
	static int r = 0;
	static int GCD = 0;
	static int LCM = 0;

	std::cin >> TC;


	for (itr = 0; itr < TC; itr++)
	{
		a = b = tmp = r = GCD = LCM = 0;

		std::cin >> inputA;
		std::cin >> inputB;

		a = inputA;
		b = inputB;

		if (b > a)
		{
			tmp = a;
			a = b;
			b = tmp;
		}
		// get GCD and LCM
		while (b != 0)
		{
			r = a % b;
			a = b;
			b = r;
		}

		GCD = a;

		//LCM
		LCM = (inputA * inputB) / GCD;
		std::cout << LCM << std::endl;
	}

	return 0;
}
