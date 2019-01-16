#include <bits/stdc++.h>
using namespace std;
const int N = 300100; 
int n, m;
struct node {
  int d, rev, sum; 
  node *ch[2], *prt; 
  inline int dir() { return prt->ch[1] == this; }  
  inline int isr() { return !prt || ((prt->ch[0] != this) && (prt->ch[1] != this)); }
  inline void setc(node *p, int k) { this->ch[k] = p; if(p) p->prt = this; }
  inline void upd() { sum = d; if(ch[0]) sum ^= ch[0]->sum; if(ch[1]) sum ^= ch[1]->sum; }
  inline void push() { if(!rev) return ; if(rev) swap(ch[0], ch[1]); if(ch[0]) ch[0]->rev ^= 1; if(ch[1]) ch[1]->rev ^= 1; rev = 0; }
} pool[N], *cur = pool, *P[N];
node *sta[N]; int top; 
inline node *New(int d) { node *p = cur++; p->d = p->sum = d; p->prt = 0; return p; }
inline void rotate(node *p) {
  node *prt = p->prt; int k = p->dir(); 
  if(!prt->isr()) prt->prt->setc(p, prt->dir()); 
  else p->prt = prt->prt; prt->setc(p->ch[!k], k); 
  p->setc(prt, !k); prt->upd(); 
} 
inline void splay(node *p) { 
  node *q = p;
  while(1) { sta[++top] = q; if(q->isr()) break; q = q->prt; }
  while(top) sta[top--]->push(); 
  while(!p->isr()) {
    if(p->prt->isr()) rotate(p);
    else if(p->dir() == p->prt->dir()) rotate(p->prt), rotate(p);
    else rotate(p), rotate(p); 
  } p->upd(); 
}
inline node *access(node *p) { node *q = 0; for(; p; p = p->prt) splay(p), p->ch[1] = q, (q = p)->upd(); return q; }
inline void mkroot(node *p) { access(p); splay(p); p->rev ^= 1; p->push(); }
inline void split (node *p, node *q) { mkroot(p); access(q); splay(p); }
inline void link  (node *p, node *q) { mkroot(p); mkroot(q); p->setc(q, 1); }
inline void cut   (node *p, node *q) { split(p, q); p->ch[1] = q->prt = 0; }
inline node *find(node *p) { access(p); splay(p); while(p->ch[0]) p = p->ch[0]; return p; }
int main() {
  scanf("%d %d", &n, &m);
  for(int i = 1; i <= n; i++) {
    int d; scanf("%d", &d); 
    P[i] = New(d); 
  } // rotate(P[1]); 
  for(int i = 1; i <= m; i++) {
    int op, u, v; scanf("%d %d %d", &op, &u, &v); 
    if(op == 0) { split(P[u], P[v]);  printf("%d\n", P[u]->sum);  }
    if(op == 1) { if(find(P[u]) != find(P[v])) link(P[u], P[v]); }
    if(op == 2) { if(find(P[u]) == find(P[v])) cut(P[u], P[v]); } 
    if(op == 3) { splay(P[u]); P[u]->d = P[u]->sum = v; }
  }
  return 0; 
}





















