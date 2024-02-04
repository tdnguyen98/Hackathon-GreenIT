#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>

float calculate_deviation(float values[], float average, int count) {
    float deviation = 0;

    for (int i = 0; i < count; i++) {
        deviation += fabs(values[i] - average);
    }

    return deviation / count;
}


float	min(float *arr, int n)
{
	int i = 0;
	int min	= 1000000;
	while (i < n)
	{
		if (min > arr[i])
			min = arr[i];
		i++;
	}
	return (min);
}

float	max(float *arr, int n)
{
	int i = 0;
	int max	= 0;
	while (i < n)
	{
		if (max < arr[i])
			max = arr[i];
		i++;
	}
	return (max);
}

int main(int argc, char *argv[]) {
	FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    float cpu_wattages[5000];  // Assuming a maximum of 100 entries
    float gpu_wattages[5000];
    float ane_wattages[5000];
    float total_wattages[5000];
    int entry_count = 0;

    // Read the file until the end or an error
    while (fscanf(file, "%f %f %f %f", &cpu_wattages[entry_count], &gpu_wattages[entry_count], &ane_wattages[entry_count], &total_wattages[entry_count]) == 4) {
        entry_count++;
    }

    fclose(file);

    if (entry_count == 0) {
        printf("No data found in the file.\n");
        return 0;
    }

    // Calculate averages
    float sum_cpu = 0, sum_gpu = 0, sum_ane = 0, sum_total = 0;

    for (int i = 0; i < entry_count; i++) {
        sum_cpu += cpu_wattages[i];
        sum_gpu += gpu_wattages[i];
        sum_ane += ane_wattages[i];
        sum_total += total_wattages[i];
    }

    float average_cpu = sum_cpu / entry_count;
    float average_gpu = sum_gpu / entry_count;
    float average_ane = sum_ane / entry_count;
    float average_total = sum_total / entry_count;

	float min_cpu = min(cpu_wattages, entry_count);
	float max_cpu = max(cpu_wattages, entry_count);

	float min_gpu = min(gpu_wattages, entry_count);
	float max_gpu = max(gpu_wattages, entry_count);
    
	float min_ane = min(ane_wattages, entry_count);
	float max_ane = max(ane_wattages, entry_count);

	float min_tot = min(total_wattages, entry_count);
	float max_tot = max(total_wattages, entry_count);

	float deviation_cpu = calculate_deviation(cpu_wattages, average_cpu, entry_count);
    float deviation_gpu = calculate_deviation(gpu_wattages, average_gpu, entry_count);
    float deviation_ane = calculate_deviation(ane_wattages, average_ane, entry_count);
    float deviation_total = calculate_deviation(total_wattages, average_total, entry_count);
	// Print averages

	printf("\n");
	printf("CPU Power min:\t\t%.2f\t\t", min_cpu);
	if (max_cpu > 10000)
		printf("CPU Power max: \t\t%.2f\t", max_cpu);
	else
		printf("CPU Power max: \t\t%.2f\t\t", max_cpu);
	printf("CPU Power avg: \t\t%.2f\t\t", average_cpu);
	printf("CPU Power deviation: \t\t%.2f\n", deviation_cpu);
	
	printf("GPU Power min:\t\t%.2f\t\t", min_gpu);
	if (max_gpu > 10000)
		printf("GPU Power max: \t\t%.2f\t", max_gpu);
	else
		printf("GPU Power max: \t\t%.2f\t\t", max_gpu);
	printf("GPU Power avg: \t\t%.2f\t\t", average_gpu);
	printf("GPU Power deviation: \t\t%.2f\n", deviation_gpu);
	
	printf("ANE Power min:\t\t%.2f\t\t", min_ane);
	printf("ANE Power max: \t\t%.2f\t\t", max_ane);
	printf("ANE Power avg: \t\t%.2f\t\t", average_ane);
	printf("ANE Power deviation: \t\t%.2f\n", deviation_ane);
	
	printf("Combined Power min: \t%.2f\t\t", min_tot);
	if (max_tot > 10000)
		printf("Combined Power max: \t%.2f\t", max_tot);
	else
		printf("Combined Power max: \t%.2f\t\t", max_tot);
	printf("Combined Power avg:\t%.2f\t\t", average_total);
	printf("Combined Power deviation: \t%.2f\n", deviation_total);

    return 0;
}


