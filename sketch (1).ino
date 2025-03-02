#include <NewPing.h>

// Ultrasonic sensor 1
#define TRIGGER_PIN1  6  // Pin trigger sensor 1
#define ECHO_PIN1     5  // Pin echo sensor 1

// Ultrasonic sensor 2
#define TRIGGER_PIN2  8  // Pin trigger sensor 2
#define ECHO_PIN2     7  // Pin echo sensor 2

#define MAX_DISTANCE1 500 // Maximum distance we want to ping for (in centimeters)
#define MAX_DISTANCE2 500 // Maximum distance we want to ping for (in centimeters)

// กำหนดพินสำหรับการใช้งานเสียง
const int buzzerPin1 = 9;  // พินสำหรับเสียง sensor 1
//const int buzzerPin2 = 10;  // พินสำหรับเสียง sensor 2

unsigned int distance1;  // ตัวแปรสำหรับเก็บค่าระยะ sensor 1
unsigned int distance2;  // ตัวแปรสำหรับเก็บค่าระยะ sensor 2

int LED_1 = 3;  //LED 1 status
int LED_2 = 4;  //LED 2 status

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE1); // Sensor 1 setup
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE2); // Sensor 2 setup

float previousDistance1 = 0; // ระยะทางก่อนหน้า (เมตร)
float previousTime1 = 0;     // เวลาก่อนหน้า (วินาที)
float currentDistance1 = 0;  // ระยะทางปัจจุบัน (เมตร)
float currentTime1 = 0;      // เวลาปัจจุบัน (วินาที)
float velocity1 = 0;         // ความเร็ว (เมตร/วินาที)
//float acceleration1 = 0;     // อัตราเร่ง (เมตร/วินาที^2)

float previousDistance2 = 0; // ระยะทางก่อนหน้า (เมตร)
float previousTime2 = 0;     // เวลาก่อนหน้า (วินาที)
float currentDistance2 = 0;  // ระยะทางปัจจุบัน (เมตร)
float currentTime2 = 0;      // เวลาปัจจุบัน (วินาที)
float velocity2 = 0;         // ความเร็ว (เมตร/วินาที)
//float acceleration2 = 0;     // อัตราเร่ง (เมตร/วินาที^2)

void setup() 
{
  Serial.begin(9600); 
  pinMode(buzzerPin1, OUTPUT); // กำหนดพิน output สำหรับเสียง sensor 1
  //pinMode(buzzerPin2, OUTPUT); // กำหนดพิน output สำหรับเสียง sensor 2

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
}

void loop() 
{
  // วัดระยะทาง
  float distance1 = sonar1.ping_cm();  // ระยะทางปัจจุบัน (เมตร)
  //float distance = measureDistance(); // ระยะทางปัจจุบัน (เมตร)
  float timeNow1 = millis() / 1000.0;  // เวลาในหน่วยวินาที
  
  // คำนวณความเร็ว (v = Δd / Δt)
  float deltaDistance1 = distance1 - previousDistance1;
  float deltaTime1 = timeNow1 - previousTime1;
  if (deltaTime1 > 0) 
  {
    velocity1 = deltaDistance1 / deltaTime1;
  }

  // แสดงข้อมูล
  Serial.print("Distance1: "); // ระยะทางปัจจุบัน (เมตร)
  Serial.print(distance1);
  Serial.print(" cm, Velocity1: "); // ความเร็ว (เมตร/วินาที)
  Serial.print(velocity1);
  Serial.print(" m/s");
  Serial.print("        Acceleration: "); // อัตราเร่ง (เมตร/วินาที^2)
  Serial.print(acceleration);
  Serial.print(" m/s^2");

  // อัปเดตค่าก่อนหน้า
  previousDistance1 = distance1;  //ระยะทางก่อนหน้า = distance
  previousTime1 = timeNow1;       // เวลาก่อนหน้า = timeNow

  //----------------------------------------------------

  // วัดระยะทาง
  float distance2 = sonar2.ping_cm();  // ระยะทางปัจจุบัน (เมตร)
  //float distance2 = measureDistance2(); // ระยะทางปัจจุบัน (เมตร)
  float timeNow2 = millis() / 1000.0;  // เวลาในหน่วยวินาที
  
  // คำนวณความเร็ว (v = Δd / Δt)
  float deltaDistance2 = distance2 - previousDistance2;
  float deltaTime2 = timeNow2 - previousTime2;
  if (deltaTime2 > 0) 
  {
    velocity2 = deltaDistance2 / deltaTime2;
  }

  // คำนวณอัตราเร่ง (a = Δv / Δt)
  /*float deltaVelocity = velocity - (deltaDistance / deltaTime);
  if (deltaTime > 0) 
  {
    acceleration = deltaVelocity / deltaTime;
  }*/

  // แสดงข้อมูล
  Serial.print("Distance2: "); // ระยะทางปัจจุบัน (เมตร)
  Serial.print(distance2);
  Serial.print(" cm, Velocity2: "); // ความเร็ว (เมตร/วินาที)
  Serial.print(velocity2);
   Serial.print(" m/s");
  //Serial.print("        Acceleration2: "); // อัตราเร่ง (เมตร/วินาที^2)
  //Serial.print(acceleration2);
  //Serial.print(" m/s^2");


  // อัปเดตค่าก่อนหน้า
  previousDistance2 = distance2;  //ระยะทางก่อนหน้า = distance
  previousTime2 = timeNow2;       // เวลาก่อนหน้า = timeNow

  //----------------------------------------------------

  delay(10);  // Wait 10ms between pings

  // อ่านค่าระยะจาก sensor 1
  distance1 = sonar1.ping_cm(); 
  Serial.print("Sensor 1: ");
  Serial.print(distance1);
  Serial.print(" cm");

  // อ่านค่าระยะจาก sensor 2
  distance2 = sonar2.ping_cm();
  Serial.print("  |  Sensor 2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  // การทำงานของ sensor 1 
    if(distance1 > 10 && distance1 <= 100)
    {
      digitalWrite(LED_1, LOW);  // LED ON
      digitalWrite(buzzerPin1, HIGH); 
      //digitalWrite(buzzerPin1, HIGH); 
      Serial.println("                                                                                                                                playTone1"); 
    }
    else 
    {
      digitalWrite(LED_1, HIGH);  //  LED OFF
      digitalWrite(buzzerPin1, LOW); // หยุดเสียง sensor 1
    }
 
    if(distance2 > 10 && distance2 <= 100)
    {
      digitalWrite(LED_2, LOW);  // LED ON
      digitalWrite(buzzerPin1, HIGH); 
      //digitalWrite(buzzerPin2, HIGH); 
      Serial.println("                                                                                                                                                                playTone2"); 
    }
    else 
    {
      digitalWrite(LED_2, HIGH);  //  LED 
      digitalWrite(buzzerPin1, LOW); // หยุดเสียง sensor 1.
    }


}




