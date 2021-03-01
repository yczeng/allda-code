#define vibe0 A0
#define vibe1 A1
#define vibe2 A2
#define vibe3 A3
#define vibe4 A4

#define VIBE_OFF 255
#define VIBE_MAX 0

#define WAITING 0
#define EXECUTING 1
int state;

void setup() {
  // put your setup code here, to run once:
  pinMode(vibe0, OUTPUT);
  pinMode(vibe1, OUTPUT);
  pinMode(vibe2, OUTPUT);
  pinMode(vibe3, OUTPUT);
  pinMode(vibe4, OUTPUT);

  analogWrite(vibe0, 255);
  analogWrite(vibe1, 255);
  analogWrite(vibe2, 255);
  analogWrite(vibe3, 255);
  analogWrite(vibe4, 255);

  Serial.begin(115200);
  Serial.setTimeout(10);
  state = WAITING;
}

void loop() {
  if (Serial.available()) {
    String instr = Serial.readString();

    // for controlling channel, pos
    // example input: V0##_V1##_V2##_V3##_V4##\n
    // (the underscores are spacers only)
    int vibe0_command = instr.substring(2, 4).toInt();
    int vibe1_command = instr.substring(7, 9).toInt();
    int vibe2_command = instr.substring(12, 14).toInt();
    int vibe3_command = instr.substring(17, 19).toInt();
    int vibe4_command = instr.substring(22, 24).toInt();

    setDuty(vibe0, vibe0_command);
    setDuty(vibe1, vibe1_command);
    setDuty(vibe2, vibe2_command);
    setDuty(vibe3, vibe3_command);
    setDuty(vibe4, vibe4_command);
  }
}

void setDuty(int vibe, int duty) {
  int rescaled = (99 - duty) * 255 / 99;
  analogWrite(vibe, rescaled);
}
