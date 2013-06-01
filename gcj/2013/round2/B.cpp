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

long long N, P;

void read() {
	cin>>N>>P;
}

long long func(long long x) {
	long long pos=0,q=N;
	while(x) {
		q/=2;
		pos += q;
		x=(x-1)/2;
	}
	return pos;
}

long long func2(long long x) {
	long long pos=N-1,q=N;
	while(x) {
		q/=2;
		pos -= q;
		x=(x-1)/2;
	}
	return pos;
}

void process() {
	N=1LL<<N;
	P--;
	long long a=0;
	for(long long add=N;add;) {
		long long na=a+add;
		if(na<N&&func(na)<=P) a=na;
		else add>>=1;
	}
	long long b=0;
	for(long long add=N;add;) {
		long long nb=b+add;
		if(nb<N&&func2(N-1-nb)<=P) b=nb;
		else add>>=1;
	}
	printf(" %lld %lld\n",a,b);
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

