#include <iostream>
#include <random>  // Satunnaislukugeneraattori
#include <vector>
#include <algorithm>

// Luodaan uusi tietorakenne "HuoneVaraus"
struct HuoneVaraus {
    int huoneNro;
    int hinta;
};


int huoneen_varaus(int huone_lkm) { // Huoneen varauksen aliohjelma

    char varaukseen;
    varaukseen = ' ';
    
    // Kysytään käyttäjältä, halutaanko varata huoneita
    std::cout << "Jatketaanko huoneen varaukseen? (Kyllä=k, Ei=e): ";
    std::cin >> varaukseen;

    int varaus {0};


    switch (varaukseen) {
        case 'k':
            // Kysytään käyttäjältä huoneiden määrää ja varmistetaan syötteen oikeellisuus
            std::cout << "Kuinka monta huonetta varataan?: " ;
            std::cin >> varaus;
            if (varaus > 0 && varaus < huone_lkm) {
                
            } 
            else if (varaus > huone_lkm) { // Tarkistetaan onko varattavien huodeiden lukumäärä suurempi kuin huonelukumäärä
                std::cout << "Varaus on suurempi kuin vapaina olevien huoneiden lukumäärä!";
                std::cout <<"\n";
                varaus = 0;
            }
            else { // Tarkistetaan onko virheellinen syöte
                // Siivotaan syötevirta 
                std::cin.clear();
                std::cin.ignore(256, '\n');

                std::cout << "Virheellinen syöte!";
                std::cout << "\n";
                varaus = 0;
            }
            
            break;
            
        case 'e': 
            std::cout << "Näkemiin!" ;
            exit(EXIT_FAILURE); // Keskeyttää ohjelman palauttamalla epäonnistumiskoodin järjestelmälle
            break;
        
        default:
            // Siivotaan syötevirta 
            std::cin.clear();
            std::cin.ignore(256, '\n');

            std::cout << "Virheellinen syöte.";
            std::cout << "\n";
            break;
    }
    return varaus;
}

int oiden_varaus(int yot) { // Aliohjelma öiden varaukselle
    int yot_lkm;

    // Kysytään käyttäjältä öiden määrää ja varmistetaan syötteen oikeellisuus
    // Siivotaan syötevirta
    std::cin.clear(); 
    std::cin.ignore(256, '\n'); 

    std::cout << "Kuinka monta yötä aiotte yöpyä?: ";
    std::cin >> yot_lkm;
    if (yot_lkm > 0) { 
        std::cout << "Varatut yöt: " << yot_lkm;
        std::cout << "\n";
    }
    else {
        std::cout << "Virheellinen syöte!";
        std::cout <<"\n";
        yot_lkm = 0;
    }

    return yot_lkm;        
}

int main() { // Pääohjelma

    std::cout << "Tervetuloa hotelli Kuuhun! \n";

    std::vector<HuoneVaraus> varaukset;

    // Tallennetaan huoneiden pienin ja suurin arvo sekä hintojen pienin ja suurin arvo
    const int huone_pienin{ 30 };
    const int huone_suurin{ 70 }; 
    const int hinta_pienin{ 80};
    const int hinta_suurin{ 100 };

    std::random_device rd;  // laitteiston satunnaislaite
    std::default_random_engine moottori{ rd() };  // tuottaa satunnaislukuja
    // em. satunnaislaitteen avulla
    std::uniform_int_distribution huone_vali{huone_pienin, huone_suurin}; // Arpoo huoneen välin
    std::uniform_int_distribution hinta_vali{hinta_pienin, hinta_suurin}; // Arpoo hinnan välin
   

    // Muuttujien asettaminen
    int hinta {0};
    int huone_lkm{ huone_vali(moottori) };
    int i {0};
    int kokonaishinta {0};
    int huone_nro {0};
    int huoneen_hinta {0};
    int varaus_lkm {0};
    int yot {0};

    // Käytetään while-silmukoita, kunnes huoneiden ja öiden varaukset on tehty
    while (varaus_lkm == 0) {
        varaus_lkm = huoneen_varaus(huone_lkm);
    }
    while (varaus_lkm != 0 && yot == 0) {
        yot = oiden_varaus(yot);
    }
    

    std::uniform_int_distribution huone_nro_vali{1, huone_lkm}; // Arpoo huoneen nro:n välin


    std::vector<int> varatutHuoneet; // Tallennetaan varatut huoneet

    while (i < varaus_lkm) { // While-silmukka toistetaan niin monta kertaa kuin asiakas halusi varauksie

        huone_nro = huone_nro_vali(moottori);

        // Tarkistetaan, onko huone jo varattu
        auto varattuHuone = std::find(varatutHuoneet.begin(), varatutHuoneet.end(), huone_nro);
        if (varattuHuone != varatutHuoneet.end()) {
            continue;  // Jatketaan seuraavaan iteraatioon
        }

        varatutHuoneet.push_back(huone_nro);  // Lisätään varattu huone vektoriin

        huoneen_hinta = hinta_vali(moottori);
        std::cout << "Valittu huoneenne ja huoneen hinta: " << huone_nro << ", " << huoneen_hinta << " euroa \n";
        
        varaukset.push_back({huone_nro, huoneen_hinta});

        kokonaishinta += huoneen_hinta;
        i++;
    }

    // Lasketaan kokonaishinta
    kokonaishinta *= yot;
    std::cout << "Varauksen kokonaishinta on: " << kokonaishinta;
           
}
