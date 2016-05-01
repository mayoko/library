// Euler-Tour
const int MAXSIZE = 200020;
int BEGIN[MAXSIZE], END[MAXSIZE];
vector<int> euler_tour;
int K;
vector<vi> G;

void createEulerTour(int v, int p) {
    BEGIN[v] = K++;
    euler_tour.push_back(v);
    for (int el : G[v]) {
        if (el == p) continue;
        createEulerTour(el, v);
        euler_tour.push_back(v);
        K++;
    }
    END[v] = K;
}
