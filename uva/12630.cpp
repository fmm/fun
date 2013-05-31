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

struct pt {
  double x,y;
  pt() {}
  pt(double x, double y) : x(x), y(y) {}
  pt operator+(pt p) {
    return pt(x+p.x,y+p.y);
  }
  pt operator-(pt p) {
    return pt(x-p.x,y-p.y);
  }
  pt operator*(double d) {
    return pt(x*d,y*d);
  }
  pt operator/(double d) {
    return *this * (1. / d);
  }
  pt operator[](double ang) {
    double C=cos(ang), S=sin(ang);
    return pt(x*C-y*S,x*S+y*C);
  }
  double operator!() {
    return hypot(x,y);
  }
  bool operator<(pt p) const {
    if(fabs(x-p.x)>1e-10) return x<p.x;
    if(fabs(y-p.y)>1e-10) return y<p.y;
    return false;
  }
} dot[111][111];

const double dx = sqrt(1.) / 2.;
const double dy = sqrt(3.) / 2.;
int my[222][222],ok;

int get(double z) {
  int sig=0;
  if(z<-1e-10) {
    sig=1;
    z=fabs(z);
  }
  int fz=int(z+1e-10);
  ok &= fabs(z-fz) <= 1e-10;
  assert( ok );
  if(sig) fz = -fz;
  return fz;
}

int main() {
  dot[0][0] = pt(0,0);
  for(int i=1;i<=100;i++) {
    dot[i][0] = dot[i-1][0] + pt(-dx,-dy);
    for(int j=1;j<=i;j++) {
      dot[i][j] = dot[i-1][j-1] + pt(+dx,-dy);
    }
  }
  for(int i=0;i<=100;i++) {
    for(int j=0;j<=i;j++) {
      ok=1;
      int rx=get(dot[i][j].x/dx);
      int ry=get(dot[i][j].y/dy);
      assert(abs(rx)<111&&abs(ry)<111);
      my[rx+111][ry+111] = i;
    }
  }
  for(int n;(cin>>n)&&n;) {
    n--;
    int sz=0;
    for(int i=0;i<=n;i++) for(int ii=0;ii<=i;ii++) {
      for(int j=i+1;j<=n;j++) for(int jj=0;jj<=j;jj++) {
        pt A=dot[i][ii], B=dot[j][jj];
        pt V=B-A;
        pt Q=B + V[M_PI/3.*2.];
        ok=1;
        int rx=get(Q.x/dx), ry=get(Q.y/dy);
        if(ok&&abs(rx)<111&&abs(ry)<111) {
          int &mk= my[rx+111][ry+111];
          if(mk && mk <= n && mk >= i) {
            //dbg( get(A.x/dx) _ get(A.y/dy) );
            //dbg( get(B.x/dx) _ get(B.y/dy) );
            //dbg( get(Q.x/dx) _ get(Q.y/dy) );
            //cerr<<endl;
            sz++;
          }
        }
      }
    }
    printf("%d\n",sz);
  }
  return 0;
}

