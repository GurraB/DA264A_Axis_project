//
// @Author Gustaf Bohlin, Anton Hellbe
//

#ifndef ESPRESSO2_UNITTEST_H
#define ESPRESSO2_UNITTEST_H

void testBegin(String mess);

void testEnd();

void assertEqual(int a, int b, String mess);

void assertNotEqual(int a, int b, String mess);

void assertBitHigh(int a, int bit, String mess);

void assertBitLow(int a, int bit, String mess);

void assertBits(int a, int b, int mask, String mess);

void assertTrue(int data, String mess);

void assertFalse(int data, String mess);

#endif //ESPRESSO2_UNITTEST_H
