#include "calculator.h"
#include "gtest/gtest.h"

namespace {

class CalculatorTest : public ::testing::Test
{
    public:
    calculator gCalculator;

    protected:
    CalculatorTest() {}

    virtual ~CalculatorTest() {}
    virtual void SetUp()
    {
        std::cout << "Setup" << std::endl;
    }

    virtual void TearDown()
    {
        std::cout << "TearDown" << std::endl;
    }
};

TEST_F(CalculatorTest, plus_p)
{
    EXPECT_EQ(2, gCalculator.plus(1, 1));
}

} // namespace

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
/*
#include "gtest/gtest.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/