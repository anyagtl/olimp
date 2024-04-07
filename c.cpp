#include <bits/extc++.h>
#define Int long long

signed main() {
    const Int MOD1 = 1e9 + 7;
    const Int P1 = 27;

    const Int MOD2 = 1e9 + 9;
    const Int P2 = 29;

    Int n, m;
    std::cin >> n;
    std::pair<Int, Int> **v = (std::pair<Int, Int> **) std::malloc(sizeof(std::pair<Int, Int>*) * n);
    Int *sz = (Int *) std::malloc(sizeof(Int) * n);

    for (Int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;

        v[i] = (std::pair<Int, Int> *) std::malloc(sizeof(std::pair<Int, Int>) * size(s) + 1);
        v[i][0].first = v[i][0].second = s[0] - 'a' + 1;
        sz[i] = size(s);
        for (Int j = 1; j < size(s); j++) {
            v[i][j].first = (v[i][j - 1].first * P1 + s[j] - 'a' + 1) % MOD1;
            v[i][j].second = (v[i][j - 1].second * P2 + s[j] - 'a' + 1) % MOD2;
        }
    }
    std::cin >> m;
    for (Int i = 0; i < m; i++) {
        std::string s;
        std::cin >> s;
        Int hehe1, hehe2;
        hehe1 = hehe2 = s[0] - 'a' + 1;
        for (Int j = 1; j < size(s); j++) {
            hehe1 = (hehe1 * P1 + s[j] - 'a' + 1) % MOD1;
            hehe2 = (hehe2 * P2 + s[j] - 'a' + 1) % MOD2;
        }

        bool find = false;
        for (Int j = 0; j < n; j++) {
            if (sz[j] >= size(s) && v[j][size(s) - 1].first == hehe1 && v[j][size(s) - 1].second == hehe2) {
                std::cout << j + 1 << '\n';
                find = true;
                break;
            }
        }
        if (!find) {
            std::cout << -1 << '\n';
        }
    }
    return 0;
}
