//void setup() {
//  // Set MIDI baud rate:
//  // 19200
//  Serial.begin(115200);
//}
//
//void loop() {
//  // play notes from F#-0 (0x1E / 30 in decimal) to F#-5 (0x5A / 90 in decimal):
//  for (int note = 0x1E; note < 0x5A; note++) {
//    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
//    noteOn(0x90, note, 0x45);
//    
//    //delay(100);
//    //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
//    noteOn(0x90, note, 0x00);
//    //delay(100);
//  }
//}
//

#include <NewPing.h>
#define TRIG_PIN    12          // trigger Pin
#define ECHO_PIN    11          // Echo Pin
//Octave 4 to 8 (60 - 119 inclusive)
#define MAX_DISTANCE 48        // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);    // 設定 NewPing 物件，並給與最遠測試距離

unsigned previousNote = 128;

void setup() {
  Serial.begin(115200);         // 開啟串列埠顯示 ping 的距離值
}

void loop() {
  delay(50);                        // 等待 50 毫秒，需大於前程式說明的 29 秒
  unsigned int uS = sonar.ping();   // 送出 ping，並取得微秒 microseconds(uS) 時間
  unsigned int currentNote = sonar.convert_cm(uS) + 60;
  if (currentNote != previousNote) {
    if (previousNote > -1 && previousNote < 128){
      // noteoff
      noteOn(0x80, previousNote, 0x00);
    }
    
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    noteOn(0x90, currentNote, 0x45);
  }

  previousNote = currentNote;
}

// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
