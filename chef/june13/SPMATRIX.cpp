#include <bits/stdc++.h>
using namespace std;
const long long magic1=-9223372035563603797LL;
const int maxn=1e5,mod=1e9+7;
pair<int,int> input[maxn];
int N,M=3;

int main() {
	scanf("%d",&N);
	for(int i=0;i<N;i++) {
		scanf("%d",&input[i].first);
		input[i].second=i;
		if(input[i].first > M) M=input[i].first;
	}
	sort(input,input+N);
	static long long refact[10000001], eita=958416129;
	refact[10000000] = 10000000;
	for(int i=9999999;i>=1;i--) {
		refact[i]=refact[i+1]*i%mod;
	}
	long long inverse_sum = 0, f = 166666668LL, g = 3;
	int auxiliar_sum = 0;
	for(int n=3,p=0;n<=M;n++) {
		inverse_sum += eita * refact[n];
		auxiliar_sum += 3;
		eita = eita * (n-1) % mod;
		f = f * g % mod;
		g = g + n;
		if(inverse_sum < 0) inverse_sum += magic1;
		if(auxiliar_sum >= mod) auxiliar_sum -= mod;
		if(g >= mod) g = g - mod;
		if(p < M && input[p].first == n) {
			int ans = auxiliar_sum - inverse_sum%mod;
			if(ans < 0) ans += mod;
			ans = f * ans % mod;
			for(;p < M && input[p].first == n;input[p].first = ans, swap(input[p].first,input[p].second), p++);
		}
	}
	sort(input,input+N);
	for(int i = 0; i < N; i++) {
		printf("%d\n",input[i].second);
	} 
	return 0;
}
