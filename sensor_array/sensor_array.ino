int WAITING = 0;
int EXECUTING = 1;
int state = WAITING;
int vol[5][6];

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  
  Serial.begin(115200);
  Serial.setTimeout(10);
}

void loop() {
  if (state == WAITING) {
    String serin = Serial.readString();
    if (serin == "go\n") {
      state = EXECUTING;
    }
  
  } else if (state == EXECUTING) {
    for (int col = 0; col <= 5; col++) {
      digitalWrite(col + 8, HIGH);
      for (int row = 0; row <= 4; row++) {
        int vol = analogRead(A0 + row);
        Serial.print(vol);
        Serial.print(" ");
      }
      digitalWrite(col + 8, LOW);
      Serial.println();
    }
    Serial.println();
    state = WAITING;
    delay(100);
  }
}
