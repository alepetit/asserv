#include <Servo.h>                                  //includes the servo library

int pinEncodG = 2;
int pinEncodD = 3;

int pinMoteurG = 11; //moteur 1
int pinMoteurD = 9; //moteur 2
int pinSensG = 10;
int pinSensD = 6;

int pinMasse1 = A1;
int pinMasse2 = A0;

int nb_incrD = 0;
int nb_incrG = 0;

int nb_incrDp = 0;
int nb_incrGp = 0;

int vitesseD = 0;
int vitesseG = 0;
int diffG = 0;
int diffD = 0;

int consigneD = 200;
int consigneG = 200;
int commandeD[] = {0, 0, 0};
int commandeG[] = {0, 0, 0};
int diffvD[3];
int diffvG[3];

float retard = 0.01;

void encodeurD(){
  nb_incrD += 1; 
  //Serial.println(nb_incrD); 
  }

void encodeurG(){
  nb_incrG += 1;  
  //Serial.println(nb_incrG);
  }
  
void setup()
{
    Serial.begin(9600);
    Serial.println("Hello World");
    attachInterrupt(digitalPinToInterrupt(pinEncodG), encodeurG, RISING);
    attachInterrupt(digitalPinToInterrupt(pinEncodD), encodeurD, RISING);
    pinMode(pinMasse1, OUTPUT);
    pinMode(pinMasse2, OUTPUT);
    analogWrite(pinMasse1, 0);
    analogWrite(pinMasse2, 0);
    pinMode(pinSensG, OUTPUT);
    pinMode(pinSensD, OUTPUT);
    analogWrite(pinSensG, 0);
    analogWrite(pinSensD, 0);

    pinMode(pinMoteurG, OUTPUT);
    pinMode(pinMoteurD, OUTPUT);

}


 
void loop()
{
      diffG = nb_incrG - nb_incrGp;
      diffD = nb_incrD - nb_incrDp;
      
      nb_incrDp = nb_incrD;
      nb_incrGp = nb_incrG;
      
      vitesseD = (diffD/(979.62*retard))*60;
      vitesseG = (diffG/(979.62*retard))*60;

      commandeD[0] = 1.949 *commandeD[1] - 0.949*commandeD[2] +0.01938*diffvD[1] -0.01857*diffvD[2];
      commandeG[0] = 1.949 *commandeG[1] - 0.949*commandeG[2] +0.01938*diffvG[1] -0.01857*diffvG[2];

      Serial.println(vitesseD);
      
      analogWrite(pinMoteurG, commandeG[0]);
      analogWrite(pinMoteurD, commandeD[0]);

      diffvD[0] = consigneD - vitesseD;
      diffvG[0] = consigneG - vitesseG;
      
      diffvD[2] = diffvD[1];
      diffvD[1] = diffvD[0];

      diffvG[2] = diffvG[1];
      diffvG[1] = diffvG[0];

      commandeD[2] = commandeD[1];
      commandeD[1] = commandeD[0];
      
      commandeG[2] = commandeG[1];
      commandeG[1] = commandeG[0];
      
      Serial.println(vitesseD);
      
      delay(retard*1000);
      
     
      
      
      
      /*
      analogWrite(pinMoteurG, 0);
      digitalWrite(pinMasse4, 0);
      analogWrite(pinMoteurD, 0);
      digitalWrite(pinMasse3, 0);
      delay(3000);
      analogWrite(pinMoteurG, 0);
      digitalWrite(pinMasse4, 1);
      analogWrite(pinMoteurD, 0);
      digitalWrite(pinMasse3, 1);
      delay(500);
      analogWrite(pinMoteurG, 0);
      digitalWrite(pinMasse4, 1);
      analogWrite(pinMoteurD, 150);
      digitalWrite(pinMasse3, 0);
      delay(3000);
      analogWrite(pinMoteurG, 0);
      digitalWrite(pinMasse4, 0);
      analogWrite(pinMoteurD, 0);
      digitalWrite(pinMasse3, 0);
      delay(5000);
      analogWrite(pinMoteurG, 0);
      analogWrite(pinMoteurD, 150);
      delay(500);
      analogWrite(pinMoteurG, 0);
      analogWrite(pinMoteurD, 0);
      delay(5000);*/
      
}

