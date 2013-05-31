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

long long N;

void read() {
	cin>>N;
}

const int maxn = 1e7;
char is_composite[maxn];

void preprocess() {
	for(int i=2;i<maxn;i++)
		if(!is_composite[i])
			for(long long j=i+i;j<maxn;j+=i)
				is_composite[j]=1;
}

void process() {
	int R=1;
	for(long long i=2;i*i<=N;i++) if(!is_composite[i]) {
		long long j=i*i;
		for(;j<=N;j=j*i) {
			R++;
		}
	}
	if(N==1) R=0;
	printf(" %d\n",R);
}

int main() {
	preprocess();
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

