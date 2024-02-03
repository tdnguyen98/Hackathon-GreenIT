# Outils existants
## Hardware
- [JouleScope]([url](https://www.joulescope.com/)): This is a hardware-based tool rather than software, but it's worth mentioning because it can monitor the energy use of any device it's connected to, regardless of the operating system.
- Apps comme: Mac Power Monitor, ...
- RAPL (Running Average Power Limit): Available on modern Intel and AMD processors, RAPL allows for the monitoring of power usage across various components of the CPU and memory. While RAPL itself is a hardware feature, various software interfaces and libraries (like pyRAPL) can access these metrics, making it somewhat cross-platform at the application level.

## Software
### Outils natifs OS X/Apple
- [**Activity Monitor** > Energy](https://developer.apple.com/library/archive/documentation/Performance/Conceptual/power_efficiency_guidelines_osx/MonitoringEnergyUsage.html):
	- **Energy Impact.** Assigns an energy impact score to your app, based on how efficiently it is operating. A variety of factors are taken into account when this score is assigned, including CPU usage, network activity, disk I/O, and more.
	- **Avg Energy Impact.** Indicates the average energy impact score over the past 8 hours, or since the time the Mac was restarted.
			=> calculer en % et faire une regle de 3 avec les kWh
	- Panel **Preventing Sleep.** => utiliser cet indicateur pour verifier si une application empeche le systeme de se mettre en veille (voir [Determine When Your App Is Preventing Sleep](https://developer.apple.com/library/archive/documentation/Performance/Conceptual/power_efficiency_guidelines_osx/PrioritizeWorkAtTheAppLevel.html#//apple_ref/doc/uid/TP40013929-CH36-SW7))
- Outils de **Xcode** (environnement de developpement pour applications Apple: OS X, iOS, ...) : meme chose mais pour une app (en developpement)
- Application **Instruments**: version 12 (installee sur les iMacs 2020 de 42) a un outil "Energy log" mais necessite le *root access* (soit un acces administrateur; quand on essaie d'utiliser l'outil comme etudiant, on a l'erreur: "The target device does not support energy logging"). Version 13: la fonctionnalite est supprimee, demeurant dans Xcode (voir [Release notes Xcode 13 - Instruments](https://developer.apple.com/documentation/xcode-release-notes/xcode-13-release-notes#Instruments), "Deprecations")
