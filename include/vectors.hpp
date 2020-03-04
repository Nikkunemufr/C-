#ifndef vectors_hpp
#define vectors_hpp

#include <emmintrin.h>
#include <cstdlib>

namespace vectors {

  /**
   * Calcule y[i] = a x[i] + b pour des vecteurs de longueur paire.
   *
   * @param[in]  a la constante @c a.
   * @param[in]  x le vecteur @c x.
   * @param[in]  n la longueur paire des vecteurs.
   * @param[in]  b la constante @c b.
   * @param[out] y le vecteur résultat @c y.
   */
  void yaxb(const double& a,
            const double x[],
            const size_t& n,
            const double& b,
            double y[]);

  /**
   * Calcule (SIMD/SSE2) y[i] = a x[i] + b pour des vecteurs de longueur paire.
   *
   * @param[in]  a la constante @c a.
   * @param[in]  x le vecteur @c x.
   * @param[in]  n la longueur paire des vecteurs.
   * @param[in]  b la constante @c b.
   * @param[out] y le vecteur résultat @c y.
   */
  void yaxbSSE2(const double& a,
                const double x[],
                const size_t& n,
                const double& b,
                double y[]);

  /**
   * Calcule la somme des éléments d'un vecteur de longueur paire.
   *
   * @param[in] x le vecteur.
   * @param[in] la longueur paire du vecteur.
   * @return la somme des éléments du vecteur.
   */
  double sum(const double x[], const size_t& n);  

  /**
   * Calcule (SIMD/SSE2) la somme des éléments d'un vecteur de longueur paire.
   *
   * @param[in] x le vecteur.
   * @param[in] la longueur paire du vecteur.
   * @return la somme des éléments du vecteur.
   */
  double sumSSE2(const double x[], const size_t& n);

  /**
   * Inverse le contenu d'un vecteur de longueur paire.
   *
   * @param[in] x le vecteur à inverser.
   * @param[in] n la longueur paire du vecteur.
   * @param[out] y le vecteur inversé.
   */
  void reverse(const double x[], const size_t& n, double y[]);  

  /**
   * Inverse (SIMD/SSE2) le contenu d'un vecteur de longueur paire.
   *
   * @param[in] x le vecteur à inverser.
   * @param[in] n la longueur paire du vecteur.
   * @param[out] y le vecteur inversé.
   */
  void reverseSSE2(const double x[], const size_t& n, double y[]);

}

#endif
