
#include <PID_v1.h>

#define PIN_PWM 9
#define PIN_SENSOR A1
//#define pot A0
double setpoint = 40.0;  // Setpoint de temperatura
double kp = 0.5;       // Ganho proporcional
double ki = 0.03;       // Ganho integral
double kd = 0.0;        // Ganho derivativo


double input, output;
PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

void setup()
{
  Serial.begin(9600);
  pinMode(PIN_PWM, OUTPUT);
 // pinMode(PIN_SENSOR, INPUT);
  analogReference(DEFAULT);
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 255);  // Limitar a saída do PID entre 0 e 255
}

void loop()
{
 double temp = map(analogRead(PIN_SENSOR), 0, 1023, 25, 125);  // Mapear o valor lido para uma faixa de temperatura

  input = temp;

  double error = setpoint - input;  // Calcular o erro

  myPID.Compute();  // Calcular o valor de controle do PID

  analogWrite(PIN_PWM, output);  // Enviar o valor do PWM para o sistema
  Serial.print(setpoint);
  Serial.print(",");
  Serial.print(input);
  Serial.print(",");
  Serial.print(output);
  Serial.println();


  delay(100);  // Tempo de amostragem

}
