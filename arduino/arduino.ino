// https://forum.arduino.cc/t/serial-input-basics-updated/382007/3
// Example 5 - Receive with start- and end-markers combined with parsing

const int numChars = 1201;
char receivedChars[numChars];
// char tempChars[numChars];        // temporary array for use when parsing

boolean newData = false;

struct color {
    byte r;
    byte g;
    byte b;
};
color ledColorArray[100];
int ledColorArrayLength = sizeof(ledColorArray) / sizeof(ledColorArray[0]);


//============

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino ready");
  Serial.println();
}

//============

void loop() {
  recvWithStartEndMarkers();
  if (newData == true) {
    // strcpy(tempChars, receivedChars);
    // this temporary copy is necessary to protect the original data
    //   because strtok() used in parseData() replaces the commas with \0
    parseData();
    showParsedData();
    newData = false;
  }
}

//============

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static int ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

//============

void parseData() {      // split the data into its parts

  int arrIndex = 0;
  char *strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(receivedChars, ",");

   while (strtokIndx != NULL) {
      int r = atoi(strtokIndx);
      
      strtokIndx=strtok(NULL, ",");
      int g = atoi(strtokIndx);
      
      strtokIndx=strtok(NULL, "+");
      int b = atoi(strtokIndx);

      ledColorArray[arrIndex] = {r, g, b};
      
      strtokIndx=strtok(NULL, ",");
      arrIndex++;
   }
  
}

//============

void showParsedData() {
  Serial.println("Message: ");
  
  for (int i = 0; i < ledColorArrayLength; i++) {

    Serial.print(ledColorArray[i].r);
    Serial.print("-");
    Serial.print(ledColorArray[i].g);
    Serial.print("-");
    Serial.println(ledColorArray[i].b);
  }

}