#include <iostream>
#include <stdio.h>

static int arr[1000010] = { 0, };
static unsigned int M = 0, N = 0;
static unsigned int i = 0;
static unsigned int j = 0;

int main()
{

	//주어진 범위에서 소수를 구하는 문제는 에라토스테네스의 채를 이용하면 된다.
	//에라토스 테네스의 채는 소수는 1과 자기자신으로만 나누어지는 특성을 이용한다.
	//즉 1보다 큰 2부터 자기자신까지의 수들로 나누었을떄 2, 자기자신 말고 안나눠지면된다.
	//구현은 2부터 시작하여 주어진 수들의 배수를 모두지우면 소수만 남는것을 이용한다.


	// 이문제는 M이상 N이하의 소수를 구하는 문제이다.
	// 1부터 M까지의 소수를 구한뒤 N 이상부터 출력하면 된다.

	std::cin >> M;
	std::cin >> N;

	for (i = 2; i <= N; i++)
	{
		if (arr[i] == 0)
		{
			arr[i] = 1;

			for (j = i + i; j<= N; j = j + i)
			{
				arr[j] = -1;
			}
		}

		if (i >= M && arr[i] == 1)
		{
			//cout사용시 timeout
			printf("%d\n", i);
		}

	}


	return 0;
}
