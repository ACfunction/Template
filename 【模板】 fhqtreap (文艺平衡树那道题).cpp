#include <bits/stdc++.h>
using namespace std;
const int N = 100100; 
int n, m, cnt; 
struct node {
  int tag, siz, d, rnd; node *ch[2];
  inline void upd() {
    int ret = 1;
    if(ch[0]) ret += ch[0]->siz; 
    if(ch[1]) ret += ch[1]->siz; 
    siz = ret; 
  } 
  inline void pushd() {
    if(!tag) return ; swap(ch[0], ch[1]); 
    if(ch[0]) ch[0]->tag ^= 1; 
    if(ch[1]) ch[1]->tag ^= 1; 
    tag = 0; 
  }
} pool[N]; 
inline int siz(node *r) {
  if(r) return r->siz; return 0; 
}
struct FhqTreap {
  node *root; 
  inline node* merge(node *p, node *q) {
    if(!p) return q; if(!q) return p; 
    if(p->rnd < q->rnd) { p->pushd(); p->ch[1] = merge(p->ch[1], q); p->upd(); return p; }
    else { q->pushd(); q->ch[0] = merge(p, q->ch[0]); q->upd(); return q; }
  }
  inline void split(node *r, int k, node *&p, node *&q) {
    if(!r) { p = q = NULL; return ; } r->pushd(); 
    if(siz(r->ch[0]) < k) p = r, split(r->ch[1], k - siz(r->ch[0]) - 1, r->ch[1], q);
    else q = r, split(r->ch[0], k, p, r->ch[0]); r->upd();  
  }
  inline void output(node *r) {
    r->pushd(); 
    if(r->ch[0]) output(r->ch[0]); 
    printf("%d ", r->d);
    if(r->ch[1]) output(r->ch[1]);  
  }
} T; 
int main() {
  scanf("%d %d", &n, &m);
  T.root = &pool[0]; T.root->siz = 1; T.root->d = 1; 
  for(int i = 2; i <= n; i++) {
    node *p = &pool[++cnt]; 
    p->siz = 1, p->rnd = rand(); 
    p->d = i, p->ch[0] = p->ch[1] = NULL; 
    T.root = T.merge(T.root, p);
  }
  for(int i = 1; i <= m; i++) {
    int l, r; scanf("%d %d", &l, &r); 
    node *p, *q, *s; 
    T.split(T.root, l - 1, p, q); 
    T.split(q, r - l + 1, q, s); 
    q->tag ^= 1; 
    T.merge(p, T.merge(q, s)); 
  } T.output(T.root); 
  return 0; 
}