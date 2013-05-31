#include <bits/stdc++.h>
#define rep(x,n) for(int x = 0; x < n; ++x)
#define print(x) cout << x << endl
#define dbg(x) cerr << #x << " == " << x << endl
#define _ << " , " <<
#define mp make_pair
#define x first
#define y second
using namespace std;

template<class T> void pv(T a, T b) { for (T i = a; i != b; ++i) cerr << *i << " "; cerr << endl; }

typedef long long ll;
typedef pair<int,int> pt;

int N;
vector<int> x, h;

bool solve(int i, int N) {
	if(i>=N) return true;
	int next=x[i];
	for(int j=i+1;j<next;j++) if(x[j]>next) return false;
	if(!solve(i+1,next)) return false;
	if(!solve(next,N)) return false;
	return true;
}

int solve(int i, int j, long long hj, int k,long long hk) {
  long long hi=hk-(hk-hj)*(k-i)/(k-j);
  if((hk-hj)*(k-i)%(k-j)!=0) hi--;
  return hi;
}

int solve2(int i, long long hi, int j, int k, long long hk) {
  long long hj=hi+(hk-hi)*(j-i)/(k-i);
  if((hk-hi)*(j-i)%(k-i)==0) hj--;
  return hj;
}

int go(int i) {
  if(h[i]<0) {
    int j=x[i], hj=go(j), k=x[j], hk=go(k);
    h[i]=solve(i,j,hj,k,hk);
    for(j=i+1,k=i;j<=N;j++) if(h[j]<0&&x[j]==x[i]) { // keep solving
      h[j]=solve2(k,h[k],j,x[k],h[x[k]]);
      if(h[j]<0) throw " Impossible";
      k=j;
    }
    if(h[i]<0) throw " Impossible";
  }
  return h[i];
}

int main() {
  int T;
	cin>>T;
	for(int testcase=1;testcase<=T;testcase++){
		printf("Case #%d:",testcase);
		cin>>N;
		x.resize(N+1);
		h.resize(N+1);
		rep(i,N-1) cin>>x[i+1];
		x[N]=N+1;
		try {
		  if(!solve(1,N)) throw " Impossible";
		  for(int i=1;i<=N;i++) h[i]=-1;
		  for(int i=1;i<=N;i=x[i]) h[i]=1e9;
		  for(int i=1;i<=N;i++) if(h[i]<0&&h[x[i]]>0) h[i]=h[x[i]]-1;
		  for(int i=1;i<=N;i++) if(h[i]<0) h[i]=go(i);
		  for(int i=1;i<=N;i++) printf(" %d",h[i]); puts("");
		} catch(char const*exception) {
		  puts(exception);
		}
	}
	return 0;
}

