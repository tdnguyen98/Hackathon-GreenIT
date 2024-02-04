#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double	get_value(char *s)
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

    /* Open the command for reading. */
	if (argc != 2)
		return (1);
    fp = popen(argv[1], "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        return 1;
    }

    /* Read the output a line at a time - output it. */
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
	moyenne_CPU = total_energy_CPU/i;
	moyenne_GPU = total_energy_GPU/j;
	moyenne_ANE = total_energy_ANE/k;
	moyenne_comb = total_energy_comb/l;
	deviation_CPU = sqrt(((total_energy_CPU - moyenne_CPU) * (total_energy_CPU - moyenne_CPU))/(i - 1))
	deviation_GPU = sqrt(((total_energy_GPU - moyenne_GPU) * (total_energy_GPU - moyenne_GPU))/(j - 1))
	deviation_ANE = sqrt(((total_energy_ANE - moyenne_ANE) * (total_energy_ANE - moyenne_ANE))/(k - 1))
	deviation_comb = sqrt(((total_energy_comb - moyenne_comb) * (total_energy_comb - moyenne_comb))/(l - 1))
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

    /* close */
    pclose(fp);

    return 0;
}
