/*
 * e4.cpp
 *
 *  Created on: 8 nov. 2026
 *      Author: hP
 */


#include <iostream>
#include <string>
#include <vector>
using namespace std;

class NoeudFichier {
protected:
    string nomNoeud;
public:
    NoeudFichier(const string& n) : nomNoeud(n) {}
    string nom() const { return nomNoeud; }
    virtual int taille() const = 0;                       // méthode pure
    virtual void afficher(int niveau = 0) const = 0;
    virtual ~NoeudFichier() {}
};

class Fichier : public NoeudFichier {
    int tailleFichier;
public:
    Fichier(const string& n, int t) : NoeudFichier(n), tailleFichier(t) {}
    int taille() const override { return tailleFichier; }
    void afficher(int niveau = 0) const override {
        cout << string(niveau * 2, ' ') << "- " << nomNoeud
             << " (" << tailleFichier << " Ko)" << endl;
    }
};

class Dossier : public NoeudFichier {
    vector<NoeudFichier*> enfants;
public:
    Dossier(const string& n) : NoeudFichier(n) {}

    ~Dossier() {
        for (size_t i = 0; i < enfants.size(); i++)
            delete enfants[i];
    }

    void ajouter(NoeudFichier* n) { enfants.push_back(n); }

    int taille() const override {
        int total = 0;
        for (size_t i = 0; i < enfants.size(); i++)
            total += enfants[i]->taille();
        return total;
    }

    void afficher(int niveau = 0) const override {
        cout << string(niveau * 2, ' ') << "+ " << nomNoeud
             << "/ (" << taille() << " Ko)" << endl;
        for (size_t i = 0; i < enfants.size(); i++)
            enfants[i]->afficher(niveau + 1);
    }

    // Recherche récursive d'un dossier par son nom
    Dossier* chercher(const string& n) {
        if (nomNoeud == n) return this;
        for (size_t i = 0; i < enfants.size(); i++) {
            Dossier* d = dynamic_cast<Dossier*>(enfants[i]);
            if (d) {
                Dossier* res = d->chercher(n);
                if (res) return res;
            }
        }
        return nullptr;
    }
};

int main() {
    Dossier racine("racine");
    Dossier* courant = &racine;
    int choix;

    do {
        cout << "\n=== Systeme de fichiers virtuel ===\n"
             << "Dossier courant : " << courant->nom() << "\n"
             << "1. Ajouter un fichier\n"
             << "2. Ajouter un sous-dossier\n"
             << "3. Changer de dossier courant\n"
             << "4. Afficher l'arborescence\n"
             << "5. Afficher la taille d'un dossier\n"
             << "0. Quitter\n"
             << "Choix : ";
        cin >> choix;

        if (choix == 1) {
            string n; int t;
            cout << "Nom du fichier : ";
            cin >> n;
            cout << "Taille (Ko) : ";
            cin >> t;
            courant->ajouter(new Fichier(n, t));
        }
        else if (choix == 2) {
            string n;
            cout << "Nom du dossier : ";
            cin >> n;
            courant->ajouter(new Dossier(n));
        }
        else if (choix == 3) {
            string n;
            cout << "Nom du dossier a ouvrir : ";
            cin >> n;
            Dossier* d = racine.chercher(n);
            if (d) courant = d;
            else cout << "Dossier introuvable." << endl;
        }
        else if (choix == 4) {
            racine.afficher();
        }
        else if (choix == 5) {
            string n;
            cout << "Nom du dossier : ";
            cin >> n;
            Dossier* d = racine.chercher(n);
            if (d) cout << "Taille totale de " << n << " : " << d->taille() << " Ko" << endl;
            else cout << "Dossier introuvable." << endl;
        }
    } while (choix != 0);

    return 0;
}

