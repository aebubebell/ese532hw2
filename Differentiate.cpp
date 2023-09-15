#define HEIGHT (3994)
#define WIDTH (5994)

// #include "stopwatch.h"
// stopwatch total_time;
// stopwatch time_projection;
// stopwatch total_time;
void Differentiate(const unsigned char * Input, unsigned char * Output)
{
  //  total_time.start();
  for (int Y = 0; Y < HEIGHT; Y++)
    for (int X = 0; X < WIDTH; X++)
    {
      int Average = 0;
      if (Y > 0 && X > 0)
        Average = (Input[WIDTH * (Y - 1) + X] + Input[WIDTH * Y + X - 1]) / 2;
      else if (Y > 0)
        Average = Input[WIDTH * (Y - 1) + X];
      else if (X > 0)
        Average = Input[WIDTH * Y + X - 1];

      unsigned char Diff = Input[WIDTH * Y + X] - Average;

      Output[Y * WIDTH + X] = Diff;
    }
  //  total_time.stop();
}
//std::cout << "Average latency of each loop iteration is: " << total_time.avg_latency() << " ns." << std::endl;