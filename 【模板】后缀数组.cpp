#include <bits/stdc++.h>
const int N = (int)1e7 + 10; 
using namespace std;
char S[N]; 
int n, sa[N], rk[N], cnt[N];
struct node { 
  int id, Fi, Se; 
}a[N], b[N];
int main() {
  scanf("%s", S + 1); n = strlen(S + 1);
  for(int i = 1; i <= n; i++) cnt[(int)S[i]] = 1; // not ++ !
  for(int i = 1; i <= 128; i++) cnt[i] += cnt[i - 1];
  for(int i = 1; i <= n; i++) rk[i] = cnt[(int)S[i]];
  // Single word sort 
  for(int L = 1; L < n; L *= 2) {
    memset(cnt, 0, sizeof(cnt));
    for(int i = 1; i <= n; i++)  
      a[i].id = i, a[i].Fi = rk[i], a[i].Se = rk[i + L];
    for(int i = 1; i <= n; i++) cnt[a[i].Se]++;
    for(int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
    for(int i = 1; i <= n; i++) b[cnt[a[i].Se]--] = a[i];
    memset(cnt, 0, sizeof(cnt));
    for(int i = 1; i <= n; i++) cnt[b[i].Fi]++;
    for(int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
    for(int i = n; i >= 1; i--) a[cnt[b[i].Fi]--] = b[i];
    rk[a[1].id] = 1;
    for(int i = 1; i <= n; i++) 
      if(a[i].Fi == a[i - 1].Fi && a[i].Se == a[i - 1].Se) 
        rk[a[i].id] = rk[a[i - 1].id];
      else rk[a[i].id] = rk[a[i - 1].id] + 1;
  }
  for(int i = 1; i <= n; i++) sa[rk[i]] = i;
  for(int i = 1; i <= n; i++) printf("%d ", sa[i]);
  
  return 0;
}
