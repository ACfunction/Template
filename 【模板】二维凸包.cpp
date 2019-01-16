#include <bits/stdc++.h>
#define db double 
const db eps = 1e-7;
const int N = 10010;
using namespace std;
int n, sta[N], top; 
db ans = 0;
struct Vec {
  db x, y;
  inline bool operator < (const Vec &a) const { return x == a.x ? y < a.y : x < a.x; }
};
Vec v[N];
inline double pf(double x) { return x * x; }
inline double Cross(Vec a, Vec b) { return a.x * b.y - a.y * b.x; }
inline double Dot(Vec a, Vec b)   { return a.x * b.y + a.y * b.x; }
inline double dis(Vec a, Vec b)   { return sqrt(pf(a.x - b.x) + pf(a.y - b.y)); }
inline bool check(int i, int j, int k) {
  return (v[i].y - v[j].y) * (v[j].x - v[k].x) > (v[j].y - v[k].y) * (v[i].x - v[j].x); 
}

int main() {
	scanf("%d", &n);
  for(int i = 1; i <= n; i++) scanf("%lf %lf", &v[i].x, &v[i].y);
  sort(v + 1, v + n + 1); top = 0; sta[++top] = 1, sta[++top] = 2; 
  for(int i = 3; i <= n; i++) {
    while(top > 1 && check(i, sta[top], sta[top - 1])) top--; sta[++top] = i; 
  }
  for(int i = 1; i < top; i++) ans += dis(v[sta[i]], v[sta[i + 1]]);
  top = 0; sta[++top] = 1, sta[++top] = 2;
  for(int i = 3; i <= n; i++) {
    while(top > 1 && !check(i, sta[top], sta[top - 1])) top--; sta[++top] = i; 
  }
  for(int i = 1; i < top; i++) ans += dis(v[sta[i]], v[sta[i + 1]]);
  printf("%.2lf\n", ans);
	return 0;
}