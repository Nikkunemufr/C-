#include "cmplx.hpp"

namespace cmplx {

  /*******
   * add *
   *******/

  void
  add(const Cmplx& a, const Cmplx& b, Cmplx& res) {
    res[0] = a[0] + b[0];
    res[1] = a[1] + b[1];
  }

  /***********
   * addSSE2 *
   ***********/

  void
  addSSE2(const Cmplx& a, const Cmplx& b, Cmplx& res) {

    // Les parties réelles et imaginaires sont chargées dans un registre 128
    // bits en un seul accès mémoire (packed data). La partie réelle est copiée
    // dans la partie basse du registre (bits de poids faible) tandis que la
    // partie imaginaire est copiée dans la partie haute (bits de poids forts).
    const __m128d pk_a = _mm_load_pd(a);

    // Chargement du second opérande dans un autre registre 128 bits.
    const __m128d pk_b = _mm_load_pd(b);

    // Un troisième registre 128 bits accueille la somme des deux registres
    // précédents. Par conséquent, sa partie basse contient la somme des parties
    // réelles tandis que sa partie haute contient la somme des parties
    // imaginaires.
    const __m128d pk_res = _mm_add_pd(pk_a, pk_b);

    // Le contenu du registre contenant le résultat est recopié dans le
    // troisième opérande. La partie basse du registre est copiée dans le
    // premier emplacement du tableau tandis que la partie haute est copiée
    // dans le second.
    _mm_store_pd(res, pk_res);

  }

  /*******
   * mul *
   *******/

  void
  mul(const Cmplx& a, const Cmplx& b, Cmplx& res) {
    res[0] = a[0] * b[0] - a[1] * b[1];
    res[1] = a[0] * b[1] + a[1] * b[0];
  }

  /***********
   * mulSSE2 *
   ***********/

  void
  mulSSE2(const Cmplx& a, const Cmplx& b, Cmplx& res) {
    // ... à compléter ...
  }

}
