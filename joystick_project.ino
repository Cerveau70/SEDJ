// Broches du joystick
const int joyX = A0;
const int joyY = A1;

// LEDs rouges (active en LOW = inverse)
int redLEDs[] = {3, 5, 6};
// LEDs vertes (active en LOW = inverse)
int greenLEDs[] = {9, 10, 11};

const int seuil = 100;

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(redLEDs[i], OUTPUT);
    pinMode(greenLEDs[i], OUTPUT);
    digitalWrite(redLEDs[i], HIGH);   // tout éteint au départ (inverse)
    digitalWrite(greenLEDs[i], HIGH);
  }
  Serial.begin(9600);
}

void loop() {
  int x = analogRead(joyX);
  int y = analogRead(joyY);
  int deltaX = x - 512;
  int deltaY = y - 512;

  // Par défaut, tout éteint
  eteindreToutes();

  // HAUT : allumer toutes les rouges
  if (deltaY > seuil && abs(deltaY) > abs(deltaX)) {
    allumerLEDs(redLEDs, 3);
  }
  // BAS : allumer toutes les vertes
  else if (deltaY < -seuil && abs(deltaY) > abs(deltaX)) {
    allumerLEDs(greenLEDs, 3);
  }
  // DROITE : allumer 2 LEDs de chaque
  else if (deltaX > seuil && abs(deltaX) > abs(deltaY)) {
    allumerLEDs(redLEDs, 2);
    allumerLEDs(greenLEDs, 2);
  }
  // GAUCHE : allumer 1 LED de chaque
  else if (deltaX < -seuil && abs(deltaX) > abs(deltaY)) {
    allumerLEDs(redLEDs, 1);
    allumerLEDs(greenLEDs, 1);
  }
  // CENTRE : tout reste éteint (déjà fait)
  
  delay(50);
}

// Allumer `n` LEDs dans un tableau (0 à 3)
void allumerLEDs(int leds[], int n) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(leds[i], (i < n) ? LOW : HIGH); // LOW = allumé (logique inversée)
  }
}

// Éteindre toutes les LEDs
void eteindreToutes() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(redLEDs[i], HIGH);
    digitalWrite(greenLEDs[i], HIGH);
  }
}
