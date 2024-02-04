# Comment mesurer le cout electrique d'un software

## Brainstorming

### Problemes
- Isoler les activites sur une machine
- Le monitoring (par exemple *Activity Monitor*) consomme lui-même beaucoup de ressources et peut donc fausser ou compliquer le calcul
- marge d'erreur plus grosse que consommation du programme pour beaucoup de programmes
- Pas vraiment calculable directement, du coup c'est une estimation, et pour arriver au kWh on fait des estimations sur des estimnations sur des estimations, du coup la marge d'erreur est enorme, et le calcul perd en pertinence. Du coup les approches existantes sont pas tellement sur la mesure precise mais plus thematique ou fonctionnelle, par exemple on voit que telle application est gourmande en CPU, donc on utilise des pratiques specifiques pour optimiser son usage du CPU, ou de la memoire, etc. sans chercher un benchmark precis qui est difficilement atteignable.
- [Calculer la consoation d'energie d'un programme en C ?](https://stackoverflow.com/questions/40707136/energy-consumption-of-an-algorithm-in-c-code)
> It is much simpler (for certain degrees of "simple") to count the assembler commands and multiply them with the respective latencies (Listed in the technical specs, e.g. for a randomly chosen MCU from the Wiki list: http://www.atmel.com/Images/doc32002.pdf). This is still not exact, division for example might take a different amount of CPU cycles depending on the input, CPU architecture and implementation in the hardware, but it comes quite close and is rather simple, although a bit tedious.

> And than there are the loops with a completely unknown number of iterations, input taking different paths with different runtimes and much more. The people writing encryption software know more about it, especially how to avoid it. You might not like their solutions.

### Questions
- A quel point la surcharge compte dans la consommation totale ?
- Comment creer un environnement stable pour avoir des mesures consistantes et precises
- while versus for
- les FLOPS (floating operations per second) comme unite de mesure ?


### Observations
- La mesure de l'utilisation du CPU, RAM, ... est instantanee
- Activity monitor separe l-usage du CPU selon que le process est lie au systeme ou aux activites de l-utilisateur, notamment les apps lancees
- Le choix du language importe beaucoup, si l'on veut utiliser moins d'energie, on devrait plutot s'orienter vers des language comme C, RUST et C++

## Idée
- formule pour convertir l'utilisation mesuree des ressources (CPU, RAM, systeme?) en kWh (watts heure)

## Outils
Voir le fichier [Outils-de-mesure.md](Outils-de-mesure.md) pour une discussion detaillee
### Hardware
- [JouleScope]([url](https://www.joulescope.com/)): This is a hardware-based tool rather than software, but it's worth mentioning because it can monitor the energy use of any device it's connected to, regardless of the operating system.
- Apps comme: Mac Power Monitor, ...
- RAPL (Running Average Power Limit): Available on modern Intel and AMD processors, RAPL allows for the monitoring of power usage across various components of the CPU and memory. While RAPL itself is a hardware feature, various software interfaces and libraries (like pyRAPL) can access these metrics, making it somewhat cross-platform at the application level.

### Software
- [**Activity Monitor** > Energy](https://developer.apple.com/library/archive/documentation/Performance/Conceptual/power_efficiency_guidelines_osx/MonitoringEnergyUsage.html):
	- **Energy Impact.** Assigns an energy impact score to your app, based on how efficiently it is operating. A variety of factors are taken into account when this score is assigned, including CPU usage, network activity, disk I/O, and more.
	- **Avg Energy Impact.** Indicates the average energy impact score over the past 8 hours, or since the time the Mac was restarted.
			=> calculer en % et faire une regle de 3 avec les kWh
	- Panel **Preventing Sleep.** => utiliser cet indicateur pour verifier si une application empeche le systeme de se mettre en veille (voir [Determine When Your App Is Preventing Sleep](https://developer.apple.com/library/archive/documentation/Performance/Conceptual/power_efficiency_guidelines_osx/PrioritizeWorkAtTheAppLevel.html#//apple_ref/doc/uid/TP40013929-CH36-SW7))
- Outils de **Xcode** (environnement de developpement pour applications Apple: OS X, iOS, ...) : meme chose mais pour une app (en developpement)
- Application **Instruments**: version 12 (installee sur les iMacs 2020 de 42) a un outil "Energy log" mais necessite le *root access* (soit un acces administrateur; quand on essaie d'utiliser l'outil comme etudiant, on a l'erreur: "The target device does not support energy logging"). Version 13: la fonctionnalite est supprimee, demeurant dans Xcode (voir [Release notes Xcode 13 - Instruments](https://developer.apple.com/documentation/xcode-release-notes/xcode-13-release-notes#Instruments), "Deprecations")

- Pour reference, la consommation des iMacs de 42 est de:

|   |   |   |   |
|---|---|---|---|
|[iMac (Retina 5K, 27-inch, 2020)](https://support.apple.com/en-us/109513)<br><br>27-inch Retina 5K display, 3.6GHz 10-Core i9, 128GB 2666MHz DDR4 SDRAM, 8TB Solid State Drive, AMD Radeon Pro 5700 XT with 16GB memory |   |   |   |
|Power Consumption|   |Thermal Output|   |
|**Idle**|**CPU Max**|**Idle**|**CPU Max**|
|74W|295W|252 BTU/h|1007 BTU/h|


## Bonnes pratiques pour coder de manière general :

Yes, the way you code your source code can impact the power consumption of the device. While individual lines of code may not directly influence power consumption, the overall design, algorithms, and programming practices can have an indirect impact on energy efficiency. Here are some aspects to consider:

1. **Algorithmic Efficiency:** The choice of algorithms and data structures can significantly affect the energy consumption of a program. Using more efficient algorithms that require fewer computational steps can reduce the overall energy usage.
    
2. **Optimizations and Compiler Flags:** Compiler optimizations and flags can impact the performance and power consumption of your code. Enabling optimization flags (-O) during compilation can result in more efficient machine code, potentially reducing the execution time and, consequently, power consumption.
    
3. **I/O Operations:** Excessive I/O operations, especially in tight loops, can lead to increased power consumption. Minimizing unnecessary file reads/writes and network operations can improve energy efficiency.
    
4. **Concurrency and Parallelism:** Efficient use of parallelism and concurrency can lead to better utilization of hardware resources. However, poorly designed parallelism may result in increased power consumption due to synchronization overhead.
    
5. **Memory Usage:** Efficient memory management is crucial for minimizing power consumption. Avoiding unnecessary allocations, optimizing data structures, and reducing memory access patterns can contribute to energy efficiency.
    
6. **Idle States and Sleep Modes:** Code that allows the system to enter low-power states during idle periods can have a positive impact on overall power consumption. Make use of system calls or platform-specific APIs to enable sleep or low-power modes when appropriate.
    
7. **Hardware-Specific Considerations:** Understanding the architecture and features of the target hardware is essential. Some hardware platforms offer features like dynamic voltage and frequency scaling (DVFS) or power-gating, which can be leveraged to optimize power usage.
    
8. **Energy Profiling:** Use profiling tools to analyze the energy consumption of your code. Tools like `perf` on Linux or vendor-specific tools can provide insights into which parts of your code consume the most energy, helping you focus optimization efforts. For software developers, starting with profiling to identify major energy consumers and then applying targeted optimizations can be an effective strategy.

9. **Energy-Aware Scheduling and Resource Allocation**
In environments like data centers or cloud computing platforms, energy-aware scheduling algorithms can dynamically adjust the allocation of computational tasks based on current power consumption and thermal states, thus optimizing overall energy use.

10. **Use of Green Frameworks and Libraries**
Some frameworks and libraries are designed with energy efficiency in mind, providing developers with tools and functions that are optimized for lower power consumption. For example, GreenSQL for database queries or energy-efficient networking libraries that minimize data transfer times and power use.

It's important to note that the impact of code optimizations on power consumption may vary depending on the specific hardware architecture and the workload of the application. Therefore, it's recommended to profile and measure the energy consumption of your code using specialized tools on the target platform to make informed decisions about optimizations.

### Explanation of point 3 and 4

#### 1. I/O Operations:

**Explanation:** I/O (Input/Output) operations involve reading from or writing to external sources, such as files, databases, or network resources. These operations can be relatively slow compared to CPU-bound tasks, and excessive I/O operations, especially in tight loops, can lead to increased power consumption.

**Why it Matters:**

- I/O operations often involve interactions with external devices or remote systems, introducing latency and potentially causing the CPU to wait for data.
- Frequent file reads/writes or network operations may keep the system awake and prevent it from entering low-power states, increasing overall power consumption.
- Disk and network activities can be energy-intensive, and minimizing unnecessary I/O operations can contribute to energy efficiency.

**Optimizations:**

- **Batching Operations:** Minimize the number of individual I/O operations by batching them together, reducing the overhead of opening and closing files or initiating network connections.
- **Caching:** Cache frequently accessed data to reduce the need for repeated I/O operations.
- **Asynchronous I/O:** Use asynchronous I/O operations to allow the program to continue executing other tasks while waiting for I/O completion.

#### 2. Concurrency and Parallelism:

**Explanation:** Concurrency and parallelism involve executing multiple tasks simultaneously. Concurrency typically deals with managing multiple tasks without necessarily running them simultaneously, while parallelism involves the simultaneous execution of tasks on multiple processors or cores.

**Why it Matters:**

- **Efficient Utilization of Resources:** Properly designed parallelism can lead to better utilization of available hardware resources, reducing the overall time required to complete a task.
- **Synchronization Overhead:** Poorly designed parallelism may introduce synchronization overhead, where multiple threads or processes contend for shared resources. Excessive synchronization can lead to increased power consumption.
- **Idle Cores:** If not managed correctly, parallelism might lead to some processor cores idling while waiting for synchronization, reducing overall energy efficiency.

**Optimizations:**

- **Load Balancing:** Distribute tasks evenly among available processing units to avoid idle cores.
- **Fine-Grained Locking:** Minimize the use of locks and use fine-grained locking strategies to reduce contention and synchronization overhead.
- **Task Decomposition:** Break down tasks into smaller, independent subtasks that can be executed in parallel.

## Conseils
> I have been doing a lot of energy optimization (for squeezing more battery life for smart watch). The principle is simple, energy efficiency is just another step in optimizing. You optimize first for memory usage, then cpu and finally for energy efficiency. And simplest way to see each step, is to first not store or duplicate what you don't need, then don't compute what you don't need and you will have energy efficiency. Energy efficiency come from not hitting the main memory and staying in the cpu cache as much as possible. It comes also from less branch prediction (every branch prediction that is incorrect has to be undone and restarted, consume energy).

> From there, you will understand that some language and architecture are better than others for energy efficiency. In the architecture side of things, if you service doesn't need to run, it just shouldn't (this give advantage to things like lambda), but if it should run all the time, the starting cost of lambda would be counter productive. In term of language, most of the time you might want to go with compiled language. The main issue that you will face trying to optimize for energy is how to measure things. On a smart watch we had hardware that told us the energy consumption and we could write benchmark to check if what we did paid off or not. In the case of remote server, I have not seen that kind of capability (cloud provider can complain about energy consumption, but if they don't give the tool to optimizethings for...). And optimizing without a benchmark is most of the time picking a bad guess.

> This is true, if you are working on something that scale a lot or has a very long running duration. Otherwise you main energy consumption point might be your own computer.

> In summary, optimizing I/O operations involves minimizing the frequency and impact of external data transfers, while optimizing concurrency and parallelism involves efficiently utilizing available hardware resources and minimizing synchronization overhead to avoid unnecessary power consumption. Both optimizations contribute to overall energy efficiency in software systems.
