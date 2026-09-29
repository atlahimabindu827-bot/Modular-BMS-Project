#include <stdio.h>

#define NUM_CELLS 4

int main()
{
    float cellVoltage[NUM_CELLS];
    float highest, lowest;
    float imbalance, previousImbalance;
    float soc;
    float threshold;
    int highestCell = 0, lowestCell = 0;

    printf("===== Modular Battery Management System =====\n");

    // Read cell voltages
    printf("\nEnter voltage of %d cells:\n", NUM_CELLS);

    for(int i = 0; i < NUM_CELLS; i++)
    {
        printf("Cell %d: ", i + 1);
        scanf("%f", &cellVoltage[i]);
    }

    // Read State of Charge
    printf("\nEnter Battery State of Charge (0-100%%): ");
    scanf("%f", &soc);

    // Read previous imbalance
    printf("Enter Previous Voltage Imbalance (V): ");
    scanf("%f", &previousImbalance);

    // Initialize highest and lowest
    highest = cellVoltage[0];
    lowest = cellVoltage[0];
        // Find highest and lowest cell
    for(int i = 1; i < NUM_CELLS; i++)
    {
        if(cellVoltage[i] > highest)
        {
            highest = cellVoltage[i];
            highestCell = i;
        }

        if(cellVoltage[i] < lowest)
        {
            lowest = cellVoltage[i];
            lowestCell = i;
        }
    }

    // Calculate imbalance
    imbalance = highest - lowest;

    // Adaptive threshold
    if(soc >= 80)
        threshold = 0.03;
    else if(soc >= 50)
        threshold = 0.05;
    else
        threshold = 0.08;
            // Display results
    printf("\n========== RESULTS ==========\n");

    printf("Strongest Cell : Cell %d (%.2f V)\n",
           highestCell + 1, highest);

    printf("Weakest Cell   : Cell %d (%.2f V)\n",
           lowestCell + 1, lowest);

    printf("Voltage Imbalance : %.2f V\n", imbalance);

    if(imbalance > previousImbalance)
        printf("Trend : Imbalance Increasing\n");
    else if(imbalance < previousImbalance)
        printf("Trend : Imbalance Decreasing\n");
    else
        printf("Trend : No Change\n");

    printf("Adaptive Threshold : %.2f V\n", threshold);
    if(imbalance > threshold)
        printf("Status : WARNING! Battery Balancing Required.\n");
    else
        printf("Status : Battery is Healthy.\n");

    return 0;
}