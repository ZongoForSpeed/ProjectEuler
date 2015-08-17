#include "Problemes.h"
#include "Arithmetiques.h"

#include <string>

int main(int argc, char ** argv)
{
    premiers::testCrible(std::stoull(argv[1]));
	return 0;
}
