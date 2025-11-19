#define MAXN 200005

typedef struct Seg {
    long long seg[MAXN * 4] = {0}, lazy[MAXN * 4] = {0};

    void push_down(int now, int l, int r, int mid) {
        int l_child = now * 2, r_child = now * 2 + 1;
        int val = lazy[now];

        seg[l_child] += val * (mid - l + 1);
        seg[r_child] += val * (r - mid);
        lazy[l_child] += val;
        lazy[r_child] += val;
        
        lazy[now] = 0;
    }

    void built(int *a, int l, int r, int now = 1) {
        lazy[now] = 0;

        if (l == r) {
            seg[now] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        built(a, l, mid, now * 2);
        built(a, mid + 1, r, now * 2 + 1);

        seg[now] = seg[now * 2] + seg[now * 2 + 1];
    }

    void update(int ql, int qr, int val, int l, int r, int now = 1) {
        if (ql <= l && r <= qr) {
            seg[now] += val * (r - l + 1);
            lazy[now] += val;
            return;
        }
        int mid = (l + r) / 2;

        push_down(now, l, r, mid);
        
        if (ql <= mid) update(ql, qr, val, l, mid, now * 2);
        if (mid + 1 <= qr) update(ql, qr, val, mid + 1, r, now * 2 + 1);

        seg[now] = seg[now * 2] + seg[now * 2 + 1];
    }

    int query(int ql, int qr, int l, int r, int now = 1) {
        if (ql <= l && r <= qr) return seg[now];

        int mid = (l + r) / 2;

        push_down(now, l, r, mid);
        
        if (qr <= mid) {
            return query(ql, qr, l, mid, now * 2);
        } else if (mid + 1 <= ql) {
            return query(ql, qr, mid + 1, r, now * 2 + 1);
        } else {
            return query(ql, qr, l, mid, now * 2) + query(ql, qr, mid + 1, r, now * 2 + 1);
        }
    }
} Seg;

/*
Usage:
    Seg seg;
    seg.built(a, 1, n);
    seg.update(ql, qr, val, 1, n);
    seg.query(ql, qr, 1, n);

Notice:
    if occur segmentation fault, please put seg array and lazy array in Global.

Needs To Do:
    define MAXN
*/