/* double	get_value(char *s)
{
	char *number;
	double value;
	int i = 0;

	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			number = &s[i];
			break;
		}
		i++;
	}
	value = atof(number);
	return (value);
}

int main(int argc, char *argv[]) {
    FILE *fp;
    char path[1035];
	double i = 0;
	double j = 0;
	double k = 0;
	double l = 0;
	double value_CPU = 0;
	double total_energy_CPU = 0;
	double max_value_CPU = 0;
	double min_value_CPU = 100000;
	double value_GPU = 0;
	double total_energy_GPU = 0;
	double max_value_GPU = 0;
	double min_value_GPU = 100000;
	double value_ANE = 0;
	double total_energy_ANE = 0;
	double max_value_ANE = 0;
	double min_value_ANE = 100000;
	double value_comb = 0;
	double total_energy_comb = 0;
	double max_value_comb = 0;
	double min_value_comb = 100000;
	double moyenne_CPU = 0;
	double moyenne_GPU = 0;
	double moyenne_ANE = 0;
	double moyenne_comb = 0;
	double deviation_CPU = 0;
	double deviation_GPU = 0;
	double deviation_ANE = 0;
	double deviation_comb = 0;
	double consumption = 0;

    // Open the command for reading.
	if (argc != 2)
		return (1);
    fp = popen(argv[1], "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        return 1;
    }

    // Read the output a line at a time - output it.
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        if (strstr(path, "CPU Power") != NULL) {
            value_CPU = get_value(path);
			if (value_CPU > max_value_CPU)
				max_value_CPU = value_CPU;
			if (value_CPU < min_value_CPU)
				min_value_CPU = value_CPU;
			total_energy_CPU += value_CPU;
			i += 1;
        }
		if (strstr(path, "GPU Power") != NULL) {
            value_GPU = get_value(path);
			if (value_GPU > max_value_GPU)
				max_value_GPU = value_GPU;
			if (value_GPU < min_value_GPU)
				min_value_GPU = value_GPU;
			total_energy_GPU += value_GPU;
			j += 1;
        }
		if (strstr(path, "ANE Power") != NULL) {
            value_ANE = get_value(path);
			if (value_ANE > max_value_ANE)
				max_value_ANE = value_ANE;
			if (value_ANE < min_value_ANE)
				min_value_ANE = value_ANE;
			total_energy_ANE += value_ANE;
			k += 1;
        }
		if (strstr(path, "Combined Power") != NULL) {
             value_comb = get_value(path);
			if (value_comb > max_value_comb)
				max_value_comb = value_comb;
			if (value_comb < min_value_comb)
				min_value_comb = value_comb;
			total_energy_comb += value_comb;
			l += 1;
        }
    }
	// average
	moyenne_CPU = total_energy_CPU/i;
	moyenne_GPU = total_energy_GPU/j;
	moyenne_ANE = total_energy_ANE/k;
	moyenne_comb = total_energy_comb/l;

	// standard deviation
	deviation_CPU = sqrt(((total_energy_CPU - moyenne_CPU) * (total_energy_CPU - moyenne_CPU))/(i - 1));
	deviation_GPU = sqrt(((total_energy_GPU - moyenne_GPU) * (total_energy_GPU - moyenne_GPU))/(j - 1));
	deviation_ANE = sqrt(((total_energy_ANE - moyenne_ANE) * (total_energy_ANE - moyenne_ANE))/(k - 1));
	deviation_comb = sqrt(((total_energy_comb - moyenne_comb) * (total_energy_comb - moyenne_comb))/(l - 1));

	// total Wh consumption calculation
		// X mWatts == (X / 1000) Watts && 1 Watt for 5 minutes = (1 / 12) Watt for 1 hour (Wh)
	consumption = (moyenne_comb / 12000);
	
		
	printf("\n");
	printf("CPU Power min:\t\t%.2f\t\t", min_value_CPU);
	if (max_value_CPU > 10000)
		printf("CPU Power max: \t\t%.2f\t", max_value_CPU);
	else
		printf("CPU Power max: \t\t%.2f\t\t", max_value_CPU);
	printf("CPU Power avg: \t\t%.2f\t\t", moyenne_CPU);
	print("CPU Power deviation: \t\t%.2\n", deviation_CPU);
	
	printf("GPU Power min:\t\t%.2f\t\t", min_value_GPU);
	if (max_value_GPU > 10000)
		printf("GPU Power max: \t\t%.2f\t", max_value_GPU);
	else
		printf("GPU Power max: \t\t%.2f\t\t", max_value_GPU);
	printf("GPU Power avg: \t\t%.2f\n", moyenne_GPU);
	print("GPU Power deviation: \t\t%.2\n", deviation_GPU);
	
	printf("ANE Power min:\t\t%.2f\t\t", min_value_ANE);
	printf("ANE Power max: \t\t%.2f\t\t", max_value_ANE);
	printf("ANE Power avg: \t\t%.2f\n", moyenne_ANE);
	print("ANE Power deviation: \t\t%.2\n", deviation_ANE);
	
	printf("Combined Power min: \t%.2f\t\t", min_value_comb);
	if (max_value_comb > 10000)
		printf("Combined Power max: \t%.2f\t", max_value_comb);
	else
		printf("Combined Power max: \t%.2f\t\t", max_value_comb);
	printf("Combined Power avg:\t%.2f\n", moyenne_comb);
	print("Combined Power deviation: \t\t%.2\n", deviation_comb);

		// precision: if 5mW average over 5 minutes, then total consumption is 0.0004 Wh. (Precision: +-1 mW)
	printf("Wh consumed during test: \t%.4f\n", consumption);

    // close
    pclose(fp);

    return 0;
} */
