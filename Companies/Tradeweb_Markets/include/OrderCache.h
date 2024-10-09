#pragma once

#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <vector>
#include <mutex>

class Order
{
public:
    Order(const std::string& ordId, const std::string& secId, const std::string& side, const unsigned int qty,
          const std::string& user, const std::string& company)
        : m_orderId(ordId), m_securityId(secId), m_side(side), m_qty(qty), m_user(user), m_company(company) {}

    std::string orderId() const { return m_orderId; }
    std::string securityId() const { return m_securityId; }
    std::string side() const { return m_side; }
    std::string user() const { return m_user; }
    std::string company() const { return m_company; }
    unsigned int qty() const { return m_qty; }

    void reduceQty(unsigned int amount);

private:
    std::string m_orderId;    // unique order id
    std::string m_securityId; // security identifier
    std::string m_side;       // side of the order, eg Buy or Sell
    unsigned int m_qty;       // qty for this order
    std::string m_user;       // user name who owns this order
    std::string m_company;    // company for user
};

class OrderCacheInterface
{
public:
    // add order to the cache
    virtual void addOrder(Order order) = 0;

    // remove order with this unique order id from the cache
    virtual void cancelOrder(const std::string& orderId) = 0;

    // remove all orders in the cache for this user
    virtual void cancelOrdersForUser(const std::string& user) = 0;

    // remove all orders in the cache for this security with qty >= minQty
    virtual void cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty) = 0;

    // return the total qty that can match for the security id
    virtual unsigned int getMatchingSizeForSecurity(const std::string& securityId) = 0;

    // return all orders in cache in a vector
    virtual std::vector<Order> getAllOrders() const = 0;
};

class OrderCache : public OrderCacheInterface
{
public:
    void addOrder(Order order) override;
    void cancelOrder(const std::string& orderId) override;
    void cancelOrdersForUser(const std::string& user) override;
    void cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty) override;
    unsigned int getMatchingSizeForSecurity(const std::string& securityId) override;
    std::vector<Order> getAllOrders() const override;

private:
    // List of added orders
    std::list<Order> m_orders;

    // Map with following key-value pair:
    // - key: orderID
    // - value: pointer to an order present inside list m_orders and defined with orderID from key
    // Used for fast deletion of order when canceling order by its ID.
    std::unordered_map<std::string, std::list<Order>::iterator> m_orderMap;

    // mutex for making functions thread safety
    mutable std::mutex m_mutex;

    // Function that collects Buy and Sell orders for particular securityId
    void collectBuyAndSellOrders(const std::string& securityId, std::list<Order*>& buyOrders, std::list<Order*>& sellOrders);

    // Function that matches Buy and Sell orders for particular securityId and returns total matched quantity
    unsigned int matchOrders(std::list<Order*>& buyOrders, std::list<Order*>& sellOrders);

    // Function that matches a Buy order with Sell orders
    unsigned int matchWithSellOrders(Order* buyOrder, std::list<Order*>& sellOrders);

    // Function that reduces Buy and Sell order quantities
    void reduceOrderQty(Order* buyOrder, Order* sellOrder, unsigned int matchQty);

    // Erase order both from m_orders list and m_orders map
    std::list<Order>::iterator eraseOrderFromContainers(const std::string& orderId, std::list<Order>::iterator it);
};
