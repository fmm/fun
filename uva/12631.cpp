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

const int maxn=1e5+10,mod=1e9+7;
long long fact[maxn], inv[maxn], p2[maxn];
long long p[maxn],C;
int a,b,c,N,K;
long long how[maxn],cc[maxn];

int my[maxn];
int lst[maxn], sz;

void doit(int z) {
	if(z==1) {
		sz=0;
		lst[sz++]=z;
		return;
	}
	int p=my[z],q=0;
	do z/=p,q++; while(z%p==0);
	doit(z);
	for(int y=1,n=sz;q;q--) {
		y*=p;
		rep(i,n) lst[sz++]=lst[i]*y;
	}
}

long long gcd(long long x, long long y) {
	while(x) y %= x, swap(x,y); return y;
}

long long stupid(int q) {
	long long x=0;
	rep(i,1<<N) if(i && __builtin_popcount(i)!=q) {
		long long g=0;
		rep(j,N) if(i>>j&1) g=gcd(g,p[j]);
		x+=C/g;
	}
	return x;
}

int main() {
	my[0]=my[1]=1;
	for(int i=2;i<maxn;i++) if(!my[i]) 
		for(int j=i;j<maxn;j=j+i) if(!my[j])
			my[j]=i;
	p2[0]=1;
	rep(i,maxn-1) p2[i+1]=p2[i]*2%mod;
	rep(i,maxn) if(i<=1) fact[i]=1; else fact[i]=i*fact[i-1]%mod;
	inv[maxn-1]=549915853;
	for(int i=maxn-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	int T;
#ifndef GENERATE
	cin>>T;
#else
	T=1111;
#endif
	for(int testcase=1;testcase<=T;testcase++){
#ifndef GENERATE
		cin>>N>>C>>K;
		cin>>a>>b>>c;
#else
		N=11;C=rand();K=rand()%N+1;
		a=rand()%maxn,b=rand()%maxn,c=rand()%maxn;
#endif
		p[0]=a;
		p[1]=b;
		for(int i=2;i<N;i++) {
			p[i]=1+(a*p[i-2]+b*p[i-1]+c)%100000;
		}
		rep(i,maxn) how[i]=cc[i]=0;
		rep(i,N) {
			doit(p[i]);
			rep(j,sz) how[lst[j]]++;
		}
		rep(i,maxn) {
			if(how[i]>=K) cc[i]=fact[how[i]]*inv[K]%mod*inv[how[i]-K]%mod;
			how[i]=p2[how[i]]-1;
		}
		long long A=0,B=0;
		for(int i=maxn-1;i>=1;i--) {
			for(int j=i+i;j<maxn;j=j+i) {
				how[i] -= how[j]; how[i] += mod;
				cc[i] -= cc[j]; cc[i] += mod;
			}
			how[i] %= mod;
			A += (C/i) % mod * how[i];
			cc[i] %= mod;
			B += (C/i) % mod * cc[i];
			A %= mod;
			B %= mod;
		}
#ifdef GENERATE
		assert(A==stupid(-1)%mod);
		assert(B==stupid(K)%mod);
#endif
		printf("Case %d: %lld %lld\n",testcase,A,B);
	}
  return 0;
}

