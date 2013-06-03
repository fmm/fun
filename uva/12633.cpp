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

#define PI	M_PI
#define TWOPI	(2.0*PI)
#define double float

void fast_fft(double data[], int nn, int isign) {
	int n, mmax, m, j, istep, i;
	double wtemp, wr, wpr, wpi, wi, theta;
	double tempr, tempi;
	n = nn << 1;
	j = 1;
	for (i = 1; i < n; i += 2) {
		if (j > i) {
			tempr = data[j];     data[j] = data[i];     data[i] = tempr;
			tempr = data[j+1]; data[j+1] = data[i+1]; data[i+1] = tempr;
		}
		m = n >> 1;
		while (m >= 2 && j > m) {
			j -= m;
			m >>= 1;
		}
		j += m;
	}
	mmax = 2;
	while (n > mmax) {
		istep = 2*mmax;
		theta = TWOPI/(isign*mmax);
		wtemp = sin(0.5*theta);
		wpr = -2.0*wtemp*wtemp;
		wpi = sin(theta);
		wr = 1.0;
		wi = 0.0;
		for (m = 1; m < mmax; m += 2) {
			for (i = m; i <= n; i += istep) {
				j =i + mmax;
				tempr = wr*data[j]   - wi*data[j+1];
				tempi = wr*data[j+1] + wi*data[j];
				data[j]   = data[i]   - tempr;
				data[j+1] = data[i+1] - tempi;
				data[i] += tempr;
				data[i+1] += tempi;
			}
			wr = (wtemp = wr)*wpr - wi*wpi + wr;
			wi = wi*wpr + wtemp*wpi + wi;
		}
		mmax = istep;
	}
}

const int maxn=(65536);
int x[maxn],y[maxn];
int R,C,N;
int row[maxn],column[maxn],diagonal[maxn<<1];
double a[maxn<<3], b[maxn<<3];
int cd[maxn<<1];

int main() {
	cin.sync_with_stdio(false);
	int T;
	cin>>T;
	for(int testcase=1;testcase<=T;testcase++) {
		cin>>R>>C>>N;
		rep(i,N) {
			cin>>x[i]>>y[i];
			x[i]=R-x[i]+1;
		}
		rep(i,R+1) row[i]=0;
		rep(i,C+1) column[i]=0;
		rep(i,R+C+1) diagonal[i]=0;
		rep(i,N) {
			row[x[i]]=C;
			column[y[i]]=R;
			int d=x[i]+y[i];
			if(!diagonal[d]) {
			  int d1 = min(R - x[i], y[i] - 1);
			  int d2 = min(C - y[i], x[i] - 1);
				diagonal[d]=1+d1+d2;
			}
		}
		rep(i,R+C+1) cd[i] = 0;
		rep(i,R+1) if(row[i]) cd[i+1] += 1, cd[i+C+1] -= 1;
		rep(i,C+1) if(column[i]) cd[i+1] += 1, cd[i+R+1] -= 1;
		rep(i,R+C) cd[i+1] += cd[i];
		int n=R+C+1;
		while(n&(n-1))n++;
		for(int i=0;i<n;i++) {
		  a[2*i+1]=(i<=R&&row[i]>0);
		  a[2*i+2]=0;
		  b[2*i+1]=(i<=C&&column[i]>0);
		  b[2*i+2]=0;
		}
		fast_fft(a,n,+1);
		fast_fft(b,n,+1);
		for(int i=0;i<n;i++) {
		  double new_real = a[2*i+1] * b[2*i+1] - a[2*i+2] * b[2*i+2];
		  double new_imag = a[2*i+1] * b[2*i+2] + a[2*i+2] * b[2*i+1];
		  a[2*i+1] = new_real, a[2*i+2] = new_imag;
		}
		fast_fft(a,n,-1);
		for(int i=0;i<=R+C;i++) if(diagonal[i]) {
			int ways = cd[i] - (int)(a[2*i+1]/n + 0.7777777);
			diagonal[i] -= ways;
		}
		long long answer=0, nr=0, nc=0;
		rep(i,R+1) answer += row[i], nr += row[i]!=0;
		rep(i,C+1) answer += column[i], nc += column[i]!=0;
		rep(i,R+C+1) if(diagonal[i]>0) answer += diagonal[i];
		answer -= nr*nc;
		answer = (long long)R*C - answer;
		printf("Case %d: %lld\n",testcase,answer);
	}
	return 0;
}
