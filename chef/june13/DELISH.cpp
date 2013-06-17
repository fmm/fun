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
long long d[maxn+10];
int n;
long long A[maxn+10];
long long B[maxn+10];
long long C[maxn+10];
long long D[maxn+10];

void prepare(long long Max[], long long Min[]) {
	Max[0]=d[0];
	Min[0]=d[0];
	for(int i=1;i<n;i++) {
		Max[i]=max(d[i],Max[i-1]+d[i]);
		Min[i]=min(d[i],Min[i-1]+d[i]);
	}
}

long long func(long long x, long long y) {
	long long delta = x - y;
	if(delta < 0)
		delta = -delta;
	return delta;
}

int main() {
	cin.sync_with_stdio(false);
	int T;
	for(cin>>T;T;T--){
		cin>>n;
		rep(i,n) cin>>d[i];
		long long ans=0;
		prepare(A,B);
		reverse(d,d+n);
		prepare(C,D);
		reverse(C,C+n),reverse(D,D+n);
		for(int i=1;i<n;i++){
			ans=max(ans,func(A[i-1],C[i]));
			ans=max(ans,func(A[i-1],D[i]));
			ans=max(ans,func(B[i-1],C[i]));
			ans=max(ans,func(B[i-1],D[i]));
		}
		printf("%lld\n",ans);
	}
  return 0;
}

