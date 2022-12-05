#include <iostream>
#include <string>
#include <random>
#include <unistd.h>

using namespace std;

void table(string aux[9][9]) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(j == 3 || j == 6) cout << "| ";
            cout << aux[i][j] << " ";
        }
        if(i == 2 || i == 5) cout << endl << "-----   -----   -----";
        cout << endl;
    }
}

void numFind(string num, string filled[9]) {
    for(int i = 0; i < 9; i++) {
        if(to_string(i + 1) == num) filled[i] = num;
    }
}

int block(string filled[9]) {
    int count = 0;
    for(int i = 0; i < 9; i++) {
        if(to_string(i + 1) == filled[i]) count++;
    }
    if(count > 7) return 1;
    return 0;
}

int check(string aux[9][9], int x, int y, string num) {
    for(int i = 0; i < 9; i++) {
        if(i != y && aux[i][x] == num) {
            return 1;
        }
    }
    for(int i = 0; i < 9; i++) {
        if(i != x && aux[y][i] == num) {
            return 1;
        }
    }
    int ai, af, bi, bf;
    if(0 <= x && x <= 2 && 0 <= y && y <= 2) {
        ai = 0;
        af = 2;
        bi = 0;
        bf = 2;
    }
    if(3 <= x && x <= 5 && 0 <= y && y <= 2) {
        ai = 3;
        af = 5;
        bi = 0;
        bf = 2;
    }
    if(6 <= x && x <= 8 && 0 <= y && y <= 2) {
        ai = 6;
        af = 8;
        bi = 0;
        bf = 2;
    }
    if(0 <= x && x <= 2 && 3 <= y && y <= 5) {
        ai = 0;
        af = 2;
        bi = 3;
        bf = 5;
    }
    if(3 <= x && x <= 5 && 3 <= y && y <= 5) {
        ai = 3;
        af = 5;
        bi = 3;
        bf = 5;
    }
    if(6 <= x && x <= 8 && 3 <= y && y <= 5) {
        ai = 6;
        af = 8;
        bi = 3;
        bf = 5;
    }
    if(0 <= x && x <= 2 && 6 <= y && y <= 8) {
        ai = 0;
        af = 2;
        bi = 6;
        bf = 8;
    }
    if(3 <= x && x <= 5 && 6 <= y && y <= 8) {
        ai = 3;
        af = 5;
        bi = 6;
        bf = 8;
    }
    if(6 <= x && x <= 8 && 6 <= y && y <= 8) {
        ai = 6;
        af = 8;
        bi = 6;
        bf = 8;
    }
    for(int k = bi; k <= bf; k++) {
        for(int l = ai; l <= af; l++) {
            if(k != y && l != x && aux[k][l] == num) return 1;
        }
    }
    return 0;
}

string value() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(1, 9);
    string value = to_string(distr(gen));
    return value;
}

int fill(string aux[9][9]) {
    int rep = 0;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            string filled[9];
            do {
                aux[i][j] = value();
                numFind(aux[i][j], filled);
                //table(aux);
                //if(block(filled) == 1) return 1;
                if(rep > 100 && block(filled) == 1) return 1;
                rep++;
            } while(check(aux, j, i, aux[i][j]) == 1);
            rep = 0;
        }
    }
    return 0;
}

void empty(string aux[9][9]) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            aux[i][j] = "0";
        }
    }
}

void copy(string from[9][9], string to[9][9]) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            to[i][j] = from[i][j];
        }
    }
}

void position(int coords[2]) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, 8);
    coords[0] = distr(gen);
    coords[1] = distr(gen);
}

int randNum(int l, int h) {
    int n;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(l, h);
    n = distr(gen);
    return n;
}

void ready(string aux[9][9]) {
    int coords[2];
    int amount = randNum(30, 40);
    for(int i = 0; i < amount; i++) {
        position(coords);
        aux[coords[0]][coords[1]] = " ";
    }
}

int checkPos(string aux[9][9], string num, int x, int y) {
    if(aux[y][x] != num) return 1;
    return 0;
}

int main() {
    string line[9][9];
    empty(line);
    int attempts = 0,h = 0, l = 0;
    
    cout << "filling table" << endl;
    while(fill(line) == 1) {
        attempts++;
        empty(line);
    }

    string play[9][9];
    copy(line, play);

    cout << endl;
    ready(play);
    table(play);

    int x, y;
    string value, status = "play";

    do {
        cout << endl << "coords: ";
        cin >> x >> y;
        cin >> value;
        if(checkPos(line, value, x, y) == 0) {
            play[y][x] = value;
            cout << endl;
            table(play);
        }
    } while(status == "play");

    return 0;
}