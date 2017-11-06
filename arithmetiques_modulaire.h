#pragma once

#include <ostream>
#include <utility>

namespace arithmetiques {
    template<size_t modulo> 
    class nombre_modulaire {
        template<typename Type>
        void set(Type op, std::false_type /*is_signed*/) {
            _value = op % modulo;
        }
    
        template<typename Type>
        void set(Type op, std::true_type /*is_signed*/) {
            bool negatif = (op < 0);
            op = std::abs(op);
            _value = static_cast<size_t>(op) % modulo;
            if (negatif) {
                _value = modulo - _value;
            }
        }
        
        template<size_t _modulo>
        static std::pair<size_t, nombre_modulaire<_modulo>> internalFact(size_t n) {
            nombre_modulaire<_modulo> resultat = 1;
            size_t exposant = 0;
            bool sgn = false;
            while (n > 0) {
                for (size_t i = n % _modulo; i > 1; --i)
                    resultat *= i;
                n /= _modulo;
                sgn ^= (n % 2 == 1);
                exposant += n;
            }
            return std::make_pair(exposant, sgn ? -resultat : resultat);
        }
        
        static nombre_modulaire<modulo> puissance(nombre_modulaire<modulo> a, size_t n) {
            nombre_modulaire<modulo> result(1);
            while (n > 0) {
                if (n % 2)
                    result *= a;
                a *= a;
                n /= 2;
            }
            return result;
        }

        size_t _value;
    public:
        template<typename Type>
        nombre_modulaire(Type n) : _value(0) {
            set(n);
        }
        
        template<typename T>
        void set(T x) {
            static_assert(std::is_integral<T>::value, "Integer required.");
            set(x, std::is_signed<T>());
        }

        size_t value() const { return _value; }
        
        nombre_modulaire<modulo> operator-() const {
            return nombre_modulaire<modulo>(modulo - value());
        }

        nombre_modulaire<modulo> &operator+=(const nombre_modulaire<modulo> &b) {
            _value += b._value;
            if (_value >= modulo) _value -= modulo;
            return *this;
        }
        
        nombre_modulaire<modulo> operator+(const nombre_modulaire<modulo> &op) const {
            nombre_modulaire<modulo> result(*this);
            result.operator+=(op);
            return result;
        }
        
        template<typename T>
        nombre_modulaire<modulo> &operator+=(const T &op) {
            nombre_modulaire<modulo> n(op);
            return this->operator+=(n);
        }
    
        template<typename T>
        nombre_modulaire<modulo> operator+(const T &op) const {
            nombre_modulaire<modulo> n(op);
            return this->operator+(n);
        }

        nombre_modulaire<modulo> &operator-=(const nombre_modulaire<modulo> &b) {
            _value = _value < b._value ? modulo + _value - b._value : _value - b._value;
            return *this;
        }
        
        nombre_modulaire<modulo> operator-(const nombre_modulaire<modulo> &op) const {
            nombre_modulaire<modulo> result(*this);
            result.operator-=(op);
            return result;
        }

        
        template<typename T>
        nombre_modulaire<modulo> &operator-=(const T &op) {
            nombre_modulaire<modulo> n(op);
            return this->operator-=(n);
        }
    
        template<typename T>
        nombre_modulaire<modulo> operator-(const T &op) const {
            nombre_modulaire<modulo> n(op);
            return this->operator-(n);
        }

        nombre_modulaire<modulo> &operator*=(const nombre_modulaire<modulo> &b) {
            size_t c = _value;
            c *= b._value;
            _value = c % modulo;
            return *this;
        }
        
        nombre_modulaire<modulo> operator*(const nombre_modulaire<modulo> &op) const {
            nombre_modulaire<modulo> result(*this);
            result.operator*=(op);
            return result;
        }
        
        template<typename T>
        nombre_modulaire<modulo> &operator*=(const T &op) {
            nombre_modulaire<modulo> n(op);
            return this->operator*=(n);
        }
    
        template<typename T>
        nombre_modulaire<modulo> operator*(const T &op) const {
            nombre_modulaire<modulo> n(op);
            return this->operator*(n);
        }

        nombre_modulaire<modulo> &operator/=(const nombre_modulaire<modulo> &b) {
            return operator*=(puissance(b, modulo - 2));
        }
        
        nombre_modulaire<modulo> operator/(const nombre_modulaire<modulo> &op) const {
            nombre_modulaire<modulo> result(*this);
            result.operator/=(op);
            return result;
        }
        
        template<typename T>
        nombre_modulaire<modulo> &operator/=(const T &op) {
            nombre_modulaire<modulo> n(op);
            return this->operator/=(n);
        }
    
        template<typename T>
        nombre_modulaire<modulo> operator/(const T &op) const {
            nombre_modulaire<modulo> n(op);
            return this->operator/(n);
        }

        static nombre_modulaire<modulo> factoriel(size_t n) {
            return internalFact<modulo>(n).second;
        }
    
        static nombre_modulaire<modulo> arrangement(size_t n, size_t k) {
            return factoriel<modulo>(n) / factoriel<modulo>(n - k);
        }
    
        static nombre_modulaire<modulo> coefficient_binomial(size_t n, size_t k) {
            auto fn = internalFact<modulo>(n);
            auto fk = internalFact<modulo>(k);
            auto fnk = internalFact<modulo>(n - k);
            if (fn.first - fk.first - fnk.first > 0)
                return arithmetiques::nombre_modulaire<modulo>(0);
            return fn.second / (fk.second * fnk.second);
        }
    };

    template<size_t modulo, typename T>
    inline nombre_modulaire<modulo> operator+(const T &op1, const nombre_modulaire<modulo> &op2) {
        return op2.operator+(op1);
    }
    
    template<size_t modulo, typename T>
    inline nombre_modulaire<modulo> operator-(const T &op1, const nombre_modulaire<modulo> &op2) {
        nombre_modulaire<modulo> n(op1);
        return n.operator-(op2);
    }
    
    template<size_t modulo, typename T>
    inline nombre_modulaire<modulo> operator*(const T &op1, const nombre_modulaire<modulo> &op2) {
        return op2.operator*(op1);
    }
    
    template<size_t modulo, typename T>
    inline nombre_modulaire<modulo> operator/(const T &op1, const nombre_modulaire<modulo> &op2) {
        nombre_modulaire<modulo> n(op1);
        return n.operator/(op2);
    }
}

template<size_t modulo>
std::ostream &operator<<(std::ostream &os, const arithmetiques::nombre_modulaire<modulo> &a) {
    os << a.value() << "[" << modulo<< "]";
    return os;
}
