#include <iostream>
#include <stdio.h>
#include <cstring>

const int MOD = 1000000;

/*

bool myStrcmp(const char* str1, int pos1, const char* str2, int pos2, int len)
{
	str1 = str1 + pos1;
	str2 = str2 + pos2;

	for (int i = 0; i < len; i++)
	{
		if (*str1 != *str2)
		{
			return false;
		}
	}

	return true;
}
*/

/*
static unsigned long hash_5381(const char* str, int start, int size)
{
	static unsigned long hash = 5381;
	static int c;
	static int pos;

	pos = start;
	str = str + start;

	while (pos < start + size)
	{
		c = *str++;
		hash = (((hash << 5) + hash) + c) % MOD;
		pos++;
	}
	return hash % MOD;
}

static unsigned long hash_5387(const char* str, int start, int size)
{
	static unsigned long hash = 9679;
	static int c;
	static int pos;

	pos = start;
	str = str + start;

	while (pos < start + size)
	{
		c = *str++;
		hash = (((hash << 5) + hash) + c) % MOD;
		pos++;
	}

	return hash % MOD;
}
*/

static void hash_5381_5387(const char* str, int start, int size, unsigned long& ret1, unsigned long& ret2)
{
	static unsigned long hash_9679 = 9679;
	static unsigned long hash_5381 = 5381;

	static int c_9679 = 0;
	static int c_5381 = 0;
	static int pos = 0;

	hash_9679 = 9679;
	hash_5381 = 5381;
	pos = start;
	str = str + start;

	while (pos < start + size)
	{
		c_9679 = *str;
		c_5381 = *str;
		
		hash_9679 = (((hash_9679 << 5) + hash_9679) + c_9679) % MOD;
		hash_5381 = (((hash_5381 << 5) + hash_5381) + c_5381) % MOD;
		pos++;
		str++;
	}

	
	ret1 = hash_5381 % MOD;
	ret2 = hash_9679 % MOD;

	return;
}

// input buffer
static char text[1000010] = { 0, };
static char pattern[1000010] = { 0, };


// output buffer
// patteren이 text에 등장하는 횟수
static int times = 0;
// pattern들의 pos
static int pos_arr[1000010] = { 0, };


int main()
{

	// get text input
	std::cin.getline(text, 1000010, '\n');

	// get pattern input
	std::cin.getline(pattern, 1000010, '\n');

	// objective
	// text안에서 pattern이 등장하는 횟수와 위치를 찾아서 반환 하여야 한다.

	// how to solove this problem?
	// 2개의 hash를 이용하여 라빈카프 알고리즘을 구현한다.
	// 특정 문자열에 대해 소수가 다른 해쉬를 두개 생성하여 비교한다.
	// 두개다 일치하면 동일한 문자열로 처리한다.

	// 동일한 문자열일시 times를 증가하고 pos_arr에 text의 문자열 시작 인덱스를 추가한다.

	// calc size of pattern
	static int p_size = 0;
	p_size = 0;
	
	while (pattern[p_size] != 0)
	{
		p_size++;
	}

	// calc hash 5381 and 5387
	static unsigned long pattern_hash_5381 = 0; // hash_5381(pattern, 0, p_size);
	static unsigned long pattern_hash_5387 = 0; // hash_5387(pattern, 0, p_size);
	
	hash_5381_5387(pattern, 0, p_size, pattern_hash_5381, pattern_hash_5387);

	static unsigned long ret1 = 0;
	static unsigned long ret2 = 0;

	// compare
	static int text_cur = 0;
	static bool check = false;
	static int i = 0;
	while (text[text_cur] != 0 && text_cur + p_size < 1000010)
	{
		if (text[text_cur] != pattern[0])
		{
			text_cur++;
			continue;
		}

		/*if (pattern_hash_5381 == hash_5381(text, text_cur, p_size) && pattern_hash_5387 == hash_5387(text, text_cur, p_size))
		{
			pos_arr[times] = text_cur;
			times++;
		}*/
		
		hash_5381_5387(text, text_cur, p_size, ret1, ret2);
		if (ret1 == pattern_hash_5381 && ret2 == pattern_hash_5387)
		{
			pos_arr[times] = text_cur;
			times++;
		}

		//시작점과 패턴길이내에서 다음시작점으로 건너뛴다
		check = false;
		for (int i = text_cur + 1; i < text_cur + p_size; i++)
		{
			if (text[i] == pattern[0])
			{
				text_cur = i;
				check = true;
				break;
			}
		}

		if (check)
		{
			continue;
		}

		text_cur++;
	}


	std::cout << times << std::endl;
	for (i = 0; i < times; i++)
	{
		std::cout << pos_arr[i] + 1 << " ";

	}

	return 0;
}
