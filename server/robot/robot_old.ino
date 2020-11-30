#define  V1 4
#define  V2 7
#define  S1 5
#define  S2 6
#define  D_L A1
#define  D_R A3
#define  D_F A2
void control(int s1, int s2)
{
  s1 = constrain(s1,-255,255);
  s2 = constrain(s2,-255,255);
  digitalWrite(V1,s1 >= 0); analogWrite(S1,abs(s1));
  digitalWrite(V2,s2 >= 0); analogWrite(S2,abs(s2));
}
//градусы положительные если вращение по часовой стрелке, иначе отрицательные
//при скорости 75 и -75 за 450мс поворачивается на 90 градусов
//kof = delay/grad
void rotate(int grad)
{ 
  float kof;
  if (grad>90)
    kof = 7.5*2;
  else
    kof = 6.4*2;
  digitalWrite(V1, grad <= 0);
  digitalWrite(V2, grad >= 0);
  analogWrite(S1, 175);
  analogWrite(S2, 175);
  delay(abs(grad*kof));
  analogWrite(S1, 0);
  analogWrite(S2, 0);

}

void setup() 
{
 Serial.begin(9600);
 pinMode(V1, OUTPUT);
 pinMode(V2, OUTPUT);

}

bool auto_mode = false;

void loop() 
{
    Serial.println("Hello");
    if (Serial.available() > 0) {
      
      char command = Serial.read();
      int value = Serial.parseInt();
      Serial.println(command);
      switch(command){
      case 'r': 
        auto_mode = false;
        rotate(value);
        break;
      case 'f':
        auto_mode = false;
        control(175, 175);
        delay(value);
        control(0, 0);
        break;
      case 'b':
        auto_mode = false;
        control(-175, -175);
        delay(value);
        control(0, 0);
        break;
      case 'a':
        auto_mode = true;
        break;
      }
    }
    if (auto_mode) {

        int d_r = analogRead(D_R);
        int d_f = analogRead(D_F);
        int d_l = analogRead(D_L);
        if (d_f < 500)
        {
          control(-175,-175);
          delay(500);
          rotate(45);
        }
        else if (d_r < 500)
          rotate(-30);
        else if (d_l < 500)
          rotate(30);
        else
          control(100,100);        
    }
}
