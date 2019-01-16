// luogu-judger-enable-o2
#include <bits/stdc++.h>
#define ll unsigned long long
const int N = 3000000;
using namespace std;
int n, cnt, sumu[N + 50], phi[N + 50], p[N + 50], mu[N + 50];
bool flag[N + 50]; 
ll sump[N + 50];
unordered_map <ll, ll> Sphi;
unordered_map <int, int> Smu;
inline void prework() {
  phi[1] = mu[1] = 1;
  for(int i = 2; i <= N; i++) {
    if(!flag[i]) {
      p[++cnt] = i; 
      mu[i] = -1; phi[i] = i - 1; 
    } for(int j = 1; j <= cnt && i * p[j] <= N; j++) {
      flag[i * p[j]] = 1; 
      if(i % p[j] == 0) {
        phi[i * p[j]] = phi[i] * p[j];
        break ;
      } phi[i * p[j]] = phi[i] * (p[j] - 1);
      mu[i * p[j]] = -1 * mu[i];
    }
  }
  for(int i = 1; i <= N; i++) 
    sumu[i] = sumu[i - 1] + mu[i], 
    sump[i] = sump[i - 1] + phi[i];
}
inline ll GetSumu(int n) {
  if(n <= N) return sumu[n];
  if(Smu[n]) return Smu[n];
  ll ret = 1ll;
  for(int l = 2, r; l <= n; l = r + 1) {
    r = n / (n / l); ret -= (r - l + 1) * GetSumu(n / l);
  } return Smu[n] = ret; 
}
inline ll GetSphi(int n) {
  if(n <= N) return sump[n];
  if(Sphi[n]) return Sphi[n];
  ll ret = 1ll * n * (n + 1) / 2; 
  for(int l = 2, r; l <= n; l = r + 1) {
    r = n / (n / l); ret -= (r - l + 1) * GetSphi(n / l);
  } return Sphi[n] = ret; 
}
int main() {
  prework(); 
  int T; scanf("%d", &T);
  while(T--) {
    int n; scanf("%d", &n);
    printf("%lld %lld\n", GetSphi(n), GetSumu(n));
  }
  return 0;
}