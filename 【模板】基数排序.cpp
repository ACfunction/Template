#include <bits/stdc++.h>
using namespace std;
const int N = (int)(1e7) + 10;
int n, a[N], b[N], cnt[65555];
int main() {
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
  for(int i = 1; i <= n; i++) cnt[a[i] & 65535]++;
  for(int i = 1; i <= 65535; i++) cnt[i] += cnt[i - 1];
  for(int i = 1; i <= n; i++) b[cnt[a[i] & 65535]--] = a[i];
  memset(cnt, 0, sizeof(cnt));
  for(int i = 1; i <= n; i++) cnt[a[i] >> 16]++;
  for(int i = 1; i <= 65535; i++) cnt[i] += cnt[i - 1];
  for(int i = n; i >= 1; i--) a[cnt[b[i] >> 16]--] = b[i];
  for(int i = 1; i <= n; i++) printf("%d ", a[i]);
  return 0;
}