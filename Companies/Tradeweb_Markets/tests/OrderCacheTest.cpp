#include <gtest/gtest.h>
#include "OrderCache.h"

class OrderCacheTest : public ::testing::Test
{
protected:
    OrderCache cache;

    // Helper function to add orders to cache
    void addOrderToCache(const std::string &orderId, const std::string &securityId, const std::string &side, 
                         unsigned int qty, const std::string &user, const std::string &company)
    {
        Order order(orderId, securityId, side, qty, user, company);
        cache.addOrder(order);
    }
};

// Example 1 Test
TEST_F(OrderCacheTest, Example1)
{
    // Add the orders
    addOrderToCache("OrdId1", "SecId1", "Buy", 1000, "User1", "CompanyA");
    addOrderToCache("OrdId2", "SecId2", "Sell", 3000, "User2", "CompanyB");
    addOrderToCache("OrdId3", "SecId1", "Sell", 500, "User3", "CompanyA");
    addOrderToCache("OrdId4", "SecId2", "Buy", 600, "User4", "CompanyC");
    addOrderToCache("OrdId5", "SecId2", "Buy", 100, "User5", "CompanyB");
    addOrderToCache("OrdId6", "SecId3", "Buy", 1000, "User6", "CompanyD");
    addOrderToCache("OrdId7", "SecId2", "Buy", 2000, "User7", "CompanyE");
    addOrderToCache("OrdId8", "SecId2", "Sell", 5000, "User8", "CompanyE");

    // Test for SecId1
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId1"), 0); // No matches because both orders are from CompanyA

    // Test for SecId2
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId2"), 2700); // Total matching qty for SecId2 is 2700

    // Test for SecId3
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId3"), 0); // Only one Buy order, no Sell orders to match
}

// Example 2 Test
TEST_F(OrderCacheTest, Example2)
{
    // Add the orders
    addOrderToCache("OrdId1", "SecId1", "Sell", 100, "User10", "Company2");
    addOrderToCache("OrdId2", "SecId3", "Sell", 200, "User8", "Company2");
    addOrderToCache("OrdId3", "SecId1", "Buy", 300, "User13", "Company2");
    addOrderToCache("OrdId4", "SecId2", "Sell", 400, "User12", "Company2");
    addOrderToCache("OrdId5", "SecId3", "Sell", 500, "User7", "Company2");
    addOrderToCache("OrdId6", "SecId3", "Buy", 600, "User3", "Company1");
    addOrderToCache("OrdId7", "SecId1", "Sell", 700, "User10", "Company2");
    addOrderToCache("OrdId8", "SecId1", "Sell", 800, "User2", "Company1");
    addOrderToCache("OrdId9", "SecId2", "Buy", 900, "User6", "Company2");
    addOrderToCache("OrdId10", "SecId2", "Sell", 1000, "User5", "Company1");
    addOrderToCache("OrdId11", "SecId1", "Sell", 1100, "User13", "Company2");
    addOrderToCache("OrdId12", "SecId2", "Buy", 1200, "User9", "Company2");
    addOrderToCache("OrdId13", "SecId1", "Sell", 1300, "User1", "Company2");

    // Test for SecId1
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId1"), 300);

    // Test for SecId2
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId2"), 1000);

    // Test for SecId3
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId3"), 600);
}

// Example 3 Test
TEST_F(OrderCacheTest, Example3)
{
    // Add the orders
    addOrderToCache("OrdId1", "SecId3", "Sell", 100, "User1", "Company1");
    addOrderToCache("OrdId2", "SecId3", "Sell", 200, "User3", "Company2");
    addOrderToCache("OrdId3", "SecId1", "Buy", 300, "User2", "Company1");
    addOrderToCache("OrdId4", "SecId3", "Sell", 400, "User5", "Company2");
    addOrderToCache("OrdId5", "SecId2", "Sell", 500, "User2", "Company1");
    addOrderToCache("OrdId6", "SecId2", "Buy", 600, "User3", "Company2");
    addOrderToCache("OrdId7", "SecId2", "Sell", 700, "User1", "Company1");
    addOrderToCache("OrdId8", "SecId1", "Sell", 800, "User2", "Company1");
    addOrderToCache("OrdId9", "SecId1", "Buy", 900, "User5", "Company2");
    addOrderToCache("OrdId10", "SecId1", "Sell", 1000, "User1", "Company1");
    addOrderToCache("OrdId11", "SecId2", "Sell", 1100, "User6", "Company2");

    // Test for SecId1
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId1"), 900);

    // Test for SecId2
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId2"), 600);

    // Test for SecId3
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId3"), 0);
}

