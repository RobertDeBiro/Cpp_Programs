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
    Order(const std::string &ordId, const std::string &secId, const std::string &side, const unsigned int qty, const std::string &user,
          const std::string &company)
        : m_orderId(ordId), m_securityId(secId), m_side(side), m_qty(qty), m_user(user), m_company(company) {}

    std::string orderId() const { return m_orderId; }
    std::string securityId() const { return m_securityId; }
    std::string side() const { return m_side; }
    std::string user() const { return m_user; }
    std::string company() const { return m_company; }
    unsigned int qty() const { return m_qty; }

    void reduceQty(unsigned int amount)
    {
        m_qty = (amount > m_qty) ? 0 : (m_qty - amount); // Reduce qty safely
    }

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
    virtual void cancelOrder(const std::string &orderId) = 0;

    // remove all orders in the cache for this user
    virtual void cancelOrdersForUser(const std::string &user) = 0;

    // remove all orders in the cache for this security with qty >= minQty
    virtual void cancelOrdersForSecIdWithMinimumQty(const std::string &securityId, unsigned int minQty) = 0;

    // return the total qty that can match for the security id
    virtual unsigned int getMatchingSizeForSecurity(const std::string &securityId) = 0;

    // return all orders in cache in a vector
    virtual std::vector<Order> getAllOrders() const = 0;
};

class OrderCache : public OrderCacheInterface
{
public:
    void addOrder(Order order) override;
    void cancelOrder(const std::string &orderId) override;
    void cancelOrdersForUser(const std::string &user) override;
    void cancelOrdersForSecIdWithMinimumQty(const std::string &securityId, unsigned int minQty) override;
    unsigned int getMatchingSizeForSecurity(const std::string &securityId) override;
    std::vector<Order> getAllOrders() const override;

private:
    std::list<Order> m_orders;
    std::unordered_map<std::string, std::list<Order>::iterator> m_orderMap;
    mutable std::mutex m_mutex;

    void collectBuyAndSellOrders(const std::string &securityId, std::list<Order *> &buyOrders, std::list<Order *> &sellOrders);
    unsigned int matchOrders(std::list<Order *> &buyOrders, std::list<Order *> &sellOrders);
    unsigned int matchWithSellOrders(Order *buyOrder, std::list<Order *> &sellOrders);
    void reduceOrderQty(Order *buyOrder, Order *sellOrder, unsigned int matchQty);
    void EraseOrdersContainers(const std::string &orderId, std::list<Order>::iterator it);
};
