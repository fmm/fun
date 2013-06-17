#include <bits/stdc++.h>
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

const int maxn=1e5,mod=3046201;
int fact[maxn*30+10], inv[maxn*30+10];
int tree[maxn+10], have[maxn+10], n,q;

void change(int A, int B) {
	int delta = B - have[A];
	for(have[A]=B;A<=n;tree[A]+=delta,A+=A&-A);
}

int query(int A) {
	int tot=0;
	for(;A;tot+=tree[A],A-=A&-A);
	return tot;
}

int query(int L, int R) {
	return query(R)-query(L-1);
}

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

int comb(int n, int m) {
	assert(0<=m&&m<=n);
	return (long long)fact[n]*inv[m]%mod*inv[n-m]%mod;
}

int func(int L, int R) {
	if(L==R) return 1;
	int N=R-L+1, M=query(L,R), r=M%N, d=M/N;
	long long ways = fact[M];
	ways = ways * fpow(inv[d+1],r) % mod;
	ways = ways * fpow(inv[d],N-r) % mod;
	return ways * comb(N, r) % mod;
}

int main() {
	cin.sync_with_stdio(false);
	for(long long i=fact[0]=1;i<=30*maxn;i++) fact[i]=fact[i-1]*i%mod;
	inv[30*maxn] = fpow(fact[30*maxn],mod-2);
	for(long long i=maxn*30-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	cin>>n;
	rep(i,n) {
		int x;
		cin>>x;
		change(i+1,x);
	}
	cin>>q;
	char cmd[11];
	int a,b;
	while(q--){
		cin>>cmd>>a>>b;
		if(cmd[0]=='c') change(a,b);
		else printf("%d\n",func(a,b));
	}
  return 0;
}

