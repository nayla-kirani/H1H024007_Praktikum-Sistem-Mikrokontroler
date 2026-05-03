#include <Servo.h> // library untuk servo motor

Servo myservo; // ini membuat objek servo

//PIN SETUP 
const int potensioPin = A0;   // pin analog input
const int servoPin = 9;       // pin PWM untuk servo

//VARIABEL 
int pos = 0; // sudut servo (0–180)
int val = 0; // nilai ADC

void setup() {
  // Hubungkan servo ke pin
  myservo.attach(servoPin);

  // Aktifkan serial monitor
  Serial.begin(9600);
}

void loop() {
  // PEMBACAAN ADC 
  // Baca nilai potensiometer (0–1023 di Arduino Uno)
  val = analogRead(potensioPin);

  // KONVERSI DATA
  // Mapping ke sudut servo (0–180)
  pos = map(val, 0, 1023, 0, 180);

  // OUTPUT SERVO 
  myservo.write(pos);

  // MONITORING 
  Serial.print("ADC Potensio: ");
  Serial.print(val);
  Serial.print(" | Sudut Servo: ");
  Serial.println(pos);

  //STABILISASI
  delay(100); // cukup 100ms biar responsif
}
