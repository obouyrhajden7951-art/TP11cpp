/*
 * e2.cpp
 *
 *  Created on: 8 nov. 2026
 *      Author: hP
 */

#include <iostream>
using namespace std;

class Paiement {
public:
    virtual void effectuerPaiement(double montant) = 0;
    virtual ~Paiement() {}
};

class PaiementCarte : public Paiement {
public:
    void effectuerPaiement(double montant) override {
        cout << "Paiement de " << montant << " DH par carte bancaire." << endl;
    }
};

class PaiementEspece : public Paiement {
public:
    void effectuerPaiement(double montant) override {
        cout << "Paiement de " << montant << " DH en especes." << endl;
    }
};

int main() {
    const int N = 4;
    Paiement* paiements[N];

    paiements[0] = new PaiementCarte();
    paiements[1] = new PaiementEspece();
    paiements[2] = new PaiementCarte();
    paiements[3] = new PaiementEspece();

    double montants[N] = {150.0, 75.5, 300.0, 20.0};

    for (int i = 0; i < N; i++)
        paiements[i]->effectuerPaiement(montants[i]);   // polymorphisme

    for (int i = 0; i < N; i++)
        delete paiements[i];

    return 0;
}


