const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

const byte fade[][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 255}}; //{R, G, B}

int length = sizeof(fade) / sizeof(fade[0]);

float i = 0;

void setup(){
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop(){
  float blending = fmod(fmod(i, length), 1);
  
  int color = fmod(i, length);
  int color2 = (color + 1) % length;
  
  analogWrite(RED_PIN, fade[color][0] + (fade[color2][0] - fade[color][0]) * blending);
  analogWrite(GREEN_PIN, fade[color][1] + (fade[color2][1] - fade[color][1]) * blending);
  analogWrite(BLUE_PIN, fade[color][2] + (fade[color2][2] - fade[color][2]) * blending);
  
  i += 0.0001;
}
