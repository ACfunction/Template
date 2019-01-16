#include <bits/stdc++.h>
using namespace std;
const int N = 100100;
const int K = 200200;
int n, k, c[K], cnt, ans[N];
struct node {
  int a, b, c, num, ans;
}A[N], B[N]; 
inline bool cmp1(node x, node y) {
  if(x.a == y.a) {
    if(x.b == y.b) 
      return x.c < y.c;
    return x.b < y.b; 
  } return x.a < y.a;
}
inline bool cmp2(node x, node y) { 
  if(x.b == y.b) 
    return x.c < y.c;
  return x.b < y.b; 
}
inline int lb(int x) { return x & (-x); }
inline void add(int x, int d) { for(int i = x; i <= k; i += lb(i)) c[i] += d; }
inline int sum(int x) { int ret = 0; for(int i = x; i; i -= lb(i)) ret += c[i]; return ret; }
inline void CDQ(int l, int r) { 
  if(l == r) return ; 
  int mid = (l + r) >> 1;
  CDQ(l, mid), CDQ(mid + 1, r); 
  sort(B + l, B + mid + 1, cmp2); 
  sort(B + mid + 1, B + r + 1, cmp2); 
  int pos = l; 
  for(int i = mid + 1; i <= r; i++) {
    while(pos <= mid && B[pos].b <= B[i].b) 
      add(B[pos].c, B[pos].num), pos++; 
    B[i].ans += sum(B[i].c); 
  } for(int i = l; i < pos; i++) add(B[i].c, -B[i].num);
}
int main() {
  scanf("%d %d", &n, &k);
  for(int i = 1; i <= n; i++) { 
    scanf("%d %d %d", &A[i].a, &A[i].b, &A[i].c); 
  } sort(A + 1, A + n + 1, cmp1); 
  int num = 0; 
  for(int i = 1; i <= n; i++) {
    num++; 
    if(A[i].a != A[i + 1].a ||
       A[i].b != A[i + 1].b ||
       A[i].c != A[i + 1].c) 
      B[++cnt] = A[i], B[cnt].num = num, num = 0;  
  } 
  CDQ(1, cnt);
  for(int i = 1; i <= cnt; i++)
    B[i].ans += B[i].num - 1, ans[B[i].ans] += B[i].num;
  for(int i = 0; i < n; i++) printf("%d\n", ans[i]);
	return 0;
}