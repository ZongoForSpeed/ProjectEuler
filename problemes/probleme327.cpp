#include "problemes.h"
#include "utilitaires.h"
#include "mp_nombre.h"
#include "matrice.h"

typedef long long int nombre;

namespace {
    nombre M(nombre c, nombre r) {
        static std::map<std::pair<nombre, nombre>, nombre> cache;
        if (r < c) {
            return r + 1;
        }
        auto clef = std::make_pair(c, r);
        auto it = cache.find(clef);
        if (it != cache.end()) {
            return it->second;
        }

        nombre x = M(c, r - 1);
        nombre resultat = 0;
        nombre p = (x - 2) / (c - 2);
        resultat += p * c + x - p * (c - 2) + 1;
        cache.emplace(clef, resultat);
        return resultat;
    }
}

ENREGISTRER_PROBLEME(327, "Rooms of Doom") {
    // A series of three rooms are connected to each other by automatic doors.
    //
    // p327_rooms_of_doom.gif
    //
    // Each door is operated by a security card. Once you enter a room the door automatically closes and that security
    // card cannot be used again. A machine at the start will dispense an unlimited number of cards, but each room
    // (including the starting room) contains scanners and if they detect that you are holding more than three security
    // cards or if they detect an unattended security card on the floor, then all the doors will become permanently
    // locked. However, each room contains a box where you may safely store any number of security cards for use at a
    // later stage.
    //
    // If you simply tried to travel through the rooms one at a time then as you entered room 3 you would have used all
    // three cards and would be trapped in that room forever!
    //
    // However, if you make use of the storage boxes, then escape is possible. For example, you could enter room 1 using
    // your first card, place one card in the storage box, and use your third card to exit the room back to the start.
    // Then after collecting three more cards from the dispensing machine you could use one to enter room 1 and collect
    // the card you placed in the box a moment ago. You now have three cards again and will be able to travel through
    // the remaining three doors. This method allows you to travel through all three rooms using six security cards in
    // total.
    //
    // It is possible to travel through six rooms using a total of 123 security cards while carrying a maximum of 3
    // cards.
    //
    // Let C be the maximum number of cards which can be carried at any time.
    //
    // Let R be the number of rooms to travel through.
    //
    // Let M(C,R) be the minimum number of cards required from the dispensing machine to travel through R rooms carrying
    // up to a maximum of C cards at any time.
    //
    // For example, M(3,6)=123 and M(4,6)=23.
    // And, ΣM(C,6)=146 for 3 ≤ C ≤ 4.
    //
    // You are given that ΣM(C,10)=10382 for 3 ≤ C ≤ 10.
    //
    // Find ΣM(C,30) for 3 ≤ C ≤ 40.
    nombre resultat = 0;
    for (nombre c = 3; c < 41; ++c) {
        resultat += M(c, 30);
    }
    return std::to_string(resultat);
}
