
//
// @Author Gustaf, Anton
//

#include <Arduino.h>
int passed;
int failed;

void testBegin(String mess) {
    Serial.println("------------BEGIN TESTS-------------");
    Serial.println("Testing " + mess);
    Serial.println("\n");
    delay(1000);
    passed = 0;
    failed = 0;
}

void testEnd() {
    Serial.println("------------TESTS DONE-------------");
    Serial.println("PASSED: ");
    Serial.println(passed);
    Serial.println("FAILED: ");
    Serial.println(failed);
    Serial.println("-----------------------------------");
}

void assertEqual(int expected, int actual, String mess) {
    if(expected == actual) {
        Serial.println(mess + " PASSED");
        passed++;
    }
    else {
        Serial.println(mess + " FAILED");
        Serial.println("Expected: ");
        Serial.println(expected);
        Serial.println("Was: ");
        Serial.println(actual);

        failed++;
    }
}

void assertNotEqual(int expected, int actual, String mess) {
    if(expected != actual) {
        Serial.println(mess + " PASSED");
        passed++;
    }
    else {
        Serial.println(mess + " FAILED");
        Serial.println("Expected: ");
        Serial.println(expected);
        Serial.println("Was: ");
        Serial.println(actual);
        failed++;
    }
}

void assertBitHigh(int data, int bit, String mess) {
    if (data & (1 << (bit))) {
        Serial.println(mess + " PASSED");
        passed++;
    }
    else {
        Serial.println(mess + " FAILED");
        failed++;
    }
}

void assertBitLow(int data, int bit, String mess) {
    if(!(data & (1 << (bit)))) {
        Serial.println(mess + " PASSED");
        passed++;
    }
    else {
        Serial.println(mess + " FAILED");
        failed++;
    }
}

void assertBits(int expected, int actual, int mask, String mess) {
    if ((actual & mask) == (expected & mask)) {
        Serial.println(mess + " PASSED");
        passed++;
    }
    else {
        Serial.println(mess + " FAILED");
        Serial.println("Expected: ");
        Serial.println((expected & mask));
        Serial.println("Was: ");
        Serial.println((actual & mask));
        failed++;
    }
}

void assertTrue(int data, String mess) {
    if (data) {
        Serial.println(mess + " PASSED");
        passed++;
    }
    else {
        Serial.println(mess + " FAILED");
        failed++;
    }
}

void assertFalse(int data, String mess) {
    if (!data) {
        Serial.println(mess + " PASSED");
        passed++;
    }
    else {
        Serial.println(mess + " FAILED");
        failed++;
    }
}