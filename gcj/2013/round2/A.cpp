#include <bits/stdc++.h>
#define _ << " _ " <<
#define dbg(x) cerr << #x << " == " << x << endl
#define mp(x,y) make_pair((x),(y))
#define pv(x,y) {for(typeof(y) z=(x);z!=(y);z++)cerr<<*z<<" ";cerr<<endl;}
#define rep(x,y) for(int(x)=(0);(x)<int(y);++(x))
#define x first
#define y second
using namespace std;

typedef long long ll;
typedef pair<int,int> pt;

#if 0
#define GENERATE 1
#endif
const int maxn=1111,mod=1000002013;
int N, M;
struct S {
	long long o,e,p;
} s[maxn];

int o[maxn], e[maxn];
long long x[2*maxn];

bool co(int i, int j){
	return s[i].o<s[j].o;
}

bool ce(int i, int j){
	return s[i].e<s[j].e;
}

void read() {
	cin>>N>>M;
	rep(i,M) cin>>s[i].o>>s[i].e>>s[i].p;
}

long long sum(long long i) {
	if(i <= 0) return 0;
	return i * (i + 1) / 2;
}

long long func(long long i, long long j) {
	if(i==j) return 0;
	long long d=abs(i-j);
	long long x= d*N%mod - sum(d-1)%mod + mod;
	return x%mod;
}

void process() {
	rep(i,M) x[2*i]=s[i].o,x[2*i+1]=s[i].e;
	rep(i,M) o[i]=e[i]=i;
	sort(o,o+M,co);
	sort(e,e+M,ce);
	int q=2*M; x[q++]=N;
	sort(x,x+q);
	q=unique(x,x+q)-x;
	map<long long,long long> mm;
	long long T=0;
	rep(i,M) {
		T += s[i].p%mod*func(s[i].o,s[i].e)%mod;
		T %= mod;
	}
	long long R=0;
	for(int i=0,j=0,k=0;i<q;i++){
		for(;k<M&&s[o[k]].o<=x[i];k++) mm[s[o[k]].o]+=s[o[k]].p;
		for(;j<M&&s[e[j]].e==x[i];j++) for(long long z=s[e[j]].p;z;) {
			assert(mm.size());
			multimap<long long,long long>::iterator iter=mm.end(); iter--;
			assert(iter->second > 0);
			long long take=min(z,iter->second);
			iter->second -= take;
			z -= take;
			for(R+=take%mod*func(x[i],iter->first)%mod;R>=mod;R-=mod);
			if(iter->second==0) mm.erase(iter);
		}
	}
	R=T-R+mod;
	R%=mod;
	printf(" %lld\n",R);
}

int main() {
	int T;
#ifdef GENERATE
	unsigned int seed=time(0);
	dbg(seed);
	srand(seed);
	T=50;
	for(int testcase=1;testcase<=T;++testcase) {
		fprintf(stderr,"Case #%d:",testcase);
		// *generate input!
		// BEGIN
		// END
#else
		cin>>T;
		for(int testcase=1;testcase<=T;++testcase) {
			fprintf(stdout,"Case #%d:",testcase);
			read();
#endif
    try {
			process();
		} catch(char const*exception) {
			puts(exception);
		}
	}
	return 0;
}

