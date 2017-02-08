#include "mp_float.h"

mp_float::mp_float() {
    mpfr_init (_data);
}

mp_float::~mp_float() {
    mpfr_clear (_data);
}
