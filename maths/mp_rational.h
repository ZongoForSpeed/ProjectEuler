#pragma once

#include <gmp.h>

class mp_rational {
	mpq_t _data;
public:
	mp_rational() {
		mpq_init(_data);
	}
	
	mp_rational(const mpq_t op) {
		mpq_set(_data, op);
	}
	
	~mp_rational() {
		mpq_clear(_data);
	}
	
	mp_rational(const mp_rational & op) {
		mpq_set(_data, op._data);
	}
	
	mp_rational(const mpz_t op) {
		mpq_set_z(_data, op);
	}
	
	mp_rational(const mp_nombre & op) {
		mpq_set_z(_data, op.get_data());
	}
	
	mp_rational(unsigned long int op1, unsigned long int op2) {
		mpq_set_ui(_data, op1, op2);
	}
	
	mp_rational(long int op1, long int op2) {
		mpq_set_si(_data, op1, op2);
	}
	
	void swap(mp_rational &op) {
		mpq_swap(_data, op._data);
	}
	
	double get_double() const {
		return mpq_get_d(_data);
	}
	
	void set(double op) {
		mpq_set_d(_data, op);
	}
	
	std::string to_string(int base = 10) const {
		char *str = mpq_get_str(nullptr, base, _data);
    	std::string resultat(str);
    	free(str);
    	return resultat;
	}
};

namespace std {

    void swap(mp_rational &op1, mp_rational &op2) {
    	op1.swap(op2);
    }
}

