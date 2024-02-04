# Mesures

## Cibles
- Composants:
  - CPU
  - GPU
  - ANE (Apple Neural Engine, puce spéciale pour machine learning)
- Total

## Temporalité
- Charge au repos (idle): 15 minutes (source: GPT4)
- Charge de travail: 1 min
- Intervalles: 200 ms (source: GPT4 suggère 100-500ms pour applications dynamiques, 1000-2000ms pour application à charge de travail plus stables). N.b.: pour vérifier précisions des intervalles de sampling , une partie du script l'enregistre dans un fichier séparé qu'on peut vérifier ensuite.
<br>Note sur les intervalles nécessaires ("granularité"):
pour l'usage général d'énergie, par exemple sur 1 minute, des intervalles plus longs (1000-2000ms), peuvent suffir. Des intervalles plus courts (100-500ms) sont utiles pour identifier les pics de consommation liés à des opérations spécifiques de l'application.
<br>Notre choix: 200ms en travail pour capturer les pics éventuels, ce qui fait 300 observations au total pour chaque test de 1 minute, et 200 ms au repos aussi pour la cohérence, et parce que le fichier généré n'est pas trop gros

## Benchmarking
- Repos: voir environnement de travail
- Travail: Jeu vidéo Théo – lancer commande pour faire danser personnages le temps du benchmark

# Statistiques
- Moyenne simple
- Variance (std deviation)
- Valeurs extrêmes (min, max)
