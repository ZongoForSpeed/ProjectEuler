#include "Problemes.h"
#include "Utilitaires.h"
#include <iostream>
int main(int argc, char ** argv)
{
    RegistreProbleme::instance().execute(argc, argv);
	return 0;
}
