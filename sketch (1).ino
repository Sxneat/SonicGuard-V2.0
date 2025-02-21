#include <NewPing.h>

// กำหนดโน้ตเสียง (ค่าความถี่ใน Hz)
//#define NOTE_C4  262 // C4
//#define NOTE_D4  294 // D4
//#define NOTE_E4  330 // E4
//#define NOTE_F4  349 // F4
//#define NOTE_G4  392 // G4
//#define NOTE_A4  440 // A4
//#define NOTE_B4  494 // B4

//เสียงแจ้งเตือนแบบเรียบง่าย (Simple Alert)
//#define NOTE_C5  523 // C5

//เสียงแจ้งเตือนแบบไต่ระดับ (Ascending Alert)
//#define NOTE_C5  523 // C5
//#define NOTE_D5  587 // D5
//#define NOTE_E5  659 // E5

//เสียงแจ้งเตือนแบบฉุกเฉิน (Urgent Alert)
//#define NOTE_C6  1047 // C6

//เสียงไซเรนของรถพยาบาล
//#define NOTE_A4  440 // A4
//#define NOTE_D5  587 // D5

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
    if(distance1 > 50 && distance1 <= 800)
    {
      digitalWrite(LED_1, LOW);  // LED ON
      digitalWrite(buzzerPin1, HIGH); 
      //digitalWrite(buzzerPin1, HIGH); 
      Serial.println("                                         playTone1"); 
    }
    else 
    {
      digitalWrite(LED_1, HIGH);  //  LED OFF
      digitalWrite(buzzerPin1, LOW); // หยุดเสียง sensor 1
    }
 
    if(distance2 > 50 && distance2 <= 800)
    {
      digitalWrite(LED_2, LOW);  // LED ON
      digitalWrite(buzzerPin1, HIGH); 
      //digitalWrite(buzzerPin2, HIGH); 
      Serial.println("                                                          playTone2");
    }
    else 
    {
      digitalWrite(LED_2, HIGH);  //  LED 
      digitalWrite(buzzerPin1, LOW); // หยุดเสียง sensor 1.
    }

    //digitalWrite(buzzerPin1, HIGH); 
  //} 
  //else 
  //{
    //digitalWrite(LED_1, HIGH);  //  LED OFF
    //digitalWrite(LED_2, HIGH);  //  LED OFF
    //digitalWrite(buzzerPin1, LOW); // หยุดเสียง sensor 1
  //}

  // การทำงานของ sensor 2
  /*if (distance2 > 10 && distance2 <= 100) // ระยะ 20 - 100 cm
  {
    //duration_distance2 = distance2; // กำหนดให้ความยาวเสียง แปลผันตรง กับ ระยะห่าง
    digitalWrite(LED_2, HIGH);  // LED ON
    digitalWrite(buzzerPin2, HIGH); 
    Serial.println("                                                          playTone2");
  } 
  else 
  {
    digitalWrite(LED_2, LOW);  // LED OFF
    digitalWrite(buzzerPin2, LOW);  // หยุดเสียง sensor 2
  }*/
}




