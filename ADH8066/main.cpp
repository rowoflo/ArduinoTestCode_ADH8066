/*
 -------------------------------------------------------------------------------
 main.cpp
 ADH8066 Project
 
 *** DESCRIPTION ***
 
 Initially created by Rowland O'Flaherty (rowlandoflaherty.com) on 1/20/13.
 
 Version 1.0
 -------------------------------------------------------------------------------
 */

//------------------------------------------------------------------------------
// Includes and Defines
//------------------------------------------------------------------------------
#include <Arduino.h>
#include <ADH8066.h>


//------------------------------------------------------------------------------
// Helper Function Declarations
//------------------------------------------------------------------------------
void printMenu();
void parseStr(const String &str);

//------------------------------------------------------------------------------
// Global Varible Declarations
//------------------------------------------------------------------------------
ADH8066 cell(6,7,8,57600);
String incomingStr = "";

String phoneNumStr = "4049198174";
String textMsgStr = "Hello from cell library";
String websiteStr = "www.cc.gatech.edu";

//------------------------------------------------------------------------------
// Setup Function - Initializes Arduino
//------------------------------------------------------------------------------
void setup() {
    cell.initialize();
    
	Serial.begin(9600);
    Serial.println("======== ADH8066 Test Program ========");
    printMenu();
}

//------------------------------------------------------------------------------
// Loop Function - Arduino Program Loop
//------------------------------------------------------------------------------
void loop() {
    char incomingChar;
    
    //If a character comes in from the cellular module...
//    while(cell.available() > 0) {
//        incomingChar = cell.read();    //Get the character from the cellular serial port.
//        Serial.print(incomingChar);  //Print the incoming character to the terminal.
//    }
    //cell.printStream();
    
    // If a character is coming from the terminal to the Arduino...
    while(Serial.available() > 0) {
        incomingChar = Serial.read();  //Get the character coming from the terminal
        incomingStr += incomingChar;
        if (incomingStr[incomingStr.length()-2] == '\r' && incomingStr[incomingStr.length()-1] == '\n') {
            parseStr(incomingStr.substring(0,incomingStr.length()-2));
            incomingStr = "";
        }
    }
}

//------------------------------------------------------------------------------
// Helper Functions
//------------------------------------------------------------------------------
void printMenu() {
    Serial.println("----- Command Menu -----");
//    Serial.println("menu    -- Print menu");
//    Serial.println("isOn    -- Check if cell is on");
//    Serial.println("toggle  -- Turn cell on or off");
//    Serial.println("turnOn  -- Turn cell on");
//    Serial.println("turnOff -- Turn cell off");
//    Serial.println("at...   -- Send AT command");
    Serial.println("check   -- Check sim card and signal");
    Serial.println("sim     -- Get sim card status");
    Serial.println("signal  -- Get signal strength");
    Serial.println("time    -- Get current date and time");
    Serial.print(  "text    -- Send text message (Num: "); Serial.print(phoneNumStr); Serial.print(") (Text: \""); Serial.print(textMsgStr); Serial.println("\")");
    Serial.print(  "call    -- Make phone call (Num: "); Serial.print(phoneNumStr); Serial.println(")");
//    Serial.print(  "website  -- Get website (Site: "); Serial.print(websiteStr); Serial.println(")");
    Serial.println("print   -- Print buffer");
    Serial.println("clear   -- Clear buffer");
//    Serial.println("closeWeb -- Close website port");
//    Serial.println("auth     -- Authenticate with server");
//    Serial.println("post     -- Do post");
    Serial.println();
}

void parseStr(const String &str) {
    if (str == String("menu")) {
        printMenu();
    } else if (str == String("isOn")) {
        if (cell.isOn()) {
            Serial.println("Cell is on");
        } else {
            Serial.println("Cell is off");
        }
    } else if (str == String("toggle")) {
        cell.toggleOnOff();
        if (cell.isOn()) {
            Serial.println("Cell is now on");
        } else {
            Serial.println("Cell is now off");
        }
    } else if (str == String("turnOn")) {
        cell.turnOn();
        Serial.println("Cell is now on");
    } else if (str == String("turnOff")) {
        cell.turnOff();
        Serial.println("Cell is now off");
    } else if (str.substring(0,2) == String("at")) {
        cell.cellCmd(str);
        delay(1000);
        Serial.println(cell.buffer());
    } else if (str == String("check")) {
        Serial.println("Checking...");
        if (cell.check()) {
            Serial.println("Check passed");
        } else {
            Serial.println("Checked failed");
        }
    } else if (str == String("sim")) {
        if (cell.sim()) {
            Serial.println("Sim is ready");
        } else {
            Serial.println("Sim in not ready");
        }
    } else if (str == String("signal")) {
        Serial.print("Signal quality: ");
        Serial.println(cell.signalQuality());
    } else if (str == String("time")) {
        cell.updateTime();
        Serial.println(cell.getTime());
        textMsgStr = String("Time: ") + cell.getTime();
    } else if (str == String("text")) {
        Serial.println(cell.sendText(phoneNumStr, textMsgStr));
    } else if (str == String("call")) {
        Serial.println(cell.makeCall(phoneNumStr));
    } else if (str == String("website")) {
//        cell.getWebsite(websiteStr);
    } else if (str == String("print")) {
        Serial.println(cell.buffer());
    } else if (str == String("clear")) {
        cell.clearBuffer();
    } else if (str == String("closeWeb")) {
//        closeWeb();
    } else if (str == String("auth")) {
//        authenticate();
    } else if (str == String("post")) {
//        postAlert();
    } else {
        Serial.print("Unknown command: ");
        Serial.println(str);
        Serial.println("Valid commands:");
        printMenu();
    }
    Serial.println();
}

//#if DEBUG
//if (c == '\0') {
//    Serial.print("\\0");
//} else if (c == '\r') {
//    Serial.print("\\r");
//} else if (c == '\n') {
//    Serial.print("\\n");
//} else if (c == 26) {
//    Serial.println("\\u");
//} else {
//    Serial.print(c);
//}
//#endif
