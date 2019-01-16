#include <bits/stdc++.h>
using namespace std;
const int N = 50050; 
int n, m, blo, a[N], cnt[1001000], ans[N], cntq, cntc, now; 
struct Query  {
  int id, l, r, idx; 
  inline bool operator < (const Query &x) const {
    return l / blo == x.l / blo ? (r / blo == x.r / blo ? idx < x.idx 
      : r / blo < x.r) : l / blo < x.l / blo; 
  }
} Q[N]; 
struct Change {
  int pos, C; 
} C[N]; 
inline void add(int x) {
  if(!cnt[x]) now++; cnt[x]++; 
}
inline void del(int x) {
  cnt[x]--; if(!cnt[x]) now--; 
}
inline void move(int x, int id) {
  if(Q[id].l <= C[x].pos && C[x].pos <= Q[id].r) {
    del(a[C[x].pos]); add(C[x].C); 
  } swap(a[C[x].pos], C[x].C); 
}
int main() {
  scanf("%d %d", &n, &m); blo = pow(n, 0.666); 
  for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
  for(int i = 1; i <= m; i++) {
    char op[5]; int l, r; 
    scanf("%s %d %d", op, &l, &r);
    if(op[0] == 'R') C[++cntc].pos = l, C[cntc].C = r;
    else  {
      Q[++cntq].l = l, Q[cntq].r = r; 
      Q[cntq].id = cntq, Q[cntq].idx = cntc; 
    }
  }  sort(Q + 1, Q + cntq + 1); 
  int L = 0, R = 0, id = 0; 
  for(int i = 1; i <= cntq; i++) {
    int l = Q[i].l, r = Q[i].r, idx = Q[i].idx;
    while(L > l) add(a[--L]);
    while(R < r) add(a[++R]);
    while(R > r) del(a[R--]); 
    while(L < l) del(a[L++]);
    while(id < idx) move(++id, i); 
    while(id > idx) move(id--, i);
    ans[Q[i].id] = now; 
  } 
  for(int i = 1; i <= cntq; i++) printf("%d\n", ans[i]); 
  return 0; 
}  