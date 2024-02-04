# Mesures

## Cibles
- Composants:
  - CPU
  - GPU
  - ANE (Apple Neural Engine, puce spéciale pour machine learning)
- Total

## Temporalité
### Durée du test
- Charge au repos (idle): 5 minutes
- Charge de travail: 5 minutes

- Justification: (source: GPT4)
  - GPT4 proposait 15 minutes ou plus de monitoring au repos, mais on a décidé 5 minutes pour simplifier notre test, avec notre script et la contrainte de temps
  - Le risque est le système n'ait pas eu le temps de se stabiliser, mais on peut le contrebalancer en limitant l'activité sur la machine et en faisant plusieurs tests. 

 ### Intervalles de sampling
- Intervalles: 200 ms (source: GPT4 suggère 100-500ms pour applications dynamiques, 1000-2000ms pour application à charge de travail plus stables). N.b.: pour vérifier précisions des intervalles de sampling , une partie du script l'enregistre dans un fichier séparé qu'on peut vérifier ensuite.
<br>Note sur les intervalles nécessaires ("granularité"):
pour l'usage général d'énergie, par exemple sur 1 minute, des intervalles plus longs (1000-2000ms), peuvent suffir. Des intervalles plus courts (100-500ms) sont utiles pour identifier les pics de consommation liés à des opérations spécifiques de l'application.
<br>Notre choix: 200ms en travail pour capturer les pics éventuels, ce qui fait 1500 observations au total pour chaque test de 5 minute, et 200 ms au repos aussi pour la cohérence, et parce que le fichier généré n'est pas gros

## Benchmarking
- Repos: voir document environnement de test
- Travail: Jeu vidéo Théo – lancer commande pour faire danser personnages le temps du benchmark

## Statistiques
- Moyenne simple (sur la durée de test)
- Variance (std deviation)
- Valeurs extrêmes (min, max)
- Consommation totale
