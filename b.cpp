#include <bits/extc++.h>

#define Int long long
//#define FAST_ALLOCATOR_MEMORY 2e8
#define fast_io

#ifdef FAST_ALLOCATOR_MEMORY
    int allocator_pos = 0;
    char allocator_memory[(int)FAST_ALLOCATOR_MEMORY];
    inline void * operator new ( size_t n ) {
        char *res = allocator_memory + allocator_pos;
        allocator_pos += n;
        assert(allocator_pos <= (int)FAST_ALLOCATOR_MEMORY);
        return (void *)res;
    }
    inline void operator delete ( void * ) noexcept { }
    inline void operator delete ( void *, size_t ) noexcept { }
    //inline void * operator new [] ( size_t ) { assert(0); }
    //inline void operator delete [] ( void * ) { assert(0); }
#endif


template <class T = int> inline T readInt();
inline double readDouble();
inline int readUInt();
inline int readChar();
inline void readWord( char *s );
inline bool readLine( char *s );
inline bool isEof();
inline int getChar(); 
inline int peekChar();
inline bool seekEof();
inline void skipBlanks();

template <class T> inline void writeInt( T x, char end = 0, int len = -1 );
inline void writeChar( int x );
inline void writeWord( const char *s );
inline void writeDouble( double x, int len = 0 );
inline void flush();

static struct buffer_flusher_t {
    ~buffer_flusher_t() {
        flush();
    }
} buffer_flusher;

struct node {
    int val;
    bool f;

    node merge(node oth) const {
        node r = oth;
        r.val += val;
        return r;
    }

    node() {
        f = false;
    }
    node(int _val) {
        *this = node();
        val = _val;
    }
};

struct segtree {
    std::vector<node> tree;
    std::vector<node> upd;
    std::vector<node> eq;
    node def = node(0);

    void build(std::vector<node> &arr, int l, int r, int v) {
        if (l == r - 1) {
            tree[v] = arr[l];
            return;
        }
        int m = l + (r - l) / 2;
        int v2 = v << 1;
        build(arr, l, m, v2 + 1);
        build(arr, m, r, v2 + 2);
        tree[v] = tree[v2 + 1].merge(tree[v2 + 2]);
    }

    void push(int l, int r, int v) {
        if (l == r - 1) {
            tree[v].val += upd[v].val;;
            upd[v] = def;

            if (eq[v].f) {
                tree[v] = node(eq[v].val);
                eq[v].f = false;
            }

        } else {
            int v2 = v << 1;
            tree[v].val += upd[v].val * (r - l);
            upd[v2 + 1].val += upd[v].val;
            upd[v2 + 2].val += upd[v].val;
            upd[v] = def;

            if (eq[v].f) {
                tree[v].val = eq[v].val * (r - l);
                eq[v2 + 1] = eq[v2 + 2] = eq[v];
                eq[v].f = false;
            }
        }
    }

    node get(int ql, int qr, int l, int r, int v) {
        if (ql >= r || qr <= l) {
            return def;
        }

        push(l, r, v);
        if (l >= ql && r <= qr) {
            return tree[v];
        }
        int m = l + (r - l) / 2;
        int v2 = v << 1;

        node ans = get(ql, qr, l, m, v2 + 1).merge(get(ql, qr, m, r, v2 + 2));
        tree[v] = tree[v2 + 1].merge(tree[v2 + 2]);
        return ans;
    }

    void update(int ql, int qr, node u, int l, int r, int v) {
        if (ql >= r || qr <= l) {
            return;
        }
        push(l, r, v);

        if (l >= ql && r <= qr) {
            upd[v].val += u.val;
            push(l, r, v);
            return;
        }

        int m = l + (r - l) / 2;
        int v2 = v << 1;
        update(ql, qr, u, l, m, v2 + 1);
        update(ql, qr, u, m, r, v2 + 2);
        tree[v] = tree[v2 + 1].merge(tree[v2 + 2]);
    }

    void eq_upd(int ql, int qr, node u, int l, int r, int v) {
        if (ql >= r || qr <= l) {
            return;
        }
        push(l, r, v);

        if (l >= ql && r <= qr) {
            eq[v] = u;
            eq[v].f = true;
            push(l, r, v);
            return;
        }

        int m = l + (r - l) / 2;
        int v2 = v << 1;
        eq_upd(ql, qr, u, l, m, v2 + 1);
        eq_upd(ql, qr, u, m, r, v2 + 2);
        tree[v] = tree[v2 + 1].merge(tree[v2 + 2]);
    }

    segtree(int n, std::vector<node> &arr) {
        tree.resize(n << 2);
        upd.resize(n << 2);
        eq.resize(n << 2);
        build(arr, 0, n, 0);
    }
};



std::mt19937_64 gen(std::chrono::steady_clock::now().time_since_epoch().count());
const int INF = std::numeric_limits<int>::max();

inline Int randint(Int le, Int ri) {
    return le + (gen() % (ri - le + 1));
}

template<typename T1, typename T2>
inline void mineq(T1 &a, const T2 &b) {
    if (a > b) {
        a = b;
    }
}

template<typename T1, typename T2>
inline void maxeq(T1 &a, const T2 &b) {
    if (a < b) {
        a = b;
    }
}

template<typename T>
inline T sig(T a) {
    return (a == 0 ? 0 : (a > 0 ? 1 : -1));
}

template<typename T>
inline T _abs(T x) {
    return x >= 0 ? x : -x;
}


