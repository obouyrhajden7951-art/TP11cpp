/*
 * e1.cpp
 *
 *  Created on: 8 nov. 2026
 *      Author: hP
 */
#include <iostream>
using namespace std;

const double PI = 3.14159265358979;

class Forme {
public:
    virtual double aire() const = 0;   // méthode virtuelle pure
    virtual ~Forme() {}                // destructeur virtuel
};

class Cercle : public Forme {
    double rayon;
public:
    Cercle(double r) : rayon(r) {}
    double aire() const override { return PI * rayon * rayon; }
};

class Rectangle : public Forme {
    double longueur, largeur;
public:
    Rectangle(double l, double w) : longueur(l), largeur(w) {}
    double aire() const override { return longueur * largeur; }
};

int main() {
    int n;
    cout << "Nombre de formes : ";
    cin >> n;

    Forme** formes = new Forme*[n];

    for (int i = 0; i < n; i++) {
        int choix;
        cout << "\nForme " << i + 1 << " (1 = Cercle, 2 = Rectangle) : ";
        cin >> choix;

        if (choix == 1) {
            double r;
            cout << "Rayon : ";
            cin >> r;
            formes[i] = new Cercle(r);
        } else {
            double l, w;
            cout << "Longueur : ";
            cin >> l;
            cout << "Largeur : ";
            cin >> w;
            formes[i] = new Rectangle(l, w);
        }
    }

    cout << "\n--- Aires ---\n";
    for (int i = 0; i < n; i++)
        cout << "Forme " << i + 1 << " : " << formes[i]->aire() << endl;

    for (int i = 0; i < n; i++)
        delete formes[i];
    delete[] formes;

    return 0;
}
