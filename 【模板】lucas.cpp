#include <bits/stdc++.h>
#define ll long long
const int N = 1001000;
const int MN = 1000000;
using namespace std;
ll fac[N]; 
inline ll qpow(ll x, int k, ll p) { ll ret = 1; while(k) { if(k & 1) ret = ret * x % p; x = x * x % p; k >>= 1; } return ret;}
inline void prework(ll p) {
  fac[0] = 1ll; for(int i = 1; i <= MN; i++) fac[i] = fac[i - 1] * i % p;
}
inline ll C (ll n, ll m, ll p) { if(m > n) return 0; return fac[n] * qpow(fac[m], p - 2, p) % p * qpow(fac[n - m], p - 2, p) % p; }
inline ll Lucas(ll n, ll m, ll p) {
  if(!m) return 1ll; else return C(n % p, m % p, p) * Lucas(n / p, m / p, p) % p; 
}
int main() {
  int T; scanf("%d", &T);
  while(T--) { ll n, m, p; scanf("%lld %lld %lld", &n, &m, &p); 
    prework(p);  printf("%lld\n", Lucas(n + m, m, p)); 
  }
  return 0;
}