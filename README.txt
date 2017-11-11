Simulation d'un reseau de neurones:
 - 12500 neurones
 - constantes.h contient toutes les constantes necessaire pour le programme
 - plot 1: spikes produites par 50 neurones choisis aux hazard a chaque step, pour un intervalle de temps donné
   (les neurones qui n'ont pas produit de spikes sont accumulée en dans le haut de la figure)
 - plot 2: total de spikes produites a chaque step, pour un intervalle de temps donné
 - images: contiens les graphiques de qutre cas differents, en dependant de deux constantes (g,nu)
	- A: g=3, nu=2 (almost fully synchronized network, neurons firing regularly at high rates)
	- B: g=6, nu=4 (fast oscillating global activity, neurons firing irregularly at low rates)
	- C: g=5, nu=2 (stationary global activity, neurons firing irregularly)
	- D: g=4.5, nu=0.9 (slow oscillating glabal activity, neurons firing irregularly at very low rates)
 - files: contiens les fichiers .txt et le script matlab nécessaires pour les plots (voir main.cpp)
 - simulation sur un nombre pré-defini de steps (0.1ms), dont une partie est selectioné pour les plots (voir main.cpp)