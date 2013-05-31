#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cfloat>
#include <climits>
#include <cctype>
#include <cmath>
#include <cassert>
#include <ctime>

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <bitset>
#include <complex>
#include <limits>
#include <functional>
#include <numeric>

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

map< int, map< int, map<int, long long> > > full;

long long go(int x, int y, int d, int wx, int wy) {
  if(x == 1 || y == 1) return 1;
  if(full.count(d) && full[d].count(wx) && full[d][wx].count(wy))\
    return full[d][wx][wy];
  // x = 2^k
  // y = 2^k
  int xx = x / 2, yy = y / 2;
  long long R=0;

  // first
  R += go(xx,yy,d-1,min(wx,xx),min(wy,yy));
  // second
  if(wx>xx)
    R += go(xx,yy,d-1,wx-xx,min(wy,yy));
  // third
  if(wy>yy)
    R += go(xx,yy,d-1,min(wx,xx),wy-yy);

  return full[d][wx][wy] = R;
}

int main() {
  int T, testcase=1;
  for(cin>>T;T;T--){
    int K,A,B;
    cin >> K >> A >> B;
    /*K=30;
    A=0;
    for(int i=0;i<30;i++)if(rand()&1)A|=1<<i;
    B=0;
    for(int i=0;i<30;i++)if(rand()&1)B|=1<<i;
    if(A>B) swap(A,B);*/
    int d = 1;
    rep(i,K) d = d * 2;
    long long RA = A > 1 ? go(d, d, K, A-1, d) : 0;
    long long RB = go(d, d, K, B, d);
    printf("Case %d: %lld\n",testcase++,RB - RA);
  }
  return 0;
}

