Repositoire de notes et de code pour le Hackathon GreenIT à l'École 42 Lausanne, 2-4/2/2024.

Le code fonctionne sur OS X, et consiste en un programme à compiler en C (`powermetrics-program.c`), exécuté par un script bash (`script.sh`) qui prend en argument un programme `.app` à évaluer: `bash script.sh path/to/program.app`.

L'évaluation, qui utilise l'outil `powermetrics` d'Apple, est une série de mesures de la consommation énergétique du système, suivie des mêmes mesures pour le programme donné en argument. Les mesures sont une moyenne et les valeurs extrêmes (min/max) de consommation en mW sur la durée de l'évaluation, mesurées séparément par composant (CPU, GPU et ANE/Apple Neural Engine). Ces mesures sont utilisées pour calculer l'énergie dépensée combinée et par composant en Wh, permettant d'avoir une estimation de la consommation énergétique d'un programme.

Équipe: GreenITLantern (@thenguyen – @kly – @fallan)
