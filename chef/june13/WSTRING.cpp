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

const int maxn=1e4;
char w[maxn+10];
int s;
int q[maxn+10][30];

int get(int i, int j) {
	int mx=0;
	rep(k,28) {
		int nmx=q[j][k]-(i>0?q[i-1][k]:0);
		if(nmx>mx) {
			mx=nmx;
		}
	}
	return mx;
}

int main() {
	cin.sync_with_stdio(false);
	int T;
	for(cin>>T;T;T--){
		cin>>w;
		s=strlen(w);
		rep(i,s+1) rep(j,30) q[i][j]=0;
		rep(i,s) {
			if(w[i]=='#') w[i]=29; else w[i]-='a';
			q[i][w[i]]++;
		}
		rep(i,s+1) rep(j,30) q[i+1][j] += q[i][j];
		int ans=0,j=-1,k=-1;
		rep(i,s) {
			if(w[i]==29) {
				if(j>0&&k>0&&j+1<=k-1&&k+1<=i-1) {
					int w1=get(0,j-1);
					int w2=get(j+1,k-1);
					int w3=get(k+1,i-1);
					int w4=get(i+1,s-1);
					if(w1>0&&w2>0&&w3>0&&w4>0)ans=max(ans,w1+1+w2+1+w3+1+w4);
				}
				j=k;
				k=i;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

