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

int S, R;
int w[1111];
int B[1111], E[1111];
double t;
int X;
int N;

void read() {
	cin>>X>>S>>R>>t>>N;
	rep(i,N) cin>>B[i]>>E[i]>>w[i];
}

struct st {
	double ds, dv, ndv, factor;
	void prepare(double ndv) {
		this->ndv=ndv;
		factor = (ndv - dv) / dv;
	}
	bool operator<(st s) const {
		return factor>s.factor;
	}
} piece[2222];

void process() {
	int m=0;
	double at=0;
	rep(i,N) {
		piece[m]=(st){B[i]-at,S};
		piece[m].prepare(R);
		m++;
		at=B[i];
		piece[m]=(st){E[i]-at,S+w[i]};
		piece[m].prepare(R+w[i]);
		m++;
		at=E[i];
	}
	piece[m]=(st){X-at,S};
	piece[m].prepare(R);
	m++;
	sort(piece,piece+m);
	double ans=0;
	rep(i,m) {
		double tt=piece[i].ds/piece[i].ndv;
		tt=min(t,tt);
		ans+=tt;
		t-=tt;
		piece[i].ds -= piece[i].ndv*tt;
		tt=piece[i].ds/piece[i].dv;
		ans+=tt;
	}
	printf(" %.9lf\n",ans);
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

