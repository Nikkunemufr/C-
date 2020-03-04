#include "vectors.hpp"

namespace vectors {

  /********
   * yaxb *
   ********/

  void
  yaxb(const double& a,
       const double x[],
       const size_t& n,
       const double& b,
       double y[]) {
    for (size_t i = 0; i != n; i ++) {
      y[i] = a * x[i] + b;
    }
  }

  /************
   * yaxbSSE2 *
   ************/

  void
  yaxbSSE2(const double& a,
           const double x[],
           const size_t& n,
           const double& b,
           double y[]) {
             const __m128d pk_a = _mm_load1_pd(&a);
             const __m128d pk_b = _mm_load1_pd(&b);
             __m128d pk;
             for (size_t i = 0; i != n; i += 2) {
               pk = _mm_load_pd(&x[i]); // x + i
               pk = _mm_mul_pd(pk_a, pk);
               pk = _mm_add_pd(pk_b, pk);
               _mm_store_pd(&y[i], pk);
             }
  }

  /*******
   * sum *
   *******/

  double
  sum(const double x[], const size_t& n) {
    double acc = 0.0;
    for (size_t i = 0; i != n; i ++) {
      acc += x[i];
    }
    return acc;
  }

  /***********
   * sumSSE2 *
   ***********/

  double
  sumSSE2(const double x[], const size_t& n) {
    double acc[2];
    __m128d pk_acc = _mm_setzero_pd();
    for (size_t i = 0; i != n; i += 2) {
        const __m128d pk_x = _mm_load_pd(&x[i]);
        pk_acc = _mm_add_pd(pk_acc,pk_x);
    }
    _mm_store_pd(acc, pk_acc);
    return acc[0] + acc[1];
  }

  /***********
   * reverse *
   ***********/

  void
  reverse(const double x[], const size_t& n, double y[]) {
    for (size_t i = 0; i != n; i ++) {
      y[n - i - 1] = x[i];
    }
  }

  /***************
   * reverseSSE2 *
   ***************/

  void
  reverseSSE2(const double x[], const size_t& n, double y[]) {
    for (size_t i = 0; i != n; i += 2) {
      __m128d pk_a = _mm_load_pd(&x[i]);
      __m128d pk = _mm_shuffle_pd(pk_a, pk_a, 1);
      _mm_store_pd(&y[n-i-2], pk);
    }
  }
}
