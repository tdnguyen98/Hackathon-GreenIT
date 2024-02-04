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
	if (argc != 3 )
		return 3;

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

	float consumption = (average_total * atof(argv[2])  / (1000 * 3600 )); // 3600 * 1000 * X seconde de test
	float cpu_consumption = (average_cpu * atof(argv[2]) / (1000 * 3600 ));
	float gpu_consumption = (average_gpu  * atof(argv[2]) / (1000 * 3600));
	float ane_consumption = (average_ane * atof(argv[2]) / (1000 * 3600 ));

	// Print averages

	printf("\n");
	printf("%s\n", argv[1]);
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
	if (average_total > 10000)
		printf("Combined Power avg:\t%.2f\t", average_total);
	else
		printf("Combined Power avg:\t%.2f\t\t", average_total);
	printf("Combined Power deviation: \t%.2f\n", deviation_total);

	printf("Wh consumed during test: \t%.4f (CPU: %.4f; GPU: %.4f; ANE: %.4f)\n", consumption, cpu_consumption, gpu_consumption, ane_consumption);

    return 0;
}
