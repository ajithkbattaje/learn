#include <iostream>
#include <vector>

using namespace std;

constexpr int maxd=500;

class Solver {
    int nr, nc, lsq;
    int imatrix[maxd][maxd];
    int nones[maxd][maxd] = {};
    int tones = 0;
    void showmatrix();
    public:
        Solver(istream &in);
        int solve();
};

void Solver::showmatrix() {
    for(auto r=0;r<nr;r++) {
        for(auto c=0;c<nc;c++) {
            cout << nones[r][c] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

Solver::Solver(istream &in) {
    in >> nr >> nc;
    lsq = min(nr, nc);

    for(auto r=0;r<nr;r++) {
        for(auto c=0;c<nc;c++) {
            in >> imatrix[r][c];
            if (imatrix[r][c] == 1) {
                tones++;
                nones[r][c] = 1;
            } 
        }
    }
}

int Solver::solve() {
    int max = (tones == nr * nc ? tones - 1 : tones + 1);

    for(auto s=1;s<lsq;s++) {
        for(auto r=0;r < nr-s;r++) {
            for(auto c=0;c < nc-s;c++) {
                int nz=0,no=0,score;

                for(auto y=c;y<=c+s;y++) {
                    if(imatrix[r+s][y] == 0) nz++;
                    else no++;
                }
                for(auto x=r;x<=(r+s-1);x++) {
                    if(imatrix[x][c+s] == 0) nz++;
                    else no++;
                }
                nones[r][c] += no;
                score = tones - nones[r][c] + ((s+1)*(s+1) - nones[r][c]);
                if (score > max) max = score;
            }
        }
    }
    return(max);
}

int main()
{
    Solver *s = new Solver(cin);
    cout << s->solve() << "\n";
    delete(s);
}

