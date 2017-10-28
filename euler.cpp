#include "problemes.h"

int main(int argc, char **argv) {
    RegistreProbleme::instance().execute(argc, argv);
    return 0;
}
