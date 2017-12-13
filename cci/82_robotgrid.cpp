#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Path;

class Grid {
    int nrows, ncols;
    vector<vector<bool>> gridmap;
    void findpaths(int r, int c, vector<Path> &paths);
    bool isreachablefrom(int r, int c);
    public:
        Grid(istream &ins);
        void findpaths(vector<Path> &paths);
        friend ostream & operator << (ostream &out, const Grid &g);
};

enum class Move {
    down,
    right,
};

class Path {
    list<Move> moves;
    public:
        Path & addmove(const Move &m);
        friend ostream & operator << (ostream &out, const Path &p);
};

Grid::Grid(istream &ins)
{
    int br, bc;

    ins >> nrows >> ncols;

    gridmap.resize(nrows);
    for (auto b=0;b<nrows;b++) {
        gridmap.at(b).resize(ncols);
    }

    while (ins >> br >> bc) {
        gridmap.at(br).at(bc) = true;
    }
}

ostream & operator << (ostream &out, const Grid &g) {
    cout << "Grid " << g.nrows << "x" << g.ncols << "\n";
    for (auto r=0;r<g.nrows;r++) {
        for (auto c=0;c<g.ncols;c++) {
            if (g.gridmap.at(r).at(c) == true) out << "X "; 
            else out << "O ";
        }
        cout << "\n";
    }
    return out;
}

bool Grid::isreachablefrom(int r, int c) {
    return (r >= 0 && c >= 0 && gridmap.at(r).at(c) == false);
}

void Grid::findpaths(int r, int c, vector<Path> &paths) {
    vector<Path> tpaths, lpaths;

    if (r == 0 && c == 0) return;

    if (isreachablefrom(r-1, c)) {
        if (r==1 && c==0) {
            paths.push_back(Path().addmove(Move::down));
        } else {
            findpaths(r-1, c, tpaths);
        }
    }
    if (isreachablefrom(r, c-1)) {
        if (r==0 && c==1) {
            paths.push_back(Path().addmove(Move::right));
        } else {
            findpaths(r, c-1, lpaths);
        }
    }

    for (auto &p:tpaths) {
        paths.push_back(p.addmove(Move::down));
    }
    for (auto &p:lpaths) {
        paths.push_back(p.addmove(Move::right));
    }
}

void Grid::findpaths(vector<Path> &paths) {
    this->findpaths(nrows-1, ncols-1, paths);
}

Path & Path::addmove(const Move &m) {
    moves.push_back(m);
    return(*this);
}

ostream & operator << (ostream &out, const Path &p) {
    for (const auto &m:p.moves) {
        if (m == Move::down) {
            out << "D:";
        } else {
            out << "R:";
        }
    }
    return out;
}

int main()
{
    Grid g(cin);
    vector<Path> paths;

    cout << "Grid Info: \n" << g << endl;
    g.findpaths(paths);
    for (const auto &p : paths) {
        cout << "Path: " << p << "\n";
    }
    return(0);
}