signed main() {
    int n;
    n = readInt();
    std::vector<std::pair<int, int>> v(n);
    for (int i = 0; i < n; i++) {
        v[i].first = readInt();
        v[i].second = i;
    }

    std::vector<node> l(n);
    std::vector<node> r(n);

    for (int i = 0; i < n; i++) {
        l[i].val = i + 1;
        r[i].val = n - i;
    }

    segtree sgl = segtree(n, l);
    segtree sgr = segtree(n, r);

    std::sort(v.begin(), v.end(), [](std::pair<int, int> a, std::pair<int, int> b) { return a.first < b.first; });
    int ans = 0;

    for (int i = 0; i < n; i++) {
        ans += sgr.get(v[i].second, v[i].second + 1, 0, n, 0).val * v[i].first;
        sgl.update(v[i].second, n, node(-1), 0, n, 0);

        ans += sgl.get(v[i].second, v[i].second + 1, 0, n, 0).val * v[i].first;
        sgl.update(0, v[i].second + 1, node(-1), 0, n, 0);

        sgr.eq_upd(v[i].second, v[i].second + 1, node(0), 0, n, 0);
        sgl.eq_upd(v[i].second, v[i].second + 1, node(0), 0, n, 0);
    }

    writeInt(ans);
    writeChar('\n');
    return 0;
}

static const int buf_size = 4096;

static unsigned char buf[buf_size];
static int buf_len = 0, buf_pos = 0;

inline bool isEof() {
    if (buf_pos == buf_len) {
        buf_pos = 0;
        buf_len = fread(buf, 1, buf_size, stdin);
        if (buf_pos == buf_len) {
            return 1;
        }
    }
    return 0;
}

inline int getChar() {
    return isEof() ? -1 : buf[buf_pos++];
}

inline int peekChar() {
    return isEof() ? -1 : buf[buf_pos];
}

inline bool seekEof() {
    int c;
    while ((c = peekChar()) != -1 && c <= 32) {
        buf_pos++;
    }
    return c == -1;
}

inline void skipBlanks() {
    while (!isEof() && buf[buf_pos] <= 32U) {
        buf_pos++;
    }
}

inline int readChar() {
    int c = getChar();
    while (c != -1 && c <= 32) {
        c = getChar();
    }
    return c;
}

inline int readUInt() {
    int c = readChar(), x = 0;
    while ('0' <= c && c <= '9') {
        x = x * 10 + c - '0';
        c = getChar();
    }
    return x;
}

template <class T>
inline T readInt() {
    int s = 1, c = readChar();
    T x = 0;
    if (c == '-') {
        s = -1, c = getChar();
    } else if (c == '+') {
        c = getChar();
    }
    while ('0' <= c && c <= '9') {
        x = x * 10 + c - '0';
        c = getChar();
    }
    return s == 1 ? x : -x;
}

inline double readDouble() {
    int s = 1, c = readChar();
    double x = 0;
    if (c == '-') {
        s = -1;
        c = getChar();
    }
    while ('0' <= c && c <= '9') {
        x = x * 10 + c - '0';
        c = getChar();
    }
    if (c == '.') {
        c = getChar();
        double coef = 1;
        while ('0' <= c && c <= '9') {
            x += (c - '0') * (coef *= 1e-1);
            c = getChar();
        }
    }
    return s == 1 ? x : -x;
}

inline void readWord( char *s ) {
    int c = readChar();
    while (c > 32) {
        *s++ = c;
        c = getChar();
    }
    *s = 0;
}

inline bool readLine( char *s ) {
    int c = getChar();
    while (c != '\n' && c != -1) {
        *s++ = c;
        c = getChar();
    }
    *s = 0;
    return c != -1;
}


static int write_buf_pos = 0;
static char write_buf[buf_size];

inline void writeChar( int x ) {
    if (write_buf_pos == buf_size) {
        fwrite(write_buf, 1, buf_size, stdout);
        write_buf_pos = 0;
    }
    write_buf[write_buf_pos++] = x;
}

inline void flush() {
    if (write_buf_pos) {
        fwrite(write_buf, 1, write_buf_pos, stdout);
        write_buf_pos = 0;
        fflush(stdout);
    }
}

template <class T>
inline void writeInt( T x, char end, int output_len ) {
    if (x < 0) {
        writeChar('-');
        x = -x;
    }

    char s[24];
    int n = 0;
    while (x || !n) {
        s[n++] = '0' + x % 10, x /= 10;
    }
    while (n < output_len) {
        s[n++] = '0';
    }
    while (n--) {
        writeChar(s[n]);
    }
    if (end) {
        writeChar(end);
    }
}

inline void writeWord( const char *s ) {
    while (*s) {
        writeChar(*s++);
    }
}

inline void writeDouble( double x, int output_len ) {
    if (x < 0) {
        writeChar('-');
        x = -x;
    }
    assert(x <= (1LLU << 63) - 1);
    long long t = (long long)x;
    writeInt(t), x -= t;
    writeChar('.');
    for (int i = output_len - 1; i > 0; i--) {
        x *= 10;
        t = std::min(9, (int)x);
        writeChar('0' + t);
        x -= t;
    }
    x *= 10;
    t = std::min(9, (int)(x + 0.5));
    writeChar('0' + t);
}


// vim config
/*
syntax on
colorscheme elflord

set showmatch               " show matching 
set ignorecase              " case insensitive 
set hlsearch                " highlight search 
set incsearch               " incremental search
set tabstop=4               " number of columns occupied by a tab 
set softtabstop=4           " see multiple spaces as tabstops so <BS> does the right thing
set shiftwidth=4             " width for autoindents
"➜⠀·
set list listchars=tab:➜⠀,space:·
set expandtab

set number                  " add line numbers
filetype plugin indent on   "allow auto-indenting depending on file type syntax on" syntax highlighting

set clipboard=unnamed   " using system clipboard
filetype plugin on
"set cursorline              " highlight current cursorline
set ttyfast                 " Speed up scrolling in Vim
*/
