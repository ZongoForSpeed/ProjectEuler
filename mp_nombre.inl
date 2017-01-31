template<typename T>
void mp_nombre::set(T x) {
    static_assert(std::is_integral<T>::value, "Integer required.");
    set(x, std::is_signed<T>());
}

template<typename T>
T mp_nombre::get() const {
    static_assert(std::is_integral<T>::value, "Integer required.");
    return get(std::is_signed<T>());
}

template<typename T>
mp_nombre &mp_nombre::operator=(const T &op) {
    set(op);
    return *this;
}

template<typename T>
int mp_nombre::compare(const T &op) const {
    mp_nombre n(op);
    return compare(n);
}

template<typename T>
mp_nombre mp_nombre::puissance_modulaire(const mp_nombre &base, unsigned long exposant, const T &modulo) {
    mp_nombre tmp_modulo(modulo);
    return puissance_modulaire(base, exposant, tmp_modulo);
}

template<typename T>
mp_nombre mp_nombre::PGCD(const mp_nombre &op1, const T &op2) {
    mp_nombre n2(op2);
    return PGCD(op1, n2);
}

template<typename T>
mp_nombre mp_nombre::PGCD(const T &op1, const mp_nombre &op2) {
    return PGCD(op2, op1);
}

template<typename T>
mp_nombre mp_nombre::PPCM(const mp_nombre &op1, const T &op2) {
    mp_nombre n2(op2);
    return PPCM(op1, n2);
}

template<typename T>
mp_nombre mp_nombre::PPCM(const T &op1, const mp_nombre &op2) {
    return PPCM(op2, op1);
}

template<typename T>
mp_nombre &mp_nombre::operator+=(const T &op) {
    mp_nombre n(op);
    return this->operator+=(n);
}

template<typename T>
mp_nombre mp_nombre::operator+(const T &op) const {
    mp_nombre resultat;
    mp_nombre n(op);
    mpz_add(resultat.data, data, n.data);
    return resultat;
}

template<typename T>
mp_nombre &mp_nombre::operator-=(const T &op) {
    mp_nombre n(op);
    return this->operator-=(n);
}

template<typename T>
mp_nombre mp_nombre::operator-(const T &op) const {
    mp_nombre n(op);
    return this->operator-(n);
}

template<typename T>
mp_nombre &mp_nombre::operator*=(const T &op) {
    mp_nombre n(op);
    return this->operator*=(n);
}

template<typename T>
mp_nombre mp_nombre::operator*(const T &op) const {
    mp_nombre n(op);
    return this->operator*(n);
}

template<typename T>
mp_nombre &mp_nombre::operator/=(const T &op) {
    mp_nombre n(op);
    return this->operator/=(n);
}

template<typename T>
mp_nombre mp_nombre::operator/(const T &op) const {
    mp_nombre n(op);
    return this->operator/(n);
}

template<typename T>
mp_nombre &mp_nombre::operator%=(const T &op) {
    mp_nombre n(op);
    return this->operator%=(n);
}

template<typename T>
mp_nombre mp_nombre::operator%(const T &op) const {
    mp_nombre n(op);
    return this->operator%(n);
}

template<typename T>
mp_nombre &mp_nombre::operator&=(const T &op) {
    mp_nombre n(op);
    return this->operator&=(n);
}

template<typename T>
mp_nombre mp_nombre::operator&(const T &op) const {
    mp_nombre n(op);
    return this->operator&(n);
}
template<typename T>
mp_nombre &mp_nombre::operator|=(const T &op) {
    mp_nombre n(op);
    return this->operator|=(n);
}

template<typename T>
mp_nombre mp_nombre::operator|(const T &op) const {
    mp_nombre n(op);
    return this->operator|(n);
}

template<typename T>
mp_nombre &mp_nombre::operator^=(const T &op) {
    mp_nombre n(op);
    return this->operator^=(n);
}

template<typename T>
mp_nombre mp_nombre::operator^(const T &op) const {
    mp_nombre n(op);
    return this->operator^(n);
}

