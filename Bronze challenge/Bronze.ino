int left, right,count=0;
const int trigPin=13;
const int echoPin=12;
float duration, distance;
long st=millis();
unsigned long d;
int gantryCounter=0;
void setup() {
Serial.begin(9600);
pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);
pinMode(4,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
}
void ultra()
{
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  distance=(duration*0.0343)/2;
  Serial.print("distance:");
  Serial.println(distance);
  if(distance<20 && distance>0)
  {
    stop1();
    delay(100);
  }
}
void gantry()
{
  if (digitalRead(4)==HIGH)
{
int StartTime = millis();
d = pulseIn(4,HIGH);
 if(d > 500 and d < 1500)
            {
                //Serial.println(d); 
                Serial.println("Gantry: 1");
                stop1();
                delay(1000);
                forward();
            }
        if (d> 1500 and d < 2500)
            {
              //  Serial.println(d); 
                  Serial.println("Gantry: 2");
                  stop1();
                  delay(1000);
                  forward();
            }
        if (d > 2500 and d < 3500)
            {
               // Serial.println(d); 
                Serial.println("Gantry: 3");
                gantryCounter=gantryCounter+1;
                Serial.print("The gantry Counter is: ");
                Serial.println(gantryCounter);
                stop1();
                delay(1000);
                forward();
            }
         else {
             //Serial.println(d); 
             Serial.println("Gantry: Unknown");   
         }
}
}

void IR()
{
  left = digitalRead(A0);
  right = digitalRead(A1);
  
  if(left == 1 && right == 0){
  right1();
}
else if(left == 0 && right == 1){
  left1();
}
else if(left == 1 && right == 1){
  forward();
}
else if(left == 0 && right == 0){

  long endt=millis();
  if(endt-st > 500)
  {
    count++;
    Serial.print("Count = ");
    Serial.println(count);
    st= millis();
  }
  if( count==1)
  forward();
  else if (count==2)
  left1();
  else if(count==3)
  forward();
  else if(count==4)
  left1();
  else if(count==5)
  right1();
  else if(count==6)
  {
    stop1();
    delay(10000);
  }
}
}


void forward()
{
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
}
void right1()
{
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
}
void left1()
{
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
}
void stop1()
{
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  delay(1000);
}

int flag=0;
void loop(){
if(Serial.read()=='X' || flag==1)
{
  flag=1;
  gantry();
  IR();  
}
 ultra();
}
