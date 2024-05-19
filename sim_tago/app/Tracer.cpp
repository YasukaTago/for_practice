#include "Tracer.h" // <1>

Tracer::Tracer():
  leftWheel(PORT_C), rightWheel(PORT_B), colorSensor(PORT_2) { // <2>
}

void Tracer::init() {
  init_f("Tracer");
}

float Tracer::calc_prop_value() {
  const float Kp =0.8;
  const int target = 10;
  const int bias = 0;

  int diff = colorSensor .getBrightness()-target;
  return (Kp*diff+bias);  //10<get<20 at start point
}

int count=0;

float Tracer::color_value_count() { 
 if(colorSensor .getColorNumber()==2){//colorSensor
    count++;
  }else{
    count=0;
  }

  return (count);  
}

void Tracer::terminate() {
    msg_f("Stopped.", 1);
    leftWheel.stop();  // <1>
    rightWheel.stop();  
}

void Tracer::run(){
  msg_f("running...", 1);
  float turn = calc_prop_value();
  float count = color_value_count();

  if(count>3){
    msg_f("Stopped.", 1);
    leftWheel.stop();  // <1>
    rightWheel.stop();
    ev3_led_set_color(LED_OFF);

  }else{
    int pwm_l = pwm - turn;
    int pwm_r = pwm + turn;
    leftWheel.setPWM(pwm_l);
    rightWheel.setPWM(pwm_r);
  }
}
