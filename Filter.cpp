#include <stdlib.h>
#include <stdio.h>
#include "App.h"
#define INPUT_HEIGHT (4000)
#define INPUT_WIDTH (6000)
#include <cstdint>
#include <iostream>
#define FILTER_LENGTH (7)
#include "stopwatch.h"
#define OUTPUT_HEIGHT (INPUT_HEIGHT - (FILTER_LENGTH - 1))
#define OUTPUT_WIDTH (INPUT_WIDTH - (FILTER_LENGTH - 1))

unsigned Coefficients[] = {2, 15, 62, 98, 62, 15, 2};
extern stopwatch total_time;
void Filter_horizontal(const unsigned char * Input, unsigned char * Output)
{
  LOOP1: for (int Y = 0; Y < INPUT_HEIGHT; Y++)
    LOOP2: for (int X = 0; X < OUTPUT_WIDTH; X++)
    {
      unsigned int Sum = 0;
      LOOP3: for (int i = 0; i < FILTER_LENGTH; i++)
        Sum += Coefficients[i] * Input[Y * INPUT_WIDTH + X + i];
      Output[Y * OUTPUT_WIDTH + X] = Sum >> 8;
    }
}

void Filter_vertical(const unsigned char * Input, unsigned char * Output)
{
  LOOP1: for (int Y = 0; Y < OUTPUT_HEIGHT; Y++)
    LOOP2: for (int X = 0; X < OUTPUT_WIDTH; X++)
    {
      unsigned int Sum = 0;
      LOOP3: for (int i = 0; i < FILTER_LENGTH; i++)
        Sum += Coefficients[i] * Input[(Y + i) * OUTPUT_WIDTH + X];
      Output[Y * OUTPUT_WIDTH + X] = Sum >> 8;
    }
}

void Filter(const unsigned char * Input, unsigned char * Output)
{
  unsigned char * Temp = (unsigned char*)malloc(INPUT_HEIGHT * OUTPUT_WIDTH);
  total_time.start();
  Filter_horizontal(Input, Temp);
  total_time.stop();
  std::cout << "Average latency of filter horizontal is: " << total_time.avg_latency() << " ns." << std::endl;

  total_time.start();
  Filter_vertical(Temp, Output);
  total_time.stop();
  std::cout << "Average latency of filter  vertical is: " << total_time.avg_latency() << " ns." << std::endl;
  free(Temp);
}