// Example 4 Test with additional cancellation functions
TEST_F(OrderCacheTest, Example4)
{
    // Add the orders
    addOrderToCache("OrdId1", "SecId1", "Buy", 1000, "User1", "CompanyA");
    addOrderToCache("OrdId2", "SecId2", "Sell", 3000, "User2", "CompanyB");
    addOrderToCache("OrdId3", "SecId1", "Sell", 500, "User3", "CompanyA");
    addOrderToCache("OrdId4", "SecId2", "Buy", 600, "User4", "CompanyC");
    addOrderToCache("OrdId5", "SecId2", "Buy", 100, "User5", "CompanyB");
    addOrderToCache("OrdId6", "SecId3", "Buy", 1000, "User6", "CompanyD");
    addOrderToCache("OrdId7", "SecId2", "Buy", 2000, "User7", "CompanyE");
    addOrderToCache("OrdId8", "SecId2", "Sell", 5000, "User8", "CompanyE");

    // Test for SecId1
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId1"), 0); // No matches because both orders are from CompanyA

    // Test for SecId2
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId2"), 2700); // Total matching qty for SecId2 is 2700

    // Test for SecId3
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId3"), 0); // Only one Buy order, no Sell orders to match

    ////////////////////////////////////////////////////////////////////////////////////////

    addOrderToCache("OrdId9", "SecId1", "Buy", 1000, "User1", "CompanyB");
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId1"), 500);

    addOrderToCache("OrdId10", "SecId1", "Sell", 200, "User1", "CompanyA");
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId1"), 200);

    addOrderToCache("OrdId11", "SecId1", "Sell", 1000, "User2", "CompanyD");
    addOrderToCache("OrdId12", "SecId1", "Buy", 400, "User3", "CompanyC");

    cache.cancelOrder("OrdId1");
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId1"), 700);

    addOrderToCache("OrdId13", "SecId1", "Buy", 300, "User3", "CompanyC");
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId1"), 300);

    addOrderToCache("OrdId14", "SecId1", "Buy", 500, "User3", "CompanyC");
    cache.cancelOrdersForUser("User2");
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId1"), 0);

    ////////////////////////////////////////////////////////////////////////////////////////

    addOrderToCache("OrdId15", "SecId2", "Buy", 3000, "User5", "CompanyA");
    addOrderToCache("OrdId16", "SecId2", "Buy", 800, "User3", "CompanyA");
    addOrderToCache("OrdId18", "SecId2", "Buy", 500, "User5", "CompanyC");
    addOrderToCache("OrdId19", "SecId2", "Buy", 4100, "User3", "CompanyE");

    cache.cancelOrdersForUser("User3");
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId2"), 3500);

    ////////////////////////////////////////////////////////////////////////////////////////

    addOrderToCache("OrdId20", "SecId3", "Buy", 180, "User4", "CompanyE");
    addOrderToCache("OrdId21", "SecId3", "Buy", 10, "User4", "CompanyC");
    addOrderToCache("OrdId22", "SecId3", "Sell", 600, "User3", "CompanyE");
    addOrderToCache("OrdId23", "SecId3", "Sell", 200, "User3", "CompanyA");
    cache.cancelOrdersForSecIdWithMinimumQty("SecId3", 300);
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId3"), 190);

    addOrderToCache("OrdId21", "SecId3", "Buy", 10, "User4", "CompanyC");
    EXPECT_EQ(cache.getMatchingSizeForSecurity("SecId3"), 0);
}
