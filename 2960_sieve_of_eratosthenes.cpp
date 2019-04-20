// Example program
#include <iostream>
#include <string>



int main()
{
	// number/isPrime 0: i don't know, 1: yes, -1: nope
	static int arr[1010] = { 0, };
	static int K = 0;
	static int N = 0;
	static int cnt = 0;
	std::cin >> N;
	std::cin >> K;

	//N과 K가 주어질떄 2~N중에  K번째 지우는 수를 구하라
	//사실 나는 왜 조건을 i*i <= N*N으로 해야하는지 모르겠다.
	//O(root(N))이 되는건 알겠다.
	//100까지라면 절반까지만 하면되지 않나?
	for (int i = 2; i <= N; i++)
	{
		if (arr[i] == 0)
		{
			arr[i] = 1;
			cnt++;
			if (cnt == K)
			{
				std::cout << i << std::endl;
				return 0;
			}
			for (int j = i; i * j <= N; j++)
			{
				
			//확인안하고 지웠네.....
				if (arr[i * j] == 0)
				{
					arr[i * j] = -1;
					cnt++;
					if (cnt == K)
					{
						std::cout << i * j << std::endl;
						return 0;
					}

				}
			}
		}
	}

	return 0;
}
