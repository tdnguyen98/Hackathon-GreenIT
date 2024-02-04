# Outils existants
Kieni et al. 2020:<br>
- Taux d'erreur eleve des methodes basees software (vs outils de mesure hardware) et methodes pour le corriger:
>While standard operating system metrics (CPU, memory, disk, or network), directly computed by the kernel, tend to exhibit a large error rate due to their lack of precision [11],[13], HWPC can be directly gathered from the processor (e.g., number of retired instructions, cache misses, non-halted cycles). Modern processors provide a variable number of HWPC events, depending on the generation of the micro-architectures and the model of the CPU. As shown by Bellosa [10] and Bircher [14], some HWPC events are highly correlated with the processor power consumption, while the authors in [15]
concluded that not all HPC are relevant, as they may not be directly correlated with dynamic power.
><br><br>C. Limitations & Opportunities<br>
>To the best of our knowledge, the state of the art in hardware power meters often imposes hardware investments to provide power measurements with an high accuracy, but a coarse granularity, while **software-defined power meters target finegrained power monitoring, but often fail to reach high accuracy on any architecture and/or workload**.
><br>Power modeling often builds on these raw metrics to apply learning techniques [16] to correlate the metrics with hardware power measurements using various regression models, which are so far mostly linear [12]. 


## Hardware
- [JouleScope](https://www.joulescope.com/):
>This is a hardware-based tool rather than software, but it's worth mentioning because it can monitor the energy use of any device it's connected to, regardless of the operating system.

## Software
### Apps
- Apps comme: Mac Power Monitor, HWInfo...

### Outils de fabricants
- RAPL (Running Average Power Limit)
>Available on modern Intel and AMD processors, RAPL allows for the monitoring of power usage across various components of the CPU and memory. While RAPL itself is a hardware feature, various software interfaces and libraries (like pyRAPL) can access these metrics, making it somewhat cross-platform at the application level.
- VTune (Intel):
- uProf (AMD): 

### Outils natifs OS X/Apple
- [**Activity Monitor** > Energy](https://developer.apple.com/library/archive/documentation/Performance/Conceptual/power_efficiency_guidelines_osx/MonitoringEnergyUsage.html):
	- **Energy Impact.**
 >Assigns an energy impact score to your app, based on how efficiently it is operating. A variety of factors are taken into account when this score is assigned, including CPU usage, network activity, disk I/O, and more.<br>
	- **Avg Energy Impact.** (note: ne semble pas exister sur les iMacs de 42)
>Indicates the average energy impact score over the past 8 hours, or since the time the Mac was restarted.<br>
			=> calculer en % et faire une regle de 3 avec les kWh<br>
	- Panel **Preventing Sleep.** => utiliser cet indicateur pour verifier si une application empeche le systeme de se mettre en veille (voir [Determine When Your App Is Preventing Sleep](https://developer.apple.com/library/archive/documentation/Performance/Conceptual/power_efficiency_guidelines_osx/PrioritizeWorkAtTheAppLevel.html#//apple_ref/doc/uid/TP40013929-CH36-SW7))
<br><br>[Activity Monitor User Guide](https://support.apple.com/en-ae/guide/activity-monitor/actmntr43697/mac):
>- The energy use of individual apps and their processes is displayed in the upper part of the Activity Monitor window.<br>
>- Energy Impact: A relative measure of the current energy consumption of the app (lower is better).<br>
>- 12 hr Power: The average energy impact of the app in the last 12 hours, or since the Mac computer started (lower is better). This column only appears on Mac laptops.<br>
>- App Nap: Whether App Nap is active for this app.<br>
>- Graphics Card: Whether the app requires a high performance graphics card. This column only appears on Mac computers with one or more graphics cards.<br>
>- Preventing Sleep: Whether this app is preventing your Mac from going to sleep.<br>
>- User: The user name running the process.<br>
>- The bottom of the window shows information about your overall energy use. If you have a Mac laptop, you see additional information related to its battery.


- Outils de **Xcode** (environnement de developpement pour applications Apple: OS X, iOS, ...) : meme chose mais pour une app (en developpement)
- Application **Instruments**: version 12 (installee sur les iMacs 2020 de 42) a un outil "Energy log" mais necessite le *root access* (soit un acces administrateur; quand on essaie d'utiliser l'outil comme etudiant, on a l'erreur: "The target device does not support energy logging"). Version 13: la fonctionnalite est supprimee, demeurant dans Xcode (voir [Release notes Xcode 13 - Instruments](https://developer.apple.com/documentation/xcode-release-notes/xcode-13-release-notes#Instruments), "Deprecations")
- `powermetrics`: doit etre invoque comme superuser/root/admin

### Outils Linux
-  **[PowerAPI]([url](https://powerapi.org/reference/overview/))**:
	- Solution libre (FOSS: free and open source software) developpee en ce moment par des universites francaises, actuellement uniquement disponible sur Linux, bien que la solution soit aussi un modele general pour estimer la consommation electrique d'un programme (voir le point "Fonctionnement" plus bas). Focalisee aujourd'hui sur la consommation electrique des serveurs (voir [publication scientifique sur SmartWatts](https://inria.hal.science/hal-02470128).
	- Le projet a developpe plusieurs outils pour mesurer la consommation electrique: de morceaux de code (**PyJoule**, une librairie Python),  de process, etc. Voir [le repositoire Github de PowerAPI](https://github.com/orgs/powerapi-ng/repositories?type=all). Ils ont egalement commence a developper un outil pour mesurer la consommation d'un programme dans un machine virtuelle, [VirtualWatts](https://github.com/powerapi-ng/virtualwatts-formula), mais la documentation du projet n'est pas disponible et il semble avoir ete abandonne en 2020.
	- Fonctionnement:
 		- un *Sensor* qui collecte des donnees brutes correlees avec la consommation electrique de la machine.
     <br> => actuellement, uniquement [HWPC (HardWare Performance Counter)](https://powerapi.org/reference/sensors/hwpc-sensor/), un outil mesurant la performance et consommation de CPUs Intel (Sandy Bridge et plus recents, donc post-2011) et AMD Zen (1,2,34). Les processeurs de type Powe/ARM/RISCV ne sont pas supportes. HWPC [exploite](https://github.com/powerapi-ng/hwpc-sensor) l'API `perf` du kernel Linux, uniquement accessible au *root*, et la technologie RAPL. Le senseur ne peut pas etre utilise dans une machine virtuelle.
     	- une *Formula* qui calcule une estimation de la consommation electrique du software a partir des donnees collectees par le *Sensor*
       <br> => actuellement, uniquement [SmartWatts](https://powerapi.org/reference/formulas/smartwatts/), qui fonctionne avec les donnees du HWPC et estime la consommation electrique d'un programme [qui tourne dans un *container*](https://github.com/powerapi-ng/smartwatts-formula), un environnement isole qui peut etre un container Docker, un pod Kubernetes, une machine virtuelle Libvirt, etc. L'explication du systeme, notamment le choix des metriques utilisees et la methode d'estimation de la consommation electrique, est detaillee dans [une publication scientifique de 2020](https://inria.hal.science/hal-02470128).

## Outils Windows
- [HWInfo](https://www.hwinfo.com/download/)
