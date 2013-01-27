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
ADH8066 cell;
String incomingStr = "";

String phoneNumStr = "4049198174";
String textMsgStr = "Hello from cell library";

//------------------------------------------------------------------------------
// Setup Function - Initializes Arduino
//------------------------------------------------------------------------------
void setup() {
	Serial.begin(9600);
    Serial.println("======== ADH8066 Test Program ========");
    printMenu();
}

//------------------------------------------------------------------------------
// Loop Function - Arduino Program Loop
//------------------------------------------------------------------------------
void loop() {
    char incomingChar;
    
//    //If a character comes in from the cellular module...
//    while(cell.available() > 0) {
//        incomingChar = cell.read();    //Get the character from the cellular serial port.
//        Serial.print(incomingChar);  //Print the incoming character to the terminal.
//    }
    
    //If a character is coming from the terminal to the Arduino...
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
    Serial.println("at...    -- Send AT command");
    Serial.println("menu     -- Print menu");
//    Serial.println("dbToggle -- Toggle debug mode");
//    Serial.println("echoOn   -- Turn on echo");
//    Serial.println("echoOff  -- Turn off echo");
    Serial.println("check    -- Check sim card and signal");
    Serial.println("time     -- Get current date and time");
    Serial.print(  "text     -- Send text message (Num: "); Serial.print(phoneNumStr); Serial.print(") (Text: \""); Serial.print(textMsgStr); Serial.println("\")");
    Serial.print(  "call     -- Make phone call (Num: "); Serial.print(phoneNumStr); Serial.println(")");
//    Serial.print(  "website  -- Get website (Site: "); Serial.print(websiteStr); Serial.println(")");
//    Serial.println("closeWeb -- Close website port");
//    Serial.println("auth     -- Authenticate with server");
//    Serial.println("post     -- Do post");
    Serial.println();
}

void parseStr(const String &str) {
    if (str.substring(0,2) == String("at")) {
//        cellCmd(str);
    } else if (str == String("menu")) {
        printMenu();
    } else if (str == String("dbToggle")) {
//        if (debugFlag) {
//            debugFlag = false;
//        } else {
//            debugFlag = true;
//        }
//        Serial.println(debugFlag);
        
    } else if (str == String("echoOn")) {
//        echoOn();
    } else if (str == String("echoOff")) {
//        echoOff();
    } else if (str == String("check")) {
        cell.check();
    } else if (str == String("time")) {
        cell.getTime();
    } else if (str == String("text")) {
        cell.sendText(phoneNumStr, textMsgStr);
    } else if (str == String("call")) {
        cell.makeCall(phoneNumStr);
    } else if (str == String("website")) {
//        getWebsite();
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
