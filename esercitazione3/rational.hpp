#include <iostream>
#include <numeric>
#pragma once

template<typename I> requires std::integral<I>
class rational
{
	I num_;
	I den_;
	
	void semplify() {
        if (den_ == I{0}) {
            if (num_ != I{0}) { // r = inf, num determina il segno
				if (num_ > I{0}) { 
					num_ = I{1};
				}
				else {
					num_ = I{-1};
				}
            }
            return;
        }
        if (den_ < I{0}) { // sposto il segno dal denominatore al numeratore
            num_ = -num_;
            den_ = -den_;
        }
        I mcd = std::gcd(num_, den_); // semplifico l'espressione tramite mcd
        num_ /= mcd;
        den_ /= mcd;
    }
public:

	/* costruttore di default */
	rational():
		num_(I{0}), den_(I{1})
	{}
	
	/* Costruttore user-defined */
	rational(const I& pnum, const I& pden):
		num_(pnum), den_(pden)
	{
		semplify(); // semplifico la frazione 
	}
	
	/* Controllo infinito */
	bool inf() const {
		return (den_ == I{0} && num_ != I{0}); // vero se den = 0, num != 0
	}
	
	/* Controllo not a number */
	bool NaN() const {
		return (den_ == I{0} && num_ == I{0}); // vero se den = num = 0
	}
	
	/* Restituiscono i valori di num e den */
    I num() { return num_; }
    I den() { return den_; }
	
	/* Implementazione dell'incremento */
    rational& operator+=(const rational& other) {
		if (NaN() || other.NaN()) {   // se un razionale è NaN
			num_ = I{0}; den_ = I{0};
		}
		else if(inf() && other.inf()) {   // se entrambi sono infinito
			if (sign() != other.sign()) { // e di segno opposto
				num_ = I{0}; den_ = I{0};
			}
		}
		else if (inf() && !other.inf()) { // se il primo è infinito
			den_ = I{0};
			if (num_ > 0) {
				num_ = I{1};
			}
			else {
				num_ = I{-1};
			}
		}
		else if (!inf() && other.inf()) { // se il secondo è infinito
			den_ = I{0};
			if (other.num_ > 0) {
				num_ = I{1};
			}
			else {
				num_ = I{-1};
			}
		}
		else if (!inf() && !other.inf()) {	 // se sono entrambi finiti
			num_ = num_*other.den_ + other.num_*den_;
			den_ = den_*other.den_;
		}
        semplify(); // semplifico la frazione e aggiusto i segni
        return *this;
    }
    
    /* Implementazione della somma */
    rational operator+(const rational& other) {
		rational ret = *this;
		ret += other;
        return ret;
	}
    

    /* Implementazione della diminuzione */
    rational& operator-=(const rational& other) {
		if (NaN() || other.NaN()) {   // se un razionale è NaN
			num_ = I{0}; den_ = I{0};
		}
		else if(inf() && other.inf()) {   // se entrambi sono inf
			if (sign() == other.sign()) { // e di stesso segno
				num_ = I{0}; den_ = I{0};
			}
		}
		else if (inf() && !other.inf()) { // se il primo è infinito
			den_ = I{0};
			if (num_ > 0) {
				num_ = I{1};
			}
			else {
				num_ = I{-1};
			}
		}
		else if (!inf() && other.inf()) { // se il secondo è infinito
			den_ = I{0};
			if (other.num_ < 0) {
				num_ = I{1};
			}
			else {
				num_ = I{-1};
			}
		}
		else if (!inf() && !other.inf()) { // se entrambi sono finiti
			num_ = num_*other.den_ - other.num_*den_;
			den_ = den_*other.den_;
		}
        semplify();
        return *this;
    }
    
    /* Implementazione della differenza */
	rational operator-(const rational& other) {
        rational ret = *this;
		ret -= other;
        return ret;
    }
	
	/* Implementazione della moltiplicazione e assegnamento */
	rational& operator*=(const rational& other) {
		if (NaN() || other.NaN()) {  // se un razionale è NaN
			num_ = I{0}; den_ = I{0};
		}
		else if ((inf() && other.num_ == I{0}) || (num_ == I{0} && other.inf())) {
			num_ = I{0}; den_=I{0};  // caso inf * 0 oppure 0 * inf
		}
		else if (inf() || other.inf()) {  		// caso inf * inf 
			if ((num_ > I{0}) == (other.num_ > I{0})) {
			num_ = I{1};
			}
			else {
				num_ = I{-1};
			}
			den_ = I{0};
		}
		else {  // entrambi sono finiti
			num_ = num_*other.num_;
			den_ = den_*other.den_;
		}
        semplify(); // semplifico e aggiusto i segni
        return *this;
    }
	
	/* Implementazione della moltiplicazione */
	rational operator*(const rational& other) {
		rational ret = *this;
		ret *= other;
        return ret;
	}
	
	/* Implementazione della divisione e assegnamento */
	rational& operator/=(const rational& other) {
		if (NaN() || other.NaN()) {  // se un razionale è NaN
			num_ = I{0}; den_ = I{0};
		}
		else if (num_== I{0} && other.num_ == I{0}) { // caso 0/0
			num_ = I{0}; den_ =I{0};
		}
		else if (inf() && other.inf()) {  // caso inf/0
			num_ = I{0}; den_ =I{0};
		}
		else if (!inf() && other.inf()) {  // caso r/inf = 0
			num_ = I{0}; den_ = I{1};
		}
		else if (inf() && !other.inf()) {  // caso inf/r = +-inf
			if ((num_ > I{0}) == (other.num_ > I{0})) {
			num_ = I{1};
			}
			else {
				num_ = I{-1};
			}
			den_ = I{0};
		}
		else {  // entrambi finiti
			num_ = num_*other.den_;
			den_ = den_*other.num_;
		}
        semplify(); // aggiusto i segni e semplifico
        return *this;
    }
	
	/* Implementazione della divisione */
    rational operator/(const rational& other) {
		rational ret = *this;
		ret /= other;
        return ret;
	}

	/* Segno del razionale */
	bool sign() const {
		return num_ >= I{0};
	}
	
};

template<typename T>
std::ostream&
operator<<(std::ostream& os, rational<T>& r)
{	
	if (r.NaN()) {  // se è NaN
		os << "NaN\n";
	}
	else if (r.inf()) {  // se è +-inf
		if (r.num() > 0) os << "inf";
		else os << "-inf";
	}
	else {
		if (r.num() == 0) {  // se è 0
			os << r.num();
		}
		else {  // se è un razionale finito diverso da 0
			if (r.den() == 1) {
				os << r.num();
			}
			else {
				os << r.num() << "/" << r.den();
			}
		}
	}
    return os;
}