#include <bits/extc++.h>
#define int long long

signed main() {
    int n, h;
    std::string s;
    std::cin >> s >> n >> h;
    std::vector<std::pair<int, int>> m(1000);

    for (int i = 0; i < n; i++) {
        std::string t;
        std::cin >> t;
        for (int j = 0; j < h; j++) {
            m[t[j]] = {i, j};
        }
    }
    int p = s[0];
    int ans = 0;

    for (int i = 1; i < size(s); i++) {
        ans += abs(m[p].first - m[s[i]].first);
        ans += abs(m[p].second - m[s[i]].second);
        p = s[i];
    }
    std::cout << ans << '\n';
    return 0;
}
