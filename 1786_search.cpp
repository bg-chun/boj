#include <iostream>
#include <stdio.h>

unsigned long hash_5381(const char *str, int start,  int size)
{
    unsigned long hash = 5381;
    int c;

	int pos = start;
	str = str + start;

    while (pos < start + size)
    {
		c = *str++;
		hash = (((hash << 5) + hash) + c);
		pos++;
    } 
	return hash;
}

unsigned long hash_5387(const char* str, int start, int size)
{
	unsigned long hash = 5387;
	int c;

	int pos = start;
	str = str + start;

	while (pos < start + size)
	{
		c = *str++;
		hash = (((hash << 5) + hash) + c);
		pos++;
	}

	return hash;
}


// input buffer
char text[1000000] = { 0, };
char pattern[1000000] = {0, };


// output buffer
// patteren이 text에 등장하는 횟수
int times = 0;
// pattern들의 pos
int pos_arr[1000000] = { 0, };


int main()
{

	// get text input
	std::cin.getline(text, 1000000, '\n');

	// get pattern input
	std::cin.getline(pattern, 1000000, '\n');

	// objective
	// text안에서 pattern이 등장하는 횟수와 위치를 찾아서 반환 하여야 한다.

	// how to solove this problem?
	// 2개의 hash를 이용하여 라빈카프 알고리즘을 구현한다.
	// 특정 문자열에 대해 소수가 다른 해쉬를 두개 생성하여 비교한다.
	// 두개다 일치하면 동일한 문자열로 처리한다.

	// 동일한 문자열일시 times를 증가하고 pos_arr에 text의 문자열 시작 인덱스를 추가한다.

	// calc size of pattern
	int p_size = 0;
	while (pattern[p_size] != 0)
	{
		p_size++;
	}

	// calc hash 5381 and 5387
	unsigned long pattern_hash_5381 = hash_5381(pattern, 0, p_size);
	unsigned long pattern_hash_5387 = hash_5387(pattern, 0, p_size);

	// compare
	int text_cur = 0;
	while (text[text_cur] != 0 && text_cur + p_size < 1000000)
	{
		if (pattern_hash_5381 == hash_5381(text, text_cur, p_size) && pattern_hash_5387 == hash_5387(text, text_cur, p_size))
		{
			pos_arr[times] = text_cur;
			times++;
		}

		text_cur++;
	}


	//std::cout << times << std::endl;
	printf("%d\n", times);

	for (int i = 0; i < times; i++)
	{
		//std::cout << pos_arr[i] + 1;
		//printf("%d ", pos_arr[i] + 1);
		std::cout << pos_arr[i] + 1<< " "; 

		//if (i < times - 1)
		//{
		//	std::cout << " ";
		//}
			
	}
	//std::cout << std::endl;

	return 0;
}
