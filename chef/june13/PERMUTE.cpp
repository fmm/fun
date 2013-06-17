#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cfloat>
#include <climits>
#include <cctype>
#include <cmath>
#include <cassert>
#include <ctime>

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <bitset>
#include <complex>
#include <limits>
#include <functional>
#include <numeric>

#define rep(x,n) for(int x = 0; x < n; ++x)
#define print(x) cout << x << endl
#define dbg(x) cerr << #x << " == " << x << endl
#define _ << " , " <<
#define mp make_pair
#define x first
#define y second

using namespace std;

template<class T> void pv(T a, T b) { for (T i = a; i != b; ++i) cout << *i << " "; cout << endl; }

typedef long long ll;
typedef pair<int,int> pii;

const int maxn=1e6,mod=1e9+7;
int f[maxn+10];

int fpow(int x, int e) {
	long long r=1;
	for(;;) {
		if(e&1) r=r*x%mod;
		if(e>>=1) {
			x=(long long)x*x%mod;
		} else break;
	}
	return r;
}

void prepare() {
	for(long long i=f[0]=1;i<=maxn;i++) f[i]=i*f[i-1]%mod;
}

int func(int n, int k) {
	k--;
	n = n-k;
	long long r=f[n];
	int b=(k+1)/2, a=k-b;
	r=r*fpow(n-1,b)%mod;
	r=r*fpow(n,a)%mod;
	return r;
}

int main() {
	prepare();
	cin.sync_with_stdio(false);
	int T;
	for(cin>>T;T;T--){
		int N,M;
		cin>>N>>M;
		printf("%d\n",func(N,2*N-M));
	}
	return 0;
}

