#include "gauge_conversions.h"

#define INPUT_START 156.0
#define INPUT_END 428.0
#define OUTPUT_START    0.0
#define OUTPUT_END      120.0

int rotation_value=INPUT_START;

int angle_to_speed(int angle)
{
    float speed;
    float input_start=INPUT_START;
    float input_end=INPUT_END;
    float output_start=OUTPUT_START;
    float output_end=OUTPUT_END;

    speed = output_start + (((output_end - output_start) / (input_end - input_start)) * (angle - input_start));
    //return (int)speed;
    return static_cast<int>(speed);

}

int speed_to_angle(int speed)
{

    float angle;
    float input_start=INPUT_START;
    float input_end=INPUT_END;
    float output_start=OUTPUT_START;
    float output_end=OUTPUT_END;

    angle = input_start + (((input_end - input_start) / (output_end - output_start)) * (speed - output_start));
   // return (int)angle;
return static_cast<int>(angle);

}
