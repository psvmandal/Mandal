#define ENA 3
#define ENB 5
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 7

char read;

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  analogWrite(ENB, 80);
  analogWrite(ENA, 255);
}

void loop() {
  if (Serial.available() > 0) { 
    read = Serial.read(); 

    if (read == 'w' || read == 'W') {  
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      delay(100);
    }
    else if (read == 's' || read == 'S') {  
      digitalWrite(IN4, HIGH);
      digitalWrite(IN3, LOW);
      delay(100);
    }
    else if (read == 'a' || read == 'A') {  
      digitalWrite(IN1, HIGH);
      digitalWrite(IN3, LOW);
      /**digitalWrite(IN2, LOW);
      digitalWrite(IN1, LOW);*/
      delay(100);
    }
    else if (read == 'd' || read == 'D') {  
      digitalWrite(IN2, HIGH);
      digitalWrite(IN4, LOW);
      /**digitalWrite(IN3, LOW);
      digitalWrite(IN2, LOW);
      delay(100);*/
    }
    else if (read == 'f' || read == 'F') {  
      digitalWrite(IN1, LOW);
      digitalWrite(IN4, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN2, LOW);
    }
    
    delay(100);
  }
}