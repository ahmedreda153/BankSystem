#include <gtest/gtest.h>
#include "BankApp.h"
#include "Client.h"
#include "BankAcc.h"
#include "SavingsBankAcc.h"

// Test fixture for BankAcc class
class BankAccTest : public ::testing::Test {
protected:
    BankAcc account;
};

// Test default constructor
TEST_F(BankAccTest, DefaultConstructor) {
    EXPECT_EQ(account.getBalance(), 0);
}

// Test parameterized constructor
TEST_F(BankAccTest, ParameterizedConstructor) {
    BankAcc account(100.0);
    EXPECT_EQ(account.getBalance(), 100.0);
}

// Test setAccountID and getAccountID
TEST_F(BankAccTest, AccountID) {
    account.setAccountID("12345");
    EXPECT_EQ(account.getAccountID(), "12345");
}

// Test setBalance and getBalance
TEST_F(BankAccTest, SetAndGetBalance) {
    EXPECT_TRUE(account.setBalance(200.0));
    EXPECT_EQ(account.getBalance(), 200.0);
    EXPECT_FALSE(account.setBalance(-50.0));
    EXPECT_EQ(account.getBalance(), 200.0);
}

// Test setType and getType
TEST_F(BankAccTest, SetAndGetType) {
    account.setType("Basic");
    EXPECT_EQ(account.getType(), "Basic");
}

// Test setClient and getClient
TEST_F(BankAccTest, SetAndGetClient) {
    Client client;
    account.setClient(client);
    EXPECT_EQ(account.getClient(), &client);
}

// Test withdraw method
TEST_F(BankAccTest, Withdraw) {
    account.setBalance(200.0);
    EXPECT_TRUE(account.withdraw(100.0));
    EXPECT_EQ(account.getBalance(), 100.0);
    EXPECT_FALSE(account.withdraw(300.0));
    EXPECT_EQ(account.getBalance(), 100.0);
}

// Test deposit method
TEST_F(BankAccTest, Deposit) {
    EXPECT_TRUE(account.deposit(100.0));
    EXPECT_EQ(account.getBalance(), 100.0);
    EXPECT_FALSE(account.deposit(-50.0));
    EXPECT_EQ(account.getBalance(), 100.0);
}

// Test fixture for SavingsBankAcc class
class SavingsBankAccTest : public ::testing::Test {
protected:
    SavingsBankAcc account;
};

// Test default constructor
TEST_F(SavingsBankAccTest, DefaultConstructor) {
    EXPECT_EQ(account.getMinimumBalance(), 1000);
}

// Test setMinimumBalance and getMinimumBalance
TEST_F(SavingsBankAccTest, SetAndGetMinimumBalance) {
    account.setMinimumBalance(1500.0);
    EXPECT_EQ(account.getMinimumBalance(), 1500.0);
}

// Test setBalance
TEST_F(SavingsBankAccTest, SetBalance) {
    EXPECT_FALSE(account.setBalance(500.0));
    EXPECT_EQ(account.getBalance(), 0);
    EXPECT_TRUE(account.setBalance(1500.0));
    EXPECT_EQ(account.getBalance(), 1500.0);
}

// Test withdraw method
TEST_F(SavingsBankAccTest, Withdraw) {
    account.setBalance(2000.0);
    EXPECT_TRUE(account.withdraw(500.0));
    EXPECT_EQ(account.getBalance(), 1500.0);
    EXPECT_FALSE(account.withdraw(1600.0));
    EXPECT_EQ(account.getBalance(), 1500.0);
}

// Test deposit method
TEST_F(SavingsBankAccTest, Deposit) {
    EXPECT_FALSE(account.deposit(50.0));
    EXPECT_EQ(account.getBalance(), 0);
    EXPECT_TRUE(account.deposit(150.0));
    EXPECT_EQ(account.getBalance(), 150.0);
}

class BankAppTest : public ::testing::Test {
    protected:
        BankApp bankApp;
    };

// Test listClients() output
TEST_F(BankAppTest, ListClientsOutputsCorrectly) {
    std::stringstream buffer;
    std::streambuf* prevcout = std::cout.rdbuf(buffer.rdbuf()); // Redirect std::cout

    // Call method
    bankApp.listClients();

    std::cout.rdbuf(prevcout); // Restore std::cout

    // Verify output
    EXPECT_EQ(buffer.str(), "List of Clients and Accounts\n");
}

// Test withdraw() output
TEST_F(BankAppTest, WithdrawOutputsCorrectly) {
    std::stringstream buffer;
    std::streambuf* prevcout = std::cout.rdbuf(buffer.rdbuf()); // Redirect std::cout

    // Call method
    bankApp.withdraw();

    std::cout.rdbuf(prevcout); // Restore std::cout

    // Verify output
    EXPECT_EQ(buffer.str(), "Withdraw done\n");
}

// Test withdraw() output
TEST_F(BankAppTest, WithdrawOutputsCorrectlyNew) {
    std::stringstream buffer;
    std::streambuf* prevcout = std::cout.rdbuf(buffer.rdbuf()); // Redirect std::cout

    // Call method
    bankApp.withdraw();

    std::cout.rdbuf(prevcout); // Restore std::cout

    // Verify output
    EXPECT_EQ(buffer.str(), "Withdraw done\n");
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


void addTest(){
int x = 6;
}
