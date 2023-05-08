#define DEBUG 1

int tl;           //TopLeft
int tr;           //TopRight
int dl;           //DownLeft
int dr;           //DownRight
int _delay = 1;

void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
  //Clear OC1A/OC1B on compare match (set output to low level)
  TCCR1A = 0;
  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
  
  //Fast PWM, TOP to ICR1
  TCCR1B = 0;
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
  
  ICR1 = 40000;
  
  OCR1A = 3400; //Initial Horizontal Value
  OCR1B = 3100; //Initial Vertical Value

#if DEBUG
  Serial.begin(9600); //For debug only
#endif

}

#if DEBUG
void debugPrint()
{
  //Serial.print("tl: ");
  //Serial.println(tl);
  
  //Serial.print("tr: ");
  //Serial.println(tr);
  
  //Serial.print("dl: ");
  //Serial.println(dl);
  
  //Serial.print("dr: ");
  //Serial.println(dr);
}
#endif

void readData()
{
  tl = analogRead(A1);
  tr = analogRead(A2);
  dl = analogRead(A0);
  dr = analogRead(A3);

#if DEBUG
  debugPrint();
#endif
}

void adjustHorizontaly()
{
   if ((tl > tr) || (dl > dr)) {
    OCR1A = OCR1A - 1; //Rotate Right
    delay(_delay);
  }
  
  if ((tl < tr) || (dl < dr)) {
    OCR1A = OCR1A + 1; //Rotate Left
    delay(_delay);
  }
  
  if (OCR1A > 4000) {
    OCR1A = 4000; //Max Horizontal Value
  }
  
  if (OCR1A < 2000) {
    OCR1A = 2000; //Min Horizontal Value
  }
}

void adjustVerticaly()
{
  if ((tl > dl) || (tr > dr)) {
    OCR1B = OCR1B - 1; //Rotate Down
    delay(_delay);
  }
  
  if ((tl < dl) || (tr < dr)) {
    OCR1B = OCR1B + 1; //Rotate Up
    delay(_delay);
  }
  
  if (OCR1B > 4200) {
    OCR1B = 4200; //Max Vertical Value
  }
  
  if (OCR1B < 3000) {
    OCR1B = 3000; //Min Vertical Value
  }
}

void loop() {
  readData();

  adjustHorizontaly();
  adjustVerticaly();

}
