#include <gtest/gtest.h>
#include "string_opt.h"

TEST(stringTestCase, testToHex) { EXPECT_EQ(Common::toHexString("0"), "30"); }