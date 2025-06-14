#include <gtest/gtest.h>
#include "BankApp.h"
#include "Client.h"
#include "BankAcc.h"
#include "SavingsBankAcc.h"

// Test fixture for BankAcc class
class BankAccTest : public ::testing::Test
{
protected:
    BankAcc account;
};

// Test default constructor
TEST_F(BankAccTest, DefaultConstructor)
{
    EXPECT_EQ(account.getBalance(), 0);
}

// Test parameterized constructor
TEST_F(BankAccTest, ParameterizedConstructor)
{
    BankAcc account(100.0);
    EXPECT_EQ(account.getBalance(), 100.0);
}

// Test setAccountID and getAccountID
TEST_F(BankAccTest, AccountID)
{
    account.setAccountID("12345");
    EXPECT_EQ(account.getAccountID(), "12345");
}

// Test setBalance and getBalance
TEST_F(BankAccTest, SetAndGetBalance)
{
    EXPECT_TRUE(account.setBalance(200.0));
    EXPECT_EQ(account.getBalance(), 200.0);
    EXPECT_FALSE(account.setBalance(5.0)); // Now minimum is 10
    EXPECT_EQ(account.getBalance(), 200.0);
}

// Test setType and getType
TEST_F(BankAccTest, SetAndGetType)
{
    account.setType("Basic");
    EXPECT_EQ(account.getType(), "Basic");
}

// Test setClient and getClient
TEST_F(BankAccTest, SetAndGetClient)
{
    Client client;
    account.setClient(client);
    EXPECT_EQ(account.getClient(), &client);
}

// Test withdraw method
TEST_F(BankAccTest, Withdraw)
{
    account.setBalance(200.0);
    EXPECT_TRUE(account.withdraw(100.0));
    EXPECT_EQ(account.getBalance(), 95.0); // 200 - 100 - 5(fee) = 95
    EXPECT_FALSE(account.withdraw(300.0));
    EXPECT_EQ(account.getBalance(), 95.0);
}

// Test deposit method
TEST_F(BankAccTest, Deposit)
{
    EXPECT_TRUE(account.deposit(100.0));
    EXPECT_EQ(account.getBalance(), 100.0);
    EXPECT_FALSE(account.deposit(-50.0));
    EXPECT_EQ(account.getBalance(), 100.0);
}

// Test transferFunds method
TEST_F(BankAccTest, TransferFunds)
{
    BankAcc sourceAccount(200.0);
    BankAcc destinationAccount(50.0);

    EXPECT_TRUE(sourceAccount.transferFunds(destinationAccount, 100.0));
    // After transfer: source = 200 - 100 - 5(withdraw fee) = 95
    // destination = 50 + 100 = 150
    EXPECT_EQ(sourceAccount.getBalance(), 95.0);
    EXPECT_EQ(destinationAccount.getBalance(), 150.0);

    // Test transfer with insufficient funds
    EXPECT_FALSE(sourceAccount.transferFunds(destinationAccount, 500.0));
    EXPECT_EQ(sourceAccount.getBalance(), 95.0);
    EXPECT_EQ(destinationAccount.getBalance(), 150.0);
}

// Test getFeeHistory method
TEST_F(BankAccTest, GetFeeHistory)
{
    BankAcc sourceAccount(300.0);
    BankAcc destinationAccount(50.0);

    // Initially no fees
    EXPECT_EQ(sourceAccount.getFeeHistory().size(), 0);

    // After transfer, should have recorded the fee
    sourceAccount.transferFunds(destinationAccount, 100.0);
    EXPECT_EQ(sourceAccount.getFeeHistory().size(), 1);

    // Make another transfer
    sourceAccount.transferFunds(destinationAccount, 50.0);
    EXPECT_EQ(sourceAccount.getFeeHistory().size(), 2);
}

// Test fixture for SavingsBankAcc class
class SavingsBankAccTest : public ::testing::Test
{
protected:
    SavingsBankAcc account;
};

// Test default constructor
TEST_F(SavingsBankAccTest, DefaultConstructor)
{
    EXPECT_EQ(account.getMinimumBalance(), 1000);
}

// Test setMinimumBalance and getMinimumBalance
TEST_F(SavingsBankAccTest, SetAndGetMinimumBalance)
{
    account.setMinimumBalance(1500.0);
    EXPECT_EQ(account.getMinimumBalance(), 1500.0);
}

// Test setBalance
TEST_F(SavingsBankAccTest, SetBalance)
{
    EXPECT_FALSE(account.setBalance(500.0));
    EXPECT_EQ(account.getBalance(), 0);
    EXPECT_TRUE(account.setBalance(1500.0));
    EXPECT_EQ(account.getBalance(), 1500.0);
}

// Test withdraw method
TEST_F(SavingsBankAccTest, Withdraw)
{
    account.setBalance(2000.0);
    EXPECT_TRUE(account.withdraw(500.0));
    EXPECT_EQ(account.getBalance(), 1495.0); // 2000 - 500 - 5(fee) = 1495
    EXPECT_FALSE(account.withdraw(600.0));   // Would go below minimum balance after fee
    EXPECT_EQ(account.getBalance(), 1495.0);
}

// Test deposit method
TEST_F(SavingsBankAccTest, Deposit)
{
    EXPECT_FALSE(account.deposit(50.0));
    EXPECT_EQ(account.getBalance(), 0);
    EXPECT_TRUE(account.deposit(150.0));
    EXPECT_EQ(account.getBalance(), 153.0); // 150 + (150 * 0.02) = 153.0
}

// Test setInterestRate and getInterestRate
TEST_F(SavingsBankAccTest, SetAndGetInterestRate)
{
    // Default interest rate should be 0.03 (3%)
    EXPECT_EQ(account.getInterestRate(), 0.03);

    // Set new interest rate and verify
    account.setInterestRate(0.05);
    EXPECT_EQ(account.getInterestRate(), 0.05);

    // Test rate bounds checking
    account.setInterestRate(-0.01);             // negative rate not allowed
    EXPECT_EQ(account.getInterestRate(), 0.03); // should revert to default

    account.setInterestRate(0.2);               // rate too high
    EXPECT_EQ(account.getInterestRate(), 0.03); // should revert to default
}

// Test calculateInterest method
TEST_F(SavingsBankAccTest, CalculateInterest)
{
    account.setBalance(1200.0);
    account.setInterestRate(0.06); // 6% annual interest

    // Calculate interest for 6 months
    EXPECT_NEAR(account.calculateInterest(6), 36.0, 0.01); // 1200 * 0.06 * (6/12) = 36

    // Calculate interest for a year
    EXPECT_NEAR(account.calculateInterest(12), 72.0, 0.01); // 1200 * 0.06 * (12/12) = 72

    // Test with invalid period
    EXPECT_EQ(account.calculateInterest(-3), 0.0); // Should return 0 for invalid period
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

void addTest()
{
    int x = 6;
}
