#include <gtest/gtest.h>
#include "puissance.h"

TEST(test_puissance, test_puissance_modulaire) {
    EXPECT_EQ(puissance::puissance_modulaire(2u, 10u, 100u), 24u);
}

TEST(test_puissance, test_puissance) {
    EXPECT_EQ(puissance::puissance(2u, 10u), 1024u);
}
