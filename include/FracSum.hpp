#ifndef FracSum_hpp
#define FracSum_hpp

#include "Pgcd.hpp"

namespace mathematics {

  /**
   * @class FracSum FracSum.hpp
   *
   * Template implémentant la somme de deux fractions avec réduction. 
   *
   * @note le signe de la fraction est systématiquement affecté au numérateur.
   *   Comme nous manipulons des long long, il n'est pas envisageable de
   *   multiplier le numérateur par le dénominateur pour déterminer ce signe.
   */
  template< long long num1, long long den1, long long num2, long long den2 >
  class FracSum {
  public:

    enum : long long { 

      // A compléter.
      num = (num1*den2 + num2*den1) / Pgcd<num1*den2 + den1*num2, den1*den2>::value,
      den = (den1 * den2) / Pgcd<num1*num2, den1*den2>::value
		    
    };

  }; // FracSum< num1, den1, num2, den2 >

} // mathematics

#endif
