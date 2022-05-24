#include<Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include<Servo.h>


int getFingerprintIDez();

//pin 2 for TX
//pin 3 for RX
int ledv=6;//led verte
int ledr=8;//led rouge
int buz=10;//alarme
int photoled=0;// la photo resistance
int val;

Servo myservo;
SoftwareSerial myserial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&myserial);

void setup() {
          // put your setup code here, to run once:
          Serial.begin(9600);
          Serial.println("fingertest");
          pinMode(ledv, OUTPUT);
          pinMode(ledr, OUTPUT);
          pinMode(buz, OUTPUT);
          pinMode(photoled, INPUT);
          myservo.attach(7);
          // set the data rate for the sensor serial port
          finger.begin(57600);
          if(finger.verifyPassword())
          { 
              Serial.println("Capteur d'empreintes trouvé");
          }else{ 
              Serial.println("Capteur d'ampeintes non trouvé :( " );
          while(1);
          }
          Serial.println("En attente d'une empreinte valide:)");
          myservo.write(180);
}


void loop() {
        // put your main code here, to run repeatedly:
        val=analogRead(photoled);
        getFingerprintIDez();
        delay(50); //petit délai
        digitalWrite(ledr, HIGH);
        if(val<50){ 
            digitalWrite(buz, HIGH);delay(500);
            digitalWrite(buz, HIGH); }
        }
        
        // cette fonction retourne -1 si l'empreinte n'est pas valide et et retourne l'ID sinon
        int getFingerprintIDez()
        {
                  uint8_t p=finger.getImage(); // on
                  enregistre l'image de l'empreinte
                  if (p!=FINGERPRINT_OK) {
                       return -1;
                  }// on sort si l'image ne correspond a aucune enregistré
                  p=finger.image2Tz();
                  if(p!=FINGERPRINT_OK) {
                       return -1;
                  }
                  p=finger.fingerFastSearch(); // on recherche l'empreintes parmi celles enregistrées
                  if(p!=FINGERPRINT_OK) {
                        return -1;
                  }// on sors si l'empreintes n'est pas trouvée
                    //a ce nivaeu l'empreinte est reconnu
                  for(int i=180;i>=0;i-=1)
                  { 
                            myservo.write(i);
                            delay(15);
                  }
                  digitalWrite(ledv,HIGH);
                  digitalWrite(ledr,LOW);
                  myservo.write(0);
                  delay(5000);
                  for(int i=0;i<=180;i+=1)
                  { 
                            myservo.write(i);
                            delay(15);
                  }
                  delay(1000);
                  digitalWrite(ledv,LOW);
                  digitalWrite(ledr,HIGH);
                  Serial.print("Identifiant trouvé");
                  Serial.print(finger.fingerID);
                  Serial.print(" avec une confiance de ");
                  Serial.print(finger.confidence);
                  return finger.fingerID;
}
