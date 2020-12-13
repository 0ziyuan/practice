#include<stdio.h>
#include <stdlib.h>

long long m[500][500], s[500][500];
long long number;
void traceback(long long i, long long j, int* out);
void solve(int n, int p[], int out[])
{
	for (long long i = 1; i <= n; i++) m[i][i] = 0;
	for (long long r = 1; r <= n - 1; r++)  //r��i��j�ļ�����
		for (long long i = 1; i <= n - r; i++) //���ż�����r��������i�ݼ���ֱ��iΪ1
		{ 
			long long j = i + r;
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j]; // ��i��λ�ö���,�ֽ�Ϊm[i][i]��m[i+1][j]��
			s[i][j] = i;
			for (long long k = i + 1; k < j; k++) // ������С��m[i][j]
			{ 
				long long t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (t < m[i][j]) 
				{
					m[i][j] = t;
					s[i][j] = k;
				} //k��i��j֮�����Ѷ���λ��
			}
		}
	out[0] = m[1][n]% 1000000007;
	for (long long i = 1; i <= n; i++)
	{
		out[i] = i;
	}
	number = n;
	traceback(1,n,out);
}

void traceback(long long i, long long j, int* out)
{
	long long k;
	if (i == j) return ;
	else {
		for (k = number; out[k + 1] != i; k--)
		{
			out[k + 1] = out[k];
		}
		out[k+1] = -1;
		number++;
		for (k = number; out[k] != j; k--)
		{
			out[k + 1] = out[k];
		}
		out[k + 1] = -2;
		number++;
		traceback(i, s[i][j], out);
		traceback(s[i][j] + 1, j, out);
	}
}

int main()
{
	int n=5;
	int p[6] = { 10,5,2,8,6,3 };
	int out[1500] = {0};
	solve(n, p, out);
	printf("out=");
	for (int i = 0; i <= number; i++)
	{
		printf("%d,", out[i]);
	}
	system("pause");
	return 0;
}