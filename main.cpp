#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using vvl = vector<vl>;

ll N, M, T;
vvl nums;

vl di{-1, 1, 0, 0};
vl dj{0, 0, -1, 1};

void Move(ll x, ll d, ll k) {
  for (auto i = 1; i * x <= N; ++i) {
    const auto& X = i * x;
    if (d == 1) {
      for (auto g = 0; g < k; ++g) {
        ll tmp = nums[X][0];
        for (auto m = 0; m < M - 1; ++m) {
          nums[X][m] = nums[X][m + 1];
        }
        nums[X][M - 1] = tmp;
      }
    } else {
      for (auto g = 0; g < k; ++g) {
        ll tmp = nums[X][M - 1];
        for (auto m = M - 1; 0 < m; --m) {
          nums[X][m] = nums[X][m - 1];
        }
        nums[X][0] = tmp;
      }
    }
  }

  vl tremi{};
  vl tremj{};
  for (auto i = 1; i <= N; ++i) {
    for (auto j = 0; j < M; ++j) {
      if (nums[i][j] == 0) continue;

      for (auto d = 0; d < 4; ++d) {
        auto ni = i + di[d];
        if (ni < 1 || N < ni) continue;

        auto nj = j + dj[d];
        if (nj < 0) {
          nj += M;
        }
        if (M <= nj) {
          nj -= M;
        }

        if (nums[i][j] == nums[ni][nj]) {
          tremi.push_back(i);
          tremj.push_back(j);

          tremi.push_back(ni);
          tremj.push_back(nj);
        }
      }
    }
  }

  if (tremi.size() != 0) {
    for (auto u = 0; u < tremi.size(); ++u) {
      nums[tremi[u]][tremj[u]] = 0;
    }
  } else {
    double avg = 0;
    ll cnt = 0;
    for (auto i = 1; i <= N; ++i) {
      for (auto j = 0; j < M; ++j) {
        if (nums[i][j] > 0) {
          ++cnt;
          avg += nums[i][j];
        }
      }
    }
    avg /= cnt;
    for (auto i = 1; i <= N; ++i) {
      for (auto j = 0; j < M; ++j) {
        if (nums[i][j] > 0) {
          if (nums[i][j] > avg) {
            nums[i][j] -= 1;
          } else if (nums[i][j] < avg) {
            nums[i][j] += 1;
          }
        }
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> N >> M >> T;
  nums = vvl(N + 1, vl(M));
  for (auto i = 1; i <= N; ++i) {
    for (auto j = 0; j < M; ++j) {
      cin >> nums[i][j];
    }
  }

  while (0 < (T--)) {
    ll x, d, k;
    cin >> x >> d >> k;
    Move(x, d, k);
  }

  ll ans = 0;
  for (auto i = 1; i <= N; ++i) {
    for (auto j = 0; j < M; ++j) {
      ans += nums[i][j];
    }
  }

  cout << ans;

  return 0;
}