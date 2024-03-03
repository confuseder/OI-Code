#include <bits/stdc++.h>
#include <valarray>
using namespace std;

template <typename T>
class Splay {
  private:
    struct node {
        T      data;
        size_t size, cnt;
        node  *left, *right, *father, **root;

        node()
            : data(0), size(0), cnt(0), left(nullptr), right(nullptr), father(nullptr), root(nullptr) {}

        node(const T _val, node *_fa, node **_root)
            : data(_val), size(1), cnt(1), left(nullptr), right(nullptr), father(_fa), root(_root) {}

        ~node() {
            if (left != nullptr) {
                delete left;
            }
            if (right != nullptr) {
                delete right;
            }
        }

        node *&child(bool x) {
            return !x ? left : right;
        }

        bool relation() {
            return (this == this->father->left) ? false : true;
        }

        size_t lsize() {
            return (left != nullptr) ? this->left->size : 0;
        }

        size_t rsize() {
            return (right != nullptr) ? this->right->size : 0;
        }

        void push_up() {
            this->size = lsize() + this->cnt + rsize();
        }

        void rotate() {
            node *old   = this->father;
            bool  relat = this->relation();

            if (old->father != nullptr) {
                old->father->child(old->relation()) = this;
            }
            father = old->father;

            if (child(relat ^ 1) != nullptr) {
                child(relat ^ 1)->father = old;
            }
            old->child(relat) = child(relat ^ 1);

            child(relat ^ 1) = old;
            old->father      = this;

            old->push_up();
            this->push_up();
        }

        void splay(node *target = nullptr) {
            while (father != target) {
                if (father->father == target) {
                    rotate();
                } else if (relation() == father->relation()) {
                    father->rotate();
                    rotate();
                } else {
                    rotate();
                    rotate();
                }
            }

            if (target == nullptr) *root = this;
        }

        node *pre() {
            node *res = left;
            while (res->right != nullptr) {
                res = res->right;
            }
            return res;
        }

        node *next() {
            node *res = right;
            while (res->left != nullptr) {
                res = res->left;
            }
            return res;
        }
    } *root;

    node *_insert(const T &value) {
        node **tag = &root, *fa = nullptr;

        while (*tag != nullptr && (*tag)->data != value) {
            fa = *tag;
            fa->size++;

            if (value < fa->data) {
                tag = &fa->left;
            } else {
                tag = &fa->right;
            }
        }

        if (*tag == nullptr) {
            *tag = new node(value, fa, &root);
        } else {
            (*tag)->size++;
            (*tag)->cnt++;
        }

        (*tag)->splay();

        return root;
    };

    node *find(const T &value) {
        node *node = root;

        while (node != nullptr && value != node->data) {
            if (value < node->data) {
                node = node->left;
            } else {
                node = node->right;
            }
        }

        if (node != nullptr) {
            node->splay();
        }

        return node;
    }

    void erase(node *u) {
        if (u == nullptr) return;

        if (u->cnt > 1) {
            u->splay();
            u->cnt--;
            u->size--;

            return;
        }

        node *pred = u->pre(),
             *succ = u->next();

        pred->splay();
        succ->splay(pred);

        delete succ->left;
        succ->left = nullptr;

        succ->push_up();
        pred->push_up();
    }

  public:
    Splay()
        : root(nullptr) {
        insert(std::numeric_limits<T>::min());
        insert(std::numeric_limits<T>::max());
    }

    ~Splay() {
        delete root;
    }

    void insert(const T &value) {
        _insert(value);
    }

    void erase(const T &value) {
        erase(find(value));
    }

    unsigned rank(const int &value) {
        node *node = find(value);

        if (node == nullptr) {
            node         = _insert(value);
            unsigned res = node->lsize();
            erase(node);

            return res;
        }

        return node->lsize();
    }

    const T &select(unsigned k) {
        node *node = root;

        while (k < node->lsize() || k >= node->lsize() + node->cnt) {
            if (k < node->lsize()) {
                node = node->left;
            } else {
                k -= node->lsize() + node->cnt;
                node = node->right;
            }
        }

        node->splay();

        return node->data;
    }

    const T &pre(const T &value) {
        node *tag = find(value);

        if (tag == nullptr) {
            tag    = _insert(value);
            T &res = tag->pre()->data;
            erase(tag);
            return res;
        }

        return tag->pre()->data;
    }

    const T &next(const T &value) {
        node *tag = find(value);

        if (tag == nullptr) {
            tag    = _insert(value);
            T &res = tag->next()->data;
            erase(tag);
            return res;
        }

        return tag->next()->data;
    }
};

int              n, m;
int              idx = 1, cnt;
int              op_n[200005], op_m[200005];
Splay<long long> splay;

int main() {

    // freopen("P1801.in", "r", stdin);
    // freopen("P1801.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> op_n[i];
    }

    for (int i = 1; i <= m; i++) {
        cin >> op_m[i];
    }

    for (int i = 1; i <= n; i++) {
        splay.insert(op_n[i]);
        while (op_m[idx] == i) {
            idx++;
            cout << splay.select(++cnt) << endl;
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}