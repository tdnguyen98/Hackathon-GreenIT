Problemes
- Isoler les activites sur une machine
- marge d'erreur plus grosse que consommation du programme pour beaucoup de programmes

Questions
- A quel point la surcharge compte dans la consommation totale ?
- Comment creer un environnement stable pour avoir des mesures consistantes et precises
- while versus for
- les FLOPS (floating operations per second) comme unite de mesure ?


Observations
- La mesure de l'utilisation du CPU, RAM, ... est instantanee
- Activity monitor separe l-usage du CPU selon que le process est lie au systeme ou aux activites de l-utilisateur, notamment les apps lancees

# idee
- formule pour convertir l'utilisation mesuree des ressources (CPU, RAM, systeme?) en kWh (watts heure)


# Outils
- Mac Power Monitor

- [Activity Monitor > Energy](https://developer.apple.com/library/archive/documentation/Performance/Conceptual/power_efficiency_guidelines_osx/MonitoringEnergyUsage.html):
	- **Energy Impact.** Assigns an energy impact score to your app, based on how efficiently it is operating. A variety of factors are taken into account when this score is assigned, including CPU usage, network activity, disk I/O, and more.
	- **Avg Energy Impact.** Indicates the average energy impact score over the past 8 hours, or since the time the Mac was restarted.
			=> calculer en % et faire une regle de 3 avec les kWh
	- Outils Xcode: meme chose mais pour une app (en developpement)
	- Panel **Preventing Sleep.** => utiliser cet indicateur pour verifier si une application empeche le systeme de se mettre en veille (voir [Determine When Your App Is Preventing Sleep](https://developer.apple.com/library/archive/documentation/Performance/Conceptual/power_efficiency_guidelines_osx/PrioritizeWorkAtTheAppLevel.html#//apple_ref/doc/uid/TP40013929-CH36-SW7))

- Application **Instruments**: "The target device does not support energy logging" => need root access ? 

- Pour reference, la consommation des iMacs de 42 est de:

|   |   |   |   |
|---|---|---|---|
|[iMac (Retina 5K, 27-inch, 2020)](https://support.apple.com/en-us/109513)<br><br>27-inch Retina 5K display, 3.6GHz 10-Core i9, 128GB 2666MHz DDR4 SDRAM, 8TB Solid State Drive, AMD Radeon Pro 5700 XT with 16GB memory |   |   |   |
|Power Consumption|   |Thermal Output|   |
|**Idle**|**CPU Max**|**Idle**|**CPU Max**|
|74W|295W|252 BTU/h|1007 BTU/h|
