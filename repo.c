#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


int ir_read1 =12;
int ir_read2 =5;
int ir_read3 =18;
int led00,led01,led10,led11;


bool seat[4][4] = {
  {(led00), (led01), 0, 0},
  {(led10), (led11), 1, 0},
  {0, 0, 0, 1},
  {1, 1, 0, 0}
};

void drawSeatingMatrix() {
  display.clearDisplay();

  int seatWidth = 25;
  int seatHeight = 15;
  int x0 = 5;
  int y0 = 5;

  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      int x = x0 + c * seatWidth;
      int y = y0 + r * seatHeight;
      
      if (seat[r][c]) {
        // Occupied → filled rectangle
        display.fillRect(x, y, seatWidth - 3, seatHeight - 3, SSD1306_WHITE);
      } else {
        // Empty → outline only
        display.drawRect(x, y, seatWidth - 3, seatHeight - 3, SSD1306_WHITE);
      }

      // Label each seat (optional)
      display.setTextSize(1);
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.setCursor(x + 5, y + 3);
      display.print((char)('A' + r));
      display.print(c + 1);
    }
  }

  display.display();
}

void setup() {
  // put your setup code here, to run once:
  //  pinMode(ir_read, INPUT);pinMode(led, OUTPUT);
  *(int*)(0x3FF4903C)=(*(int*)(0x3FF4903C))|(0x00000200);  //set gpio 15 input-enable=1
  *(int*)(0x3FF44020)=((*(int*)(0x3FF44020))&(0xFFFF7FFF))| (0x00000004);  //output enable=0 for gpio15, output enable=1 for gpio2
  *(int*)(0x3FF49040)=(*(int*)(0x3FF49040))&(0xFFFFFDFF);  ////set gpio 2 input-enable=0
  *(int*)(0x3FF44538)=((*(int*)(0x3FF44538))&(0xFFFFF000)) | (0x00000100); //configuring o/p using gpio_funcx_out_sel_cfg_reg
  pinMode(ir_read1, INPUT);
  pinMode(ir_read2, INPUT);
  pinMode(ir_read3, INPUT);
  
  
  Serial.begin(9600);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
 display.display();

}

void loop() {
  
  //int IR_value= digitalRead(ir_read);
  if (((*(int*)(0x3FF4403C))& 0x00008000)==0) {   //0x3FF4403C=gpio_in_reg ~register that reads input
    //digitalWrite(2, HIGH);
    *(int*)(0x3FF44004)= (*(int*)(0x3FF44004)|(0x00000004));   //0x3FF44004=gpio_out_reg ~register that writes output
    //*(int*)(0x3FF44008)= (*(int*)(0x3FF44008)|(0x00000004));    //set register- output
    led11= 1;
  }
  else {
    //digitalWrite(2, LOW);
    //*(int*)(0x3FF4400C)= (*(int*)(0x3FF4400C)|(0x00000004));    //&(0xFFFFFFFB));    //reset register- output
    *(int*)(0x3FF44004)= (*(int*)(0x3FF44004)&(0xFFFFFFFB));
    led11= 0;
  }
  led00=!digitalRead(ir_read1);
  led01=!digitalRead(ir_read2);
  led10=!digitalRead(ir_read3);
  seat[0][0]=led00;
  seat[0][1]=led01;
  seat[1][0]=led10;
  seat[1][1]=led11;

  drawSeatingMatrix();
  
  // Serial.println(seat[0][0]);
  // delay(1000); // Wait for 1 second

}
