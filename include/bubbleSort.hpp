#ifndef bubbleSort_hpp
#define bubbleSort_hpp

#include <utility>
#include <functional>

namespace sorting {

  /**
   * Implémentation séquentielle du tri à bulle dont la complexité au pire est 
   * O(n^2) si n réprésente le nombre d'éléments à trier. 
   *
   * @param[in] first - un itérateur repérant le premier élément de la séquence
   *   à trier.
   * @param[in] last - un itérateur repérant l'élément situé juste derrière le
   *   dernier élément de la séquence à trier.
   * @param[in] comp - un comparateur binaire permettant d'ordonner deux 
   *   éléments.
   */
  template< typename RandomAccessIterator, typename Compare >
  void bubbleSort(const RandomAccessIterator& first,
                  const RandomAccessIterator& last,
                  const Compare& comp) {

    // Flag indiquant si un échange entre deux éléments consécutifs s'est pro-
    // duit lors de la dernière itération de la boucle extérieure.
    bool echange = true;

    // Boucle extérieure qui ne s'arrête que lorsque plus aucun échange d'élé-
    // ments n'est effectué à l'itération précédente.
    while (echange) {

      // Pour l'instance, aucun échange entre deux éléments n'a encore été
      // effectué pour cette nouvelle itération de la boucle.
      echange = false;

      // Balayage des n-1 premiers éléments.
      for (RandomAccessIterator it = first; it != last - 1; it ++) {

	// Obtention de l'élément courant et de son successeur. Le mot-clé auto,
	// introduit par la norme 2011, permet de ne pas mentionner le type des
	// éléments.
	auto& courant = *it;
	auto& suivant = *(it + 1);

	// Les éléments ne sont pas correctement ordonnés : il faut procéder à
	// un échange.
	if (! comp(courant, suivant)) {
	  std::swap(courant, suivant);
	  echange = true;
	}

      }

    }

  } // bubbleSort

  /**
   * Implémentation séquentielle du tri à bulle dont la complexité au pire est
   * O(n^2) si n réprésente le nombre d'éléments à trier. La relation d'ordre 
   * total utilisée est "strictement inférieur à".
   *
   * @param[in] first - un itérateur repérant le premier élément de la séquence
   *   à trier.
   * @param[in] last - un itérateur repérant l'élément situé juste derrière le
   *   dernier élément de la séquence à trier.
   */
  template< typename RandomAccessIterator >
  void bubbleSort(const RandomAccessIterator& first, 
                  const RandomAccessIterator& last) {

    // Type synonyme pour le type des éléments du conteneur. 
    typedef std::iterator_traits< RandomAccessIterator > Traits;
    typedef typename Traits::value_type value_type;

    // Fabriquer le comparateur less puis invoquer la fonction définie 
    // ci-dessus.
    bubbleSort(first, last, std::less< const value_type& >());

  } // bubbleSort

} // sorting

#endif
