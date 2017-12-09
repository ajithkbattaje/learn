#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class BTree {
    int data;
    BTree *left, *right;
    public:
        BTree(vector<int>&dvec);
        BTree(int d):data(d),left(nullptr),right(nullptr) {}
        bool isSubtree(const BTree &that) const;
        bool operator == (const BTree &that) const;
        friend ostream & operator << (ostream &out, const BTree &bt);
};

/* Create a binary tree such that it is balanced at all time.
 * Achieve this by inserting nodes using BFS walk using a queue */
BTree::BTree(vector<int>&dvec):data(0),right(nullptr),left(nullptr)
{
    queue<BTree *> nextq;

    for (auto &d:dvec) {
        if (!nextq.empty()) {
            BTree *n = new BTree(d);

            BTree *p = nextq.front();

            if (p->left == nullptr) {
                p->left = n;
            } else if (p->right == nullptr) {
                p->right = n;
                nextq.pop();
            }
            nextq.push(n);
        } else {
            this->data = d;
            nextq.push(this);
        }
    }
}

bool BTree::operator == (const BTree &that) const
{
    if (((this->left == nullptr) != (that.left == nullptr)) ||
        ((this->right == nullptr) != (that.right == nullptr)))
        return false;

    if (this->data == that.data) {
        if (this->left && !(*(this->left) == *(that.left))) return false;
        if (this->right && !(*(this->right) == *(that.right))) return false;
        return true;
    }
    return false;
}

bool BTree::isSubtree(const BTree &that) const
{
    if ((this->data == that.data && *this == that)) {
        return true;
    } else {
        return((this->left && this->left->isSubtree(that)) || (this->right && this->right->isSubtree(that)));
    }
}

ostream & operator << (ostream &out, const BTree &bt)
{
    if (bt.left != nullptr) {
        out << bt.data << "->L: " << *bt.left;
    } else {
        out << bt.data << "->L: " << "null ";
    }

    if (bt.right != nullptr) {
        out << bt.data << "->R: " << *bt.right;
    } else {
        out << bt.data << "->R: " << "null ";
    }
    return(out);
}

int main()
{
    vector<int> v1, v2;
    int t;

    cout << "Enter elements of first tree\n";
    while (cin >> t) {
        v1.push_back(t);
    }
    cout << "Enter elements of second tree\n";
    cin.clear();
    while (cin >> t) {
        v2.push_back(t);
    }
    BTree t1(v1), t2(v2);
    cout << "Is subtree(t1->t2): " << t1.isSubtree(t2) << endl;
    return 0;
}
