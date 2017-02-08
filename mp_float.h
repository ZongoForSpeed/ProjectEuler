#pragma once

#include <mpfr.h>
#include "mp_nombre.h"

class mp_float {
    mpfr_t _data;
    
public:
    mp_float();
    virtual ~mp_float();
    mp_float(mpfr_t op) {
        mpfr_init_set(_data, op, MPFR_RNDN);
    }
    
    mp_float(const mp_float & op) {
        mpfr_init_set(_data, op._data, MPFR_RNDN);
    }
    
    mp_float(unsigned int op) {
        mpfr_init_set_ui(_data, op, MPFR_RNDN);
    }    
    
    mp_float(signed int op) {
        mpfr_init_set_si(_data, op, MPFR_RNDN);
    }
    
    mp_float(unsigned long int op) {
        mpfr_init_set_ui(_data, op, MPFR_RNDN);
    }    
    
    mp_float(signed long int op) {
        mpfr_init_set_si(_data, op, MPFR_RNDN);
    }
    
    mp_float(double op) {
        mpfr_init_set_d(_data, op, MPFR_RNDN);
    }    
    
    mp_float(long double op) {
        mpfr_init_set_ld(_data, op, MPFR_RNDN);
    } 
    
    mp_float(const mp_nombre & op) {
        mpfr_init_set_z(_data, op.get_data(), MPFR_RNDN);
    } 
    
    mp_float(const std::string & op, int base = 10) {
        mpfr_init_set_str(_data, op.c_str(), base, MPFR_RNDN);
    }    
    
    void set(mpfr_t op) {
        mpfr_set(_data, op, MPFR_RNDN);
    }
    
    void set(const mp_float & op) {
        mpfr_set(_data, op._data, MPFR_RNDN);
    }
    
    void set(unsigned int op) {
        mpfr_set_ui(_data, op, MPFR_RNDN);
    }    
    
    void set(signed int op) {
        mpfr_set_si(_data, op, MPFR_RNDN);
    }
    
    void set(unsigned long int op) {
        mpfr_set_ui(_data, op, MPFR_RNDN);
    }    
    
    void set(signed long int op) {
        mpfr_set_si(_data, op, MPFR_RNDN);
    }
    
    void set(double op) {
        mpfr_set_d(_data, op, MPFR_RNDN);
    }    
    
    void set(long double op) {
        mpfr_set_ld(_data, op, MPFR_RNDN);
    }    
    
    void set(const mp_nombre & op) {
        mpfr_set_z(_data, op.get_data(), MPFR_RNDN);
    }
    
    void set(const std::string & op, int base = 10) {
        mpfr_set_str(_data, op.c_str(), base, MPFR_RNDN);
    }
    
    void setNaN() {
        mpfr_set_nan(_data);
    }
    
    void setInfini(int signe = 1) {
        mpfr_set_inf(_data, signe);
    }
    
    void setZero(int signe = 1) {
        mpfr_set_zero(_data, signe);
    }
    
    void swap(mp_float & op) {
        mpfr_swap(_data, op._data);
    }
    
    float get_float() const {
        return mpfr_get_flt(_data, MPFR_RNDN);
    }
    
    double get_double() const {
        return mpfr_get_d(_data, MPFR_RNDN);
    }
    
    long double get_long_double() const {
        return mpfr_get_ld(_data, MPFR_RNDN);
    }
    
    signed long int get_signed_long() const {
        return mpfr_get_si (_data, MPFR_RNDZ);
    }
    
    unsigned long int get_unsigned_long() const {
        return mpfr_get_ui (_data, MPFR_RNDZ);
    }
    
    mp_nombre get_mp_nombre() {
        mp_nombre result;
        mpfr_get_z(result.get_data(), _data, MPFR_RNDZ);
        return result;
    }
    
    std::string to_string(size_t n = 0) const {
    	// Use MPFR native function for output
    	char format[128];
    	size_t digits = n > 0 ? n : 10;
    
    	sprintf(format,"%%.%zuRNg",digits);		// Default format

        char *s = NULL;
        std::string out;
        
        if(!(mpfr_asprintf(&s, format, _data) < 0))
        {
            out = std::string(s);

            mpfr_free_str(s);
        }
        return out;
    }
    
    mp_float &operator=(const mp_nombre &op) {
        set(op);
        return *this;
    }

    template<typename T>
    mp_float &operator=(const T &op) {
        set(op);
        return *this;
    }
    
    // region Addition
    mp_float &operator+=(const mp_float &op) {
        mpfr_add(_data, _data, op._data, MPFR_RNDN);
        return *this;
    }
    mp_float &operator+=(unsigned long int op) {
        mpfr_add_ui(_data, _data, op, MPFR_RNDN);
        return *this;
    }
    mp_float &operator+=(signed long int op) {
        mpfr_add_si(_data, _data, op, MPFR_RNDN);
        return *this;
    }
    mp_float &operator+=(double op) {
        mpfr_add_d(_data, _data, op, MPFR_RNDN);
        return *this;
    }
    mp_float &operator+=(const mp_nombre & op) {
        mpfr_add_z(_data, _data, op.get_data(), MPFR_RNDN);
        return *this;
    }
    
    mp_float operator+(const mp_float &op) const {
        mp_float result;
        mpfr_add(result._data, _data, op._data, MPFR_RNDN);
        return result;
    }
    mp_float operator+(unsigned long int op) const {
        mp_float result;
        mpfr_add_ui(result._data, _data, op, MPFR_RNDN);
        return result;
    }
    mp_float operator+(signed long int op) const {
        mp_float result;
        mpfr_add_si(result._data, _data, op, MPFR_RNDN);
        return result;
    }
    mp_float operator+(double op) const {
        mp_float result;
        mpfr_add_d(result._data, _data, op, MPFR_RNDN);
        return result;
    }
    mp_float operator+(const mp_nombre & op) const {
        mp_float result;
        mpfr_add_z(result._data, _data, op.get_data(), MPFR_RNDN);
        return result;
    }

    template<typename T>
    mp_float &operator+=(const T &op) {
        mp_float n(op);
        return this->operator+=(n);
    }
    
    template<typename T>
    mp_float operator+(const T &op) const {
        mp_float resultat;
        mp_float n(op);
        mpfr_add(resultat._data, _data, n._data, MPFR_RNDN);
        return resultat;
    }
    // endregion Addition

    // Function: int mpfr_fits_ulong_p (mpfr_t op, mpfr_rnd_t rnd)
    // Function: int mpfr_fits_slong_p (mpfr_t op, mpfr_rnd_t rnd)
    // Function: int mpfr_fits_uint_p (mpfr_t op, mpfr_rnd_t rnd)
    // Function: int mpfr_fits_sint_p (mpfr_t op, mpfr_rnd_t rnd)
    // Function: int mpfr_fits_ushort_p (mpfr_t op, mpfr_rnd_t rnd)
    // Function: int mpfr_fits_sshort_p (mpfr_t op, mpfr_rnd_t rnd)
    // Function: int mpfr_fits_uintmax_p (mpfr_t op, mpfr_rnd_t rnd)
    // Function: int mpfr_fits_intmax_p (mpfr_t op, mpfr_rnd_t rnd)
    
};
