#include <iostream>
#include <vector>

using namespace std;

constexpr int maxd=500;

class Solver {
    int nr, nc, lsq;
    int imatrix[maxd][maxd];
    int score_matrix[maxd][maxd] = {};
    int tones = 0;
    public:
        Solver(istream &in);
        int solve();
};

Solver::Solver(istream &in) {
    in >> nr >> nc;
    lsq = min(nr, nc);

    for(auto r=0;r<nr;r++) {
        for(auto c=0;c<nc;c++) {
            in >> imatrix[r][c];
            if (imatrix[r][c] == 1) {
                tones++;
            } 
        }
    }
}

int Solver::solve() {
    int max=score_matrix[0][0];
    
    for(auto s=1;s<lsq;s++) {
        for(auto r=0;r < nr-s;r++) {
            for(auto c=0;c < nc-s;c++) {
                int score = score_matrix[r][c];
                int nz=0,no=0;

                for(auto x=r;x<r+s+1;x++) {
                    if(imatrix[x][c+s+1] == 0) nz++;
                    else no++;
                }
                for(auto y=c;y<(c+s+1);y++) {
                    if(imatrix[r+s+1][y] == 0) nz++;
                    else no++;
                }
                score += (nz - no);
                score_matrix[r][c] = score;
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

