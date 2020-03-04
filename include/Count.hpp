#ifndef Count_hpp
#define Count_hpp

#include <omp.h>
#include <algorithm>
#include <vector>

namespace paralgos {

  /**
   * @class Count Count.hpp
   *
   * Version OpenMP de l'algorithme count de la bibliothèque standard.
   */
  class Count {
  public:

    /**
     * Forme générale de l'algorithme.
     *
     * @param[in, out] first un itérateur repérant le premier élément à traiter.
     * @param[in, out] last un itérateur repérant l'élément situé juste derrière
     *   le dernier élément à traiter.
     * @param[in] val la valeur recherchée.
     * @return le nombre d'occurrences de la valeur recherchée.
     */
    template< typename InputIterator, typename T >
    static typename std::iterator_traits< InputIterator >::difference_type
    apply(InputIterator first, InputIterator last, const T& val) {

      // Obtention du nombre de threads. Si celui-ci vaut 1, nous utilisons
      // directement la version séquentielle de l'algorithme, c'est à dire celle
      // de la bibliothèque standard.
      int threads;
#pragma omp parallel
#pragma omp single
      threads = omp_get_num_threads();
      if (threads == 1) {
      	return std::count(first, last, val);
      }

      // Obtention du type des itérateurs first et last (nous passons par le
      // template iterator_traits de la bibliothèque standard afin de pouvoir 
      // gérer tous les types de RandomAccessIterator, y compris les simples 
      // pointeurs).
      typedef std::iterator_traits< InputIterator > Traits;

      // Instanciation de l'implémentation (sous-classe) adéquate.
      typedef Impl< typename Traits::iterator_category > Impl;

      // Invocation de la version dédiée de cet algorithme.
      return Impl::apply(first, last, val, threads);

    } // apply

  public:

    /**
     * Implémentation de cet algorithme dédiée aux InputIterator.
     */
    template< typename Category >
    class Impl {
    public:

      // Déclaration d'amitié envers la classe mère : seule cette dernière peut
      // invoquer la méthode de classe privée @c apply.
      friend class Count;

    private:

      /**
       * Implémentation de count.
       *
       * @param[in, out] first un itérateur repérant le premier élément à 
       *   traiter.
       * @param[in, out] last un itérateur repérant l'élément situé juste 
       *   derrière le dernier élément à traiter.
       * @param[in] val la valeur recherchée.
       * @param[in] threads le nombre de threads disponibles.
       * @return le nombre d'occurrences de la valeur recherchée.
       */
      template< typename InputIterator, typename T >
      static
      typename std::iterator_traits< InputIterator >::difference_type
      apply(const InputIterator& first,
            const InputIterator& last,
            const T& val,
            const int& threads) {
	return strategyB(first, last, val, threads);
      } // apply

    private:

      /**
       * Implémentation basée sur l'idée d'une répartition cyclique des
       * éléments du conteneur entre les différents threads disponibles,
       * répartition analogue à la clause schedule(static, 1) des boucles for.
       *
       * @param[in, out] first un itérateur repérant le premier élément à 
       *   traiter.
       * @param[in, out] last un itérateur repérant l'élément situé juste 
       *   derrière le dernier élément à traiter.
       * @param[in] val la valeur recherchée.
       * @param[in] threads le nombre de threads disponibles.
       * @return le nombre d'occurrences de la valeur recherchée.
       */
      template< typename InputIterator, typename T >
      static
      typename std::iterator_traits< InputIterator >::difference_type
      strategyA(const InputIterator& first,
                const InputIterator& last,
                const T& val,
                const int& threads) {

        // Le nombre d'occurrences.
        typename std::iterator_traits< InputIterator >::difference_type
          acc = 0;

        // ... à compléter ...
 
        // C'est terminé.
        return acc;

      } // strategyA
      
      /**
       * Implémentation basée sur l'idée d'un découpage du conteneur en 
       * tronçons en utilisant la notion de tâches. La longueur des tronçons
       * est fixée arbitrairement (éventuellement en fonction du nombre de
       * threads disponibles). Cette répartition est analogue à la clause 
       * schedule(dynamic, size) des boucles for.
       *
       * @param[in, out] first un itérateur repérant le premier élément à 
       *   traiter.
       * @param[in, out] last un itérateur repérant l'élément situé juste 
       *   derrière le dernier élément à traiter.
       * @param[in] val la valeur recherchée.
       * @param[in] threads le nombre de threads disponibles.
       * @return le nombre d'occurrences de la valeur recherchée.
       */
      template< typename InputIterator, typename T >
      static
      typename std::iterator_traits< InputIterator >::difference_type
      strategyB(const InputIterator& first,
                const InputIterator& last,
                const T& val,
                const int& threads) {

	// Taille d'un tronçon fixée arbitrairement (le nombre des éléments
        // du conteneur ne peut être calculé sans un coup prohibitif).
	const int taille = 128 * threads;

        // Le nombre d'occurrences de la valeur recherchée.
        typename std::iterator_traits< InputIterator >::difference_type
          acc = 0;

        // ... à compléter ...

        // C'est terminé.
        return acc;
	
      } // strategyB

    }; // Impl< not RandomAccessIterator >

  }; // Count

  /**
   * Implémentation de cet algorithme dédiée aux RandomAccessIterator.
   */
  template<>
  class Count::Impl< std::random_access_iterator_tag > {
  public:

    // Déclaration d'amitié envers la classe mère : seule cette dernièrer peut
    // invoquer la méthode de classe privée @c apply.
    friend class Count;

  private:

    /**
     * Implémentation de count.
     *
     * @param[in, out] first un itérateur repérant le premier élément à traiter.
     * @param[in, out] last un itérateur repérant l'élément situé juste derrière
     *   le dernier élément à traiter.
     * @param[in] val la valeur recherchée.
     * @param[in] threads le nombre de threads disponibles (inutile ici).
     * @return le nombre d'occurrences de la valeur recherchée.
     */
    template< typename RandomAccessIterator, typename T >
    static
    typename std::iterator_traits< RandomAccessIterator >::difference_type
    apply(const RandomAccessIterator& first,
          const RandomAccessIterator& last,
          const T& val,
          const int& threads) {

      // Le compteur d'occurrences.
      typename std::iterator_traits< RandomAccessIterator >::difference_type
        acc = 0;

#pragma omp parallel
#pragma omp for schedule(static, 1)
      for(int i = 0; i < ; i++){ 
      }      

      // C'est terminé.
      return acc;

    } // apply

  }; // Impl< RandomAccessIterator >

} // paralgos

#endif
