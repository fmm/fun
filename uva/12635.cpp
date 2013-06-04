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

const int maxn=10000;
int sig[maxn+10];
vector<int> root;

void prepare() {
	for(int i=0;i<=maxn;i++){
		int q=0;
		rep(j,root.size()) if(root[j]==i) q=-77; else if(i<root[j]) q++;
		if(q<0) sig[i]=0; else if(q%2) sig[i]=-1; else sig[i]=+1;
	}
}

int test(int xl, int xu) {
	if(sig[xl]*sig[xu]>=0) return -1;
	for(int step=0;step<7;step++) {
		int xr = (xl + xu);
		if(xr % 2) return -1; else xr /= 2;
		int flag = sig[xl]*sig[xr];
		if(flag<0) xu=xr;
		if(flag>0) xl=xr;
		if(flag==0) return xr;    
	}
	return -1;
}

int stupid(int want) {
	int cnt = 0;
	for(int i=0;i<=maxn;i++) for(int j=i+1;j<=maxn;j++) if(test(i,j)==want) cnt++;
	return cnt;
}

int solve(int x0, int y0, int x1, int y1, int want, int t) {
	if(t < 0) return 0;
	int nx = (x0 + x1) / 2, ny = (y0 + y1) / 2, cnt_mid = 0;
	for(int a=0;a<=maxn;a++) {
		int r=(want<<7)-a*nx;
		if(r%ny==0) {
			int b=r/ny;
			if(a<b&&b<=maxn&&test(a,b)==want) {
				cnt_mid++;
			}
		}
	}
	int cnt_left  = solve(x0, y0, nx, ny, want, t - 1);
	int cnt_right = solve(nx, ny, x1, y1, want, t - 1);
	return cnt_left + cnt_mid + cnt_right;
}

int main() {
	cin.sync_with_stdio(false);
	int T;
	cin>>T;
	for(int testcase=1;testcase<=T;testcase++) {
		string equation;
		cin>>equation;
		rep(i,equation.size()) if(!isdigit(equation[i])) equation[i]=' ';
		stringstream ss(equation);
		root.clear();
		for(int r;ss>>r;root.push_back(r)); root.pop_back();
		prepare();
		int want;
		cin>>want;
		int ans=solve(128,0,0,128,want,6);
		printf("%d\n",ans);
	}
	return 0;
}

