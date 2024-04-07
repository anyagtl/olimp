#include <bits/extc++.h>

signed main() {
    int q, n;
    std::cin >> q >> n;
    std::map<int, std::pair<int, int>> m;
    int a;
    std::cin >> a;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            std::cout << "? " << i << ' ' << j << std::endl;
            std::cin >> x;
            m[x] = {i, j};
        }
    }

    for (int i = 0; i < q; i++) {
        if (i != 0) {
            std::cin >> a;
        }
        if (m.count(a)) {
            std::cout << "! " << m[a].first << ' ' << m[a].second << std::endl;
            continue;
        } else {
            std::cout << "! " << -1 << std::endl;
        }
    }


    return 0;
}
