#include "problemes.h"
#include "utilitaires.h"
#include <iostream>
int main(int argc, char ** argv)
{
    RegistreProbleme::instance().execute(argc, argv);
	return 0;
}
