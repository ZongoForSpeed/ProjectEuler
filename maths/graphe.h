#include <vector>
#include <map>
#include <limits>
#include <set>
#include <optional>
#include <deque>
#include <queue>
#include <functional>

namespace graphe {
    typedef unsigned long long nombre;
    typedef std::vector<nombre> vecteur;

    class Tarjan {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"

        struct Sommet {
            nombre n;
            nombre lowlink;
            bool onStack;

            std::optional<nombre> index;

            explicit Sommet(nombre _n) : n(_n), lowlink(std::numeric_limits<nombre>::max()), onStack(false) {}
        };

#pragma clang diagnostic pop

        void strongconnect(Sommet &v);

    public:
        std::vector<std::set<nombre>> resultat;

        explicit Tarjan(const std::map<nombre, vecteur> &g);

        void algorithme();

    private:
        nombre index;
        std::map<nombre, vecteur> graphe;
        std::vector<nombre> S;
        std::map<nombre, Sommet> sommets;
    };

    class Dijkstra {
    public:
        typedef std::pair<nombre, nombre> paire;
        typedef std::map<nombre, std::vector<paire>> graphe;

        vecteur resultat;

        Dijkstra(graphe _G, nombre _debut, nombre _fin);

        nombre algorithme();

    private:
        graphe G;
        nombre debut;
        nombre fin;
    };

    class Kruskal {
    public:
        typedef std::tuple<nombre, nombre, nombre> arete;
        typedef std::vector<arete> aretes;

        explicit Kruskal(aretes _A);

        aretes algorithme();

    private:
        aretes A;
    };

    template<typename E>
    struct Noeud {
        Noeud(E _noeud, double _cout, double _heuristic) :
                noeud(_noeud), cout(_cout), heuristic(_heuristic) {}

        E noeud;
        double cout;
        double heuristic;

        bool operator<(const Noeud &n) const {
            return noeud < n.noeud;
        }
    };

    template<typename E, typename G, typename D>
    double algorithme_a_star(const E &start, const E &end, const G &graph, const D &distance) {
        std::set<E> closedList;
        auto compare = [](const Noeud<E> &a, const Noeud<E> &b) {
            return a.cout > b.cout;
        };
        std::priority_queue<Noeud<E>, std::deque<Noeud<E>>, decltype(compare)> queue;
        queue.emplace(start, 0.0, 0.0);
        while (!queue.empty()) {
            Noeud<E> courant = queue.top();
            queue.pop();

            if (courant.noeud == end) {
                return courant.cout;
            }

            if (auto it = closedList.insert(courant.noeud);it.second) {
                auto moves = graph(courant.noeud);
                for (auto move: moves) {
                    if (!closedList.contains(move)) {
                        double d1 = distance(courant.noeud, move);
                        double d2 = distance(move, end);
                        queue.emplace(move, courant.cout + d1, courant.cout + d1 + d2);
                    }
                }
            }
        }

        return std::numeric_limits<double>::max();
    }

    template<typename T>
    class SegmentTree {

        size_t size_;
        std::vector<T> storage_;
        std::function<T(T, T)> op_;
    public:
        SegmentTree(size_t n, std::function<T(T, T)> op)
                : op_(std::move(op)) {
            size_ = 1;
            while (size_ < n) {
                size_ <<= 1;
            }
            storage_.resize(2 * size_);
        }

        SegmentTree(const std::vector<T> &data, std::function<T(T, T)> op)
                : SegmentTree(data.size(), op) {
            for (size_t i = 0; i < data.size(); ++i) {
                set(i, data[i]);
            }
        }

        void set(size_t index, const T &value) {
            index += size_;
            while (index) {
                storage_[index] = op_(storage_[index], value);
                index >>= 1;
            }
        }

        T get(size_t index) const {
            return storage_[index + size_];
        }

        T get(size_t left, size_t right) const {
            T result = 0;
            left += size_;
            right += size_;
            while (left < right) {
                if (left & 1) {
                    result = op_(result, storage_[left]);
                    ++left;
                }
                if (right & 1) {
                    --right;
                    result = op_(result, storage_[right]);
                }
                left >>= 1;
                right >>= 1;
            }
            return result;
        }
    };

}
