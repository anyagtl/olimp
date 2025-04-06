
    #include <bits/extc++.h>


    #include <bits/extc++.h>
#define int long long

void dfs(std::vector<std::vector<int>> &g, std::vector<bool> &used, int n) {
    used[n] = true;
    for (int i = 0; i < size(g[n]); i++) {
        if (!used[g[n][i]]) {
            dfs(g, used, g[n][i]);
        }
    }
}

#все служат большому брату и все ему подчиняются
внутри компании строгая система также если А является подчиненным сотрудника Б то все подчиненные сотрудника А 
также считаются подчинен Б
Также для соц равенства Выявляются все сотрудники подчиненные Х среди них ищутся 2 сотрудника с наибольшими и два с наименьшими
зарплатами, из суммы а + b (наибольших) вычитаются a1 + b1 (сумма наименьших) при это сам Х в счет не принимается
Также зарплата сотрудника Х и всех его подчиненных может быть изменена на величину d 

signed main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);

    }

std::cin >>





    в первой строке вводится N колво сотрудников
    во второй вводится N - 1 число a_i (от 1 до N) это руководитель сотрудника номер i + 1
    руководитель компании имеет номер 1 каждый из сотрудников под подчинением 
    в третьей строке вводится N чисел b_i (b1 = 10^30
        10^4 <= b2.....bn <= 10^9) - зарплаты сотрудников

        в четвертой число Q количество запросов на которое необходимо ответить
        в следующих Q строках вводятся запросы в одном из двух форматов
        1. X (1 <= X >= N) запрос вычисления неравенства среди подчиненных
        Х выввести О если у Х нет подчиненных или он один
        2. X d запрос изменения зарплаты X и всех его подчиненных 
        на заданную величину

        гарантируется что будет хотябы один запрос 1 типа
    std::vector<bool> used(n, false);
 ввод
6
1 2 1 4 4
1000000000000000000000000000000 10005 10004 10003 10002 10001
4
1 1
1 3
2 4 10
1 1

вывод
6 (у главного в подчинении находятся все сотрудники 2,3,4,5,6 их зарплаты 10005, 10004, 10002, 10001
две макс 1005 и 1004 - две мин 1002 и 1001 = 6)
0  (в подчинении у сотрудника никого нет ответ на запрос 0)
16 (в подчинении сотрудника 4 находятся сотрудники 5 и 7 после изменения зарплат сотрудников 4 5 6 их зарплаты станут 10013 10012 10011
в подчнении у главного все сотрудники 2 3 4 5 6
их зарплаты 10005 10004 10013 10012 10011
две макс 10013 и 10012 а две мин 10005 и 10004 
ответом будет 10013 + 10012 - 10005 - 10004 = 16)



