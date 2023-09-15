#include "App.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <iostream>
#define DATA_SIZE (12000 * 8000)
#define STAGES (4)
#include "stopwatch.h"


stopwatch total_time;
stopwatch time_projection;
unsigned char *Data[STAGES + 1];

void Exit_with_error(void)
{
  perror(NULL);
  exit(EXIT_FAILURE);
}

void Load_data(void)
{
  FILE *File = fopen("Input.bin", "rb");
  if (File == NULL)
    Exit_with_error();

  if (fread(Data[0], 1, DATA_SIZE, File) != DATA_SIZE)
    Exit_with_error();

  if (fclose(File) != 0)
    Exit_with_error();
}

void Store_data(const char *Filename, int Stage, unsigned int Size)
{
  FILE *File = fopen(Filename, "wb");
  if (File == NULL)
    Exit_with_error();

  if (fwrite(Data[Stage], 1, Size, File) != Size)
    Exit_with_error();

  if (fclose(File) != 0)
    Exit_with_error();
}

int main()
{
  for (int i = 0; i <= STAGES; i++)
  {
    // We could strictly allocate less memory for some of these buffers, but
    // that is irrelevant here.
    Data[i] = (unsigned char *)malloc(DATA_SIZE);
    if (Data[i] == NULL)
      Exit_with_error();
  }
  Load_data();
  total_time.start();
  Scale(Data[0], Data[1]);
  total_time.stop();
  std::cout << "Average latency of scale is: " << total_time.avg_latency() << " ns." << std::endl;

  Filter(Data[1], Data[2]);



  total_time.start();
  Differentiate(Data[2], Data[3]);
  total_time.stop();
  std::cout << "Average latency of Differentiate is: " << total_time.avg_latency() << " ns." << std::endl;

  total_time.start();
  int Size = Compress(Data[3], Data[4]);
  total_time.stop();
  std::cout << "Average latency of compress is: " << total_time.avg_latency() << " ns." << std::endl;

  Store_data("Output.bin", 4, Size);

  for (int i = 0; i <= STAGES; i++)
    free(Data[i]);

  puts("Application completed successfully.");

  return EXIT_SUCCESS;
}
