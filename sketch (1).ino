#include <NewPing.h>

// Ultrasonic sensor 1
#define TRIGGER_PIN1  6  // Pin trigger sensor 1
#define ECHO_PIN1     5  // Pin echo sensor 1

// Ultrasonic sensor 2
#define TRIGGER_PIN2  8  // Pin trigger sensor 2
#define ECHO_PIN2     7  // Pin echo sensor 2

#define MAX_DISTANCE1 800 // Maximum distance we want to ping for (in centimeters)
#define MAX_DISTANCE2 800 // Maximum distance we want to ping for (in centimeters)

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

float previousDistance2 = 0; // ระยะทางก่อนหน้า (เมตร)
float previousTime2 = 0;     // เวลาก่อนหน้า (วินาที)
float currentDistance2 = 0;  // ระยะทางปัจจุบัน (เมตร)
float currentTime2 = 0;      // เวลาปัจจุบัน (วินาที)
float velocity2 = 0;         // ความเร็ว (เมตร/วินาที)

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

  // คำนวณอัตราเร่ง (a = Δv / Δt)
  /*float deltaVelocity1 = velocity1 - (deltaDistance1 / deltaTime1);
  if (deltaTime1 > 0) 
  {
    acceleration1 = deltaVelocity1 / deltaTime1;
  }*/

  // แสดงข้อมูล
  Serial.print("Distance1: "); // ระยะทางปัจจุบัน (เมตร)
  Serial.print(distance1);
  Serial.print(" cm, Velocity1: "); // ความเร็ว (เมตร/วินาที)
  Serial.print(velocity1);
   Serial.print(" m/s");

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
  //if (distance1 > 10 && distance1 <= 100 ||  distance2 > 10 && distance2 <= 100 ) // ระยะ 20 - 100 cm
  //{
    if(distance1 > 50 && distance1 <= 800  && velocity1 < -9 && velocity1 < 0   && velocity1 != 9.35 && velocity1 != -9.35 && velocity1 != 9.43 && velocity1 != -9.43  && velocity1 != -74.77  && velocity1 != -35.3 && velocity1 != -379.77  && velocity1 != -376.64  && velocity1 != -376.11  && velocity1 != -365.85  && velocity1 != -349.99  && velocity1 != -337.49  && velocity1 != -384.68  && velocity1 != -182.93  && velocity1 != -361.48 && velocity1 != -520  && velocity1 != -7.94  && velocity1 != -6.71  && velocity1 != -341.27  && velocity1 != -8.0  && velocity1 != -7.69  && velocity1 != -6.67  && velocity1 != -7.75  && velocity1 != -7.25)
    //if(distance1 > 50 && distance1 <= 800 )
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
 
    if(distance2 > 50 && distance2 <= 800 && velocity2 < -9  && velocity2 < 0  && velocity2 != 9.35 && velocity2 != -9.35 && velocity2 != 9.43 && velocity2 != -9.43  && velocity2 != -74.77  && velocity2 != -35.3 && velocity2 != -379.77  && velocity2 != -376.64  && velocity2 != -376.11  && velocity2 != -365.85  && velocity2 != -349.99  && velocity2 != -337.49  && velocity2 != -384.68  && velocity2 != -182.93  && velocity2 != -361.48  && velocity2 != -520  && velocity2 != -7.94  && velocity2 != -6.71  && velocity2 != -341.27  && velocity2 != -8.0  && velocity2 != -7.69  && velocity2 != -6.67  && velocity2 != -7.75  && velocity2 != -7.25)
    //if(distance2 > 50 && distance2 <= 800 )
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


