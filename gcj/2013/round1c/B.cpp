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

void doit(int want, int n, vector<int>& v) {
	for(;n>0;n--) if(want>=n) v[n]=+1, want -= n;
	assert(want==0);
}

int main() {
  int T;
	cin>>T;
	for(int testcase=1;testcase<=T;testcase++){
		printf("Case #%d: ",testcase);
		int X,Y;
		cin>>X>>Y;
		int sx=X<0, sy=Y<0;
		X=abs(X), Y=abs(Y);
		int N=0,S=0;
		while(S<X+Y||(S-X-Y)%2) S += (++N);
		int K=(S-X-Y)/2;
		vector<int> vx(N+1,0), vy(N+1,0), vk(N+1,0);
		doit(X+K,N,vx);
		rep(i,N+1) if(vx[i]==0) vy[i]=+1;
		doit(K,N,vk);
		rep(i,N+1) if(vk[i]) {
			if(vx[i]) vy[i]=-1, vx[i]=0;
			else if(vy[i]) vx[i]=-1, vy[i]=0;
		}
		if(sx) rep(i,N+1) vx[i]=-vx[i];
		if(sy) rep(i,N+1) vy[i]=-vy[i];
		rep(i,N) {
			if(vx[i+1]>0) putchar('E');
			if(vx[i+1]<0) putchar('W');
			if(vy[i+1]>0) putchar('N');
			if(vy[i+1]<0) putchar('S');
		}
		puts("");
	}
	return 0;
}

