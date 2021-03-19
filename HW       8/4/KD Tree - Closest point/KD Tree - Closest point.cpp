#include <bits/stdc++.h>
using namespace std;

struct point_comparator {
    int dimension;

    point_comparator(int dimension = 0) : dimension(dimension) {}

    const bool operator()(const vector<int>& point1, const vector<int>& point2) const {
        return point1[dimension] < point2[dimension];
    }
};

class kd_tree {
private:
    struct kd_node {
        vector<int> point;

        kd_node* left;
        kd_node* right;

        kd_node(const vector<int>& point) : point(point) {}
    };

    int k;
    kd_node* root;

    kd_node* build(vector<vector<int>>& points, int from, int to, int axis) {
        if (from > to) {
            return nullptr;
        }

        int mid = (from + to) / 2;
        nth_element(points.begin() + from,
            points.begin() + mid,
            points.begin() + to + 1,
            point_comparator(axis));

        kd_node* node = new kd_node(points[mid]);
        node->left = build(points, from, mid - 1, (axis + 1) % k);
        node->right = build(points, mid + 1, to, (axis + 1) % k);

        return node;
    }

public:
    kd_tree(vector<vector<int>> points, int dimensions) {
        k = dimensions;
        root = build(points, 0, points.size() - 1, 0);
    }

    /*
     * Each node in the KD tree is represented as follows:
     *
     *      struct kd_node {
     *          vector<int> point;
     *
     *          kd_node* left;
     *          kd_node* right;
     *      };
     *
     * The root of the tree is stored in the variable:
     *
     *      kd_tree* root;
     *
     * Each point in the tree has k coordinates (one for each dimension):
     *
     *      int k;
     *
     * The following method finds the distance to the point in the KD tree
     * that is closest to the given point.
     *
     * The method returns a single real number (of type dobule) that is
     * the distance to the closest point in the tree.
     */

    long double nearest(kd_node* root, const vector<int>& point, int depth, long double best) {
        if (root == NULL)
            return best;

        kd_node* goodSide = NULL;
        kd_node* badSide = NULL;

        long double currDistance = 0.0;
        for (int i = 0; i < k; i++) {
            currDistance += pow((root->point[i] - point[i]),2);
        }

        if (abs(currDistance) < abs(best)) //poluchavam otricatelni stoinost
            best = currDistance;

        if (point[depth % k] < root->point[depth % k]) {
            goodSide = root->left;
            badSide = root->right;
        }
        else {
            goodSide = root->right;
            badSide = root->left;
        }

        best = nearest(goodSide, point, depth + 1, best);

        long double distToAxis = point[depth % k] - root->point[depth % k];

        if (distToAxis * distToAxis <= best)
            best = nearest(badSide, point, depth + 1, best);

        return best;
    }

    long double closest_point(const vector<int>& point) {
        long double distance = 0.0;

        distance = sqrt(abs(nearest(root, point, 0, DBL_MAX)));

        return distance;
    }

};

vector<int> read_point(int k) {
    vector<int> point(k);
    for (int i = 0; i < k; i++) {
        cin >> point[i];
    }
    return point;
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<vector<int>> points;
    for (int i = 0; i < n; i++) {
        points.push_back(read_point(k));
    }

    kd_tree tree(points, k);

    int q;
    cin >> q;
    cout << fixed << setprecision(3);

    for (int i = 0; i < q; i++) {
        cout << abs(tree.closest_point(read_point(k))) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}