#include <iostream>
#include <stdio.h>


static char text[1000010] = { 0, };
static char pattern[1000010] = { 0, };


// prime number for hash
//static unsigned long long int prime_number_multi = 1000000007; //257
//static unsigned long long int prime_number_mod = 1000000009; //1000000007

static unsigned long long int prime_number_multi = 257;
//static unsigned long long int prime_number_mod = 1000000007;

static unsigned long long int multi_arr[1000001] = { 0, };

static int ret_pos[1000010] = { 0, };
static int cnt = 0;

unsigned long long int getHashN(char* buf, int pos, int len)
{
	static unsigned long long int ret = 0;
	static int buf_idx = 0;
	static int pow_n = 0;

	ret = 0;
	buf_idx = 0;
	pow_n = len - 1;

	//char * prinm^n한걸 다 더한 뒤 mod
	while (buf_idx < len)
	{
		ret += (buf[pos + buf_idx] * multi_arr[pow_n]);// % prime_number_mod;
		//ret %= prime_number_mod;
		

		buf_idx++;
		pow_n--;
	}

	//ret = ret % prime_number_mod;

	return ret;
}

int main()
{
	//곱셈용 소수의 n승을 텍스트의 최대 길이많큼 구해 놓는다.
	multi_arr[0] = 1;
	for (int i = 1; i < 1000001; i++)
	{
		multi_arr[i] = (multi_arr[i - 1] * prime_number_multi);// % prime_number_mod;
	}
	

	// get text input
	std::cin.getline(text, 1000010, '\n');

	// get pattern input
	std::cin.getline(pattern, 1000010, '\n');


	/*
	1. P의 길이를 구한다
	2. P의 hash값을 구한다.
	3. T에서 P의 길이많큼 순차적으로 해쉬를 생성하며 비교한다
	*/

	//텍스트의 전체 길이 
	int text_size = 0;
	while (text[text_size] != 0)
	{
		text_size++;
	}

	//패턴의 전체 길이
	int pattern_size = 0;
	while (pattern[pattern_size] != 0)
	{
		pattern_size++;
	}


	//패턴의 해쉬값
	unsigned long long int pattern_hash = 0;
	unsigned long long int tmp_text_hash = 0;

	pattern_hash = getHashN(pattern, 0, pattern_size);
	tmp_text_hash = 0;

	//text에서 계산할 해쉬의 시작점
	int text_pos = 0;

	

	while(text_pos < text_size && text_pos + pattern_size <= text_size)
	{ 
		//just hash
		//tmp_text_hash = getHashN(text, text_pos, pattern_size);
		
		//rolling hash
		//시작점으로부터 특정길이에 대해 해쉬값을 구해 놓는다
		//offset이 1씩 증가할때마다 사라진 부분의 값을 빼주고 새로 생성되는 값을 더해준다
		if (text_pos == 0)
		{
			tmp_text_hash = getHashN(text, text_pos, pattern_size);
		}
		else
		{

			//이전 해쉬값중 첫번쨰 문자의 값을 빼준다
			tmp_text_hash -= ((text[text_pos - 1] * multi_arr[pattern_size - 1])/* % prime_number_mod*/);
			
			//음수 대비
			//tmp_text_hash += prime_number_mod;
			//mod
			//tmp_text_hash %= prime_number_mod;

			
			
			
			
			// 곱셈 소수를 한번 곱해줘서 pow를 마춰준다
			tmp_text_hash *= prime_number_multi;
			//tmp_text_hash %= prime_number_mod;

			

			//맨 마지막 문자의 해쉬값을 더해준다
			tmp_text_hash += text[text_pos + pattern_size - 1];
			//tmp_text_hash %= prime_number_mod;

		}


		if (pattern_hash == tmp_text_hash)
		{
			ret_pos[cnt] = text_pos;
			cnt++;
		}
			
		text_pos++;
	}

	printf("%d\n", cnt);

	for (int i = 0; i < cnt; i++)
	{
		printf("%d ", ret_pos[i]+1);
	}

	return 0;
}
