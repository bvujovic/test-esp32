#include <unity.h>
// #include <stdio.h>

int SleepSeconds(int m, int s, int itv)
{
    if (itv % 60 != 0) // ako itv ne predstavlja tacan broj minuta, onda nema namestanja na pocetak minuta
        return itv;
    int x = itv / 60;                     // 300/60 = 5
    int nextMin = m / x * x + x;    // 56/5 * 5 + 5 = 11*5 + 5 = 55 + 5 = 60
    // printf("%d\n", nextMin);
    int min = nextMin - m;                // 60 - 56 = 4
    // printf("%d\n", min);
    int sec = min * 60 - s;               // 4*60 - 30 = 240 - 30 = 210
    return sec;
}

void TestSS()
{
    TEST_ASSERT_EQUAL(15, SleepSeconds(5, 45, 15));
    TEST_ASSERT_EQUAL(30, SleepSeconds(25, 45, 30));

    TEST_ASSERT_EQUAL(3 * 60 + 30, SleepSeconds(56, 30, 300));
    TEST_ASSERT_EQUAL(2 * 60 + 00, SleepSeconds(58, 00, 300));
    TEST_ASSERT_EQUAL(0 * 60 + 15, SleepSeconds(59, 45, 300));
    TEST_ASSERT_EQUAL(3 * 60 + 30, SleepSeconds(16, 30, 300));
    TEST_ASSERT_EQUAL(2 * 60 + 00, SleepSeconds(38, 00, 300));
    TEST_ASSERT_EQUAL(0 * 60 + 15, SleepSeconds(29, 45, 300));
    
    TEST_ASSERT_EQUAL(4 * 60 + 15, SleepSeconds(0, 45, 300));
    TEST_ASSERT_EQUAL(0 * 60 + 15, SleepSeconds(0, 45, 60));
    TEST_ASSERT_EQUAL(1 * 60 + 45, SleepSeconds(02, 15, 120));
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(TestSS);

    UNITY_END();
    return 0;
}
