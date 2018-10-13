#include<iostream>
#include "optional.h"

using namespace std;

int main(){
    optional<int> a(3);
    optional<int> b;

    cout << "swap\n";
    if (a){
        cout << 'a' << *a << endl;
    }
    if (b){
        cout << 'b' << *b << endl;
    }
    swap(a, b);
    cout << endl;
    if (a){
        cout << 'a' << *a << endl;
    }
    if (b){
        cout << 'b' << *b << endl;
    }

    b = 2;
    cout << "clear\n";
    if (a){
        cout << 'a' << *a << endl;
    }
    if (b){
        cout << 'b' << *b << endl;
    }
    b.clear();
    cout << endl;
    if (a){
        cout << 'a' << *a << endl;
    }
    if (b){
        cout << 'b' << *b << endl;
    }
    cout << endl;

    cout << "* and =\n";
    b = 3;
    a = b;
    (*a)++;

    if (a){
        cout << 'a' << *a << endl;
    }
    if (b){
        cout << 'b' << *b << endl;
    }

}

