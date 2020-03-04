#ifndef cmplx_hpp
#define cmplx_hpp

#include <emmintrin.h>

namespace cmplx {

  // Type synonyme pour un nombre complexe.
  typedef double Cmplx[2];

  /**
   * Calcule puis retourne la somme de deux nombres complexes.
   *
   * @param[in]  a l'opérande gauche.
   * @param[in]  b l'opérande droite.
   * @param[out] res la somme des deux opérandes.
   */
  void add(const Cmplx& a, const Cmplx& b, Cmplx& res);

  /**
   * Calcule (SIMD/SSE2) puis retourne la somme de deux nombres complexes.
   *
   * @param[in]  a l'opérande gauche.
   * @param[in]  b l'opérande droite.
   * @param[out] res la somme des deux opérandes.
   */
  void addSSE2(const Cmplx& a, const Cmplx& b, Cmplx& res);  

  /**
   * Calcule puis retourne le produit de deux nombres complexes.
   *
   * @param[in]  a l'opérande gauche.
   * @param[in]  b l'opérande droite.
   * @param[out] res le produit des deux opérandes.
   */
  void mul(const Cmplx& a, const Cmplx& b, Cmplx& res);

  /**
   * Calcule (SIMD/SSE2) puis retourne le produit de deux nombres complexes.
   *
   * @param[in]  a l'opérande gauche.
   * @param[in]  b l'opérande droite.
   * @param[out] res le produit des deux opérandes.
   */
  void mulSSE2(const Cmplx& a, const Cmplx& b, Cmplx& res);

}

#endif
