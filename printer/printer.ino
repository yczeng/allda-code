
#define idle 0
#define driving 1

#define step1 7
#define dir1 2
#define step2 3
#define dir2 4
#define step3 5
#define dir3 6

int state = idle;

int chan1_step = 0;
int chan1_pos = 0;
int chan1_target = 0;
int chan1_dir = 0;

int chan2_step = 0;
int chan2_pos = 0;
int chan2_target = 0;
int chan2_dir = 0;

int chan3_step = 0;
int chan3_pos = 0;
int chan3_target = 0;
int chan3_dir = 0;

int delay_target = 10;

void endSignal(){
  Serial.println("$");
}

void setup() {
  pinMode(step1, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(step2, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(step3, OUTPUT);
  pinMode(dir3, OUTPUT);

  digitalWrite(dir1, 0);
  digitalWrite(step1, 0);
  digitalWrite(dir2, 0);
  digitalWrite(step2, 0);
  digitalWrite(dir3, 0);
  digitalWrite(step3, 0);
  
  Serial.begin(9600);
  
    
  String input = "";
  int count = 0;
  while (input[0] != '$') {
    if (count % 5 == 0) {
      Serial.println("");
      Serial.println("Send a '$' to begin communication.");
      Serial.print("Waiting for host");
    }
    Serial.print(".");
    Serial.print(input);
    input = Serial.readString();
    count++;
  }
  Serial.println("Found host.");
  Serial.println("++++++++++++++++++++++++");
  Serial.println("Allda Prototyping System");
  Serial.println("(c) 2021 Allda");
  Serial.println("Authors: Zachary Pitcher and Catherine Zeng");
  endSignal();
}

void loop() {
  if (state == idle) {
    String input = Serial.readStringUntil('$');
       
    // for controlling channel, pos
    // example input: C100050_C200050_C300050_D000 (the underscores are spacers only)
    if (input.substring(0, 1) == "C"){
      chan1_target = input.substring(2, 7).toInt();
      chan2_target = input.substring(9, 14).toInt();
      chan3_target = input.substring(16, 21).toInt();

      delay_target = input.substring(22, 25).toInt();
      
      if (chan1_target > chan1_pos) {
        chan1_dir = 0;
      } else { chan1_dir = 1; }
          
      if (chan2_target > chan2_pos) {
        chan2_dir = 0;
      } else { chan2_dir = 1; }
          
      if (chan3_target > chan3_pos) {
        chan3_dir = 0;
      } else { chan3_dir = 1; }

      state = driving;
      
      // Serial.print("chan1_pos: ");
      // Serial.print(chan1_pos);
      // Serial.print(", chan1_target: ");
      // Serial.print(chan1_target);
      // Serial.print(", chan1_dir: ");
      // Serial.println(chan1_dir);
      
      // Serial.print("chan2_pos: ");
      // Serial.print(chan2_pos);
      // Serial.print(", chan2_target: ");
      // Serial.print(chan2_target);
      // Serial.print(", chan2_dir: ");
      // Serial.println(chan2_dir);
      
      // Serial.print("chan3_pos: ");
      // Serial.print(chan3_pos);
      // Serial.print(", chan3_target: ");
      // Serial.print(chan3_target);
      // Serial.print(", chan3_dir: ");
      // Serial.println(chan3_dir);

      // Serial.print(chan);
    }

  } else if (state == driving) {

    // Drive Channel 1
    digitalWrite(dir1, chan1_dir);
    if (chan1_pos != chan1_target) {
      chan1_step = !chan1_step;
      digitalWrite(step1, chan1_step);
      if (chan1_dir) { chan1_pos--; }
      else { chan1_pos++; }
      
//      if (chan1_step) { Serial.print("^"); }
//      else { Serial.print("v"); }
    }
    
    // Drive Channel 2
    digitalWrite(dir2, chan2_dir);
    if (chan2_pos != chan2_target) {
      chan2_step = !chan2_step;
      digitalWrite(step2, chan2_step);
      if (chan2_dir) { chan2_pos--; }
      else { chan2_pos++; }
      
//      if (chan2_step) { Serial.print("^"); }
//      else { Serial.print("v"); }
    }
    
    // Drive Channel 3
    digitalWrite(dir3, chan3_dir);
    if (chan3_pos != chan3_target) {
      chan3_step = !chan3_step;
      digitalWrite(step3, chan3_step);
      if (chan3_dir) { chan3_pos--; }
      else { chan3_pos++; }

//      if (chan3_step) { Serial.print("^"); }
//      else { Serial.print("v"); }
    }


    if (chan1_pos == chan1_target && 
        chan2_pos == chan2_target && 
        chan3_pos == chan3_target) {
      state = idle;
//      Serial.println(" done");
      endSignal();
    }
    
    delayMicroseconds(delay_target);
  }
}
