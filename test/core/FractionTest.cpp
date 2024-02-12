//
// Created by Amy Fetzner on 2/11/2024.
//

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"
#include "Farey/Fraction.h"

using namespace Farey;

TEST_CASE("Fraction arithmetic") {
    GIVEN("Two coprime fractions") {
        Fraction f1_2 {1, 2};
        Fraction f3_5 {3, 5};

        REQUIRE_THAT(f1_2.toFloat(),  Catch::Matchers::WithinRel(0.5, 0));
        REQUIRE_THAT(f3_5.toFloat(),  Catch::Matchers::WithinRel(0.6, 0.00001));
        REQUIRE_THAT(f1_2.toDouble(), Catch::Matchers::WithinRel(0.5, 0));
        REQUIRE_THAT(f3_5.toDouble(), Catch::Matchers::WithinRel(0.6, 0.00001));

        WHEN("Binary arithmetic operators are applied"){
            Fraction sum = f1_2 + f3_5;
            Fraction diff1 = f1_2 - f3_5;
            Fraction diff2 = f3_5 - f1_2;
            Fraction product = f1_2 * f3_5;
            Fraction quotient1 = f1_2 / f3_5;
            Fraction quotient2 = f3_5 / f1_2;
            Fraction mediant_ = mediant(f1_2, f3_5);
            THEN("The sum is correct"){
                CHECK(sum == Fraction {11, 10});
            }
            THEN("The difference is correct"){
                CHECK(diff1 == Fraction {-1, 10});
                CHECK(diff2 == Fraction {1, 10});
            }
            THEN("The product is correct"){
                CHECK(product == Fraction {3, 10});
            }
            THEN("The quotient is correct"){
                CHECK(quotient1 == Fraction {5, 6});
                CHECK(quotient2 == Fraction {6, 5});
            }
            THEN("The mediant is correct"){
                CHECK(mediant_ == Fraction {4, 7});
            }

        }
    }

    GIVEN("Two fractions with shared factors") {
        Fraction f3_4 {3, 4};
        Fraction f1_12 {1, 12};

        REQUIRE_THAT(f3_4.toFloat(), Catch::Matchers::WithinRel(3. / 4, 0));
        REQUIRE_THAT(f1_12.toFloat(), Catch::Matchers::WithinRel(1. / 12, 0.0001));
        REQUIRE_THAT(f3_4.toDouble(), Catch::Matchers::WithinRel(3. / 4, 0));
        REQUIRE_THAT(f1_12.toDouble(), Catch::Matchers::WithinRel(1. / 12, 0.0001));

        WHEN("Binary arithmetic operators are applied"){
            Fraction sum = f3_4 + f1_12;
            Fraction diff1 = f3_4 - f1_12;
            Fraction diff2 = f1_12 - f3_4;
            Fraction product = f3_4 * f1_12;
            Fraction quotient1 = f3_4 / f1_12;
            Fraction quotient2 = f1_12 / f3_4;
            Fraction mediant_ = mediant(f3_4, f1_12);
            THEN("The sum is correct"){
                CHECK(sum == Fraction {5, 6});
            }
            THEN("The difference is correct"){
                CHECK(diff1 == Fraction {2, 3});
                CHECK(diff2 == Fraction {-2, 3});
            }
            THEN("The product is correct"){
                CHECK(product == Fraction {1, 16});
            }
            THEN("The quotient is correct"){
                CHECK(quotient1 == Fraction {9, 1});
                CHECK(quotient2 == Fraction {1, 9});
            }
            THEN("The mediant is correct"){
                CHECK(mediant_ == Fraction {1, 4});
            }
        }
    }

    GIVEN("Two large fractions nearly overflowing") {
        Fraction f2_3 {1'073'741'824, 1'162'261'467};  // 2^30 / 3^19

        WHEN("They are multiplied or divided"){
            Fraction product = f2_3 * Fraction {9, 4};
            // 2^30 * 9 = 9,663,676,416   and   3^19 * 4 = 4,649,045,868   are both larger than 32-bit int max
            // But when multiplied they reduce to numbers representable with 32 bits

            Fraction quotient1 = f2_3 / Fraction {4, 9};
            Fraction quotient2 = Fraction {4, 9} / f2_3;

            THEN("The product is correct and does not overflow"){
                CHECK(product == Fraction {268'435'456, 129'140'163});  // == 2^28 / 3^17
            }
            THEN("The quotient is correct"){
                CHECK(quotient1 == Fraction {268'435'456, 129'140'163});
                CHECK(quotient2 == Fraction {129'140'163, 268'435'456});
            }
        }

        Fraction f1{1'073'741'821, 4};  // (2^30 - 3) / 4
        Fraction f2{1'073'741'827, 4};  // (2^30 + 3) / 4
        WHEN("They are added or subtracted"){
            Fraction sum = f1 + f2;    // Should be 2^31 / 4 = 2^29
            Fraction diff1 = f1 - f2;  // Should be -3/2
            Fraction diff2 = f2 - f1;  // Should be 3/2

            THEN("The sum is correct and does not overflow"){
                CHECK(sum == Fraction {536'870'912, 1});
            }
            THEN("The difference is correct and does not overflow"){
                CHECK(diff1 == Fraction {-3, 2});
                CHECK(diff2 == Fraction {3, 2});
            }
        }
    }

    GIVEN("A fraction and an integer") {
        Fraction f1_2 {1, 2};

        WHEN("Binary arithmetic operators are applied"){
            Fraction sum1 = f1_2 + 2;
            Fraction sum2 = 2 + f1_2;
            Fraction diff1 = f1_2 - 2;
            Fraction diff2 = 2 - f1_2;
            Fraction product1 = f1_2 * 2;
            Fraction product2 = 2 * f1_2;
            Fraction quotient1 = f1_2 / 2;
            Fraction quotient2 = 2 / f1_2;
            Fraction negative = -f1_2;

            THEN("The sum is correct"){
                CHECK(sum1 == Fraction {5, 2});
                CHECK(sum2 == Fraction {5, 2});
            }
            THEN("The difference is correct"){
                CHECK(diff1 == Fraction {-3, 2});
                CHECK(diff2 == Fraction {3, 2});
            }
            THEN("The product is correct"){
                CHECK(product1 == Fraction {1, 1});
                CHECK(product2 == Fraction {1, 1});
            }
            THEN("The quotient is correct"){
                CHECK(quotient1 == Fraction {1, 4});
                CHECK(quotient2 == Fraction {4, 1});
            }
            THEN("The negation is correct"){
                CHECK(negative == Fraction {-1, 2});
            }
        }
    }
}

TEST_CASE("Fraction approximation"){
    GIVEN("A real number exactly 0"){
        THEN("It's approximation is exactly correct"){
            CHECK(Fraction::approximate(0., 3) == Fraction{0, 1});
        }
    }
    GIVEN("A real number exactly 1"){
        THEN("It's approximation is exactly correct"){
            CHECK(Fraction::approximate(1., 3) == Fraction{1, 1});
        }
    }
    GIVEN("A real number exactly a power of 2"){
        THEN("It's approximation is exactly correct"){
            CHECK(Fraction::approximate(0.5, 3) == Fraction{1, 2});
            CHECK(Fraction::approximate(0.25, 5) == Fraction{1, 4});
            CHECK(Fraction::approximate(0.125, 10) == Fraction{1, 8});
        }
    }
    GIVEN("A real number exactly representable by a fraction"){
        THEN("It's approximation is exactly correct"){
            CHECK(Fraction::approximate(3. / 7., 10) == Fraction{3, 7});
            CHECK(Fraction::approximate(2. / 3., 10) == Fraction{2, 3});
            CHECK(Fraction::approximate(13. / 17., 20) == Fraction{13, 17});
        }
    }
    GIVEN("A real number exactly representable by a fraction, but not with a low enough order"){
        THEN("It's approximation is nearly correct"){
            CHECK(Fraction::approximate(3. / 7., 4) == Fraction{1, 2});
            CHECK(Fraction::approximate(13. / 17., 5) == Fraction{3, 4});
        }
    }
}
