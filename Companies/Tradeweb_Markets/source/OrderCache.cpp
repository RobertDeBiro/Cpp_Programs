#include "OrderCache.h"

void OrderCache::addOrder(Order order)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_orders.push_back(order);
    m_orderMap[order.orderId()] = --m_orders.end();
}

void OrderCache::cancelOrder(const std::string &orderId)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_orderMap.find(orderId);
    if (it != m_orderMap.end())
        EraseOrdersContainers(it->first, it->second);
}

void OrderCache::cancelOrdersForUser(const std::string &user)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_orders.begin();
    while (it != m_orders.end())
    {
        if (it->user() == user)
            EraseOrdersContainers(it->orderId(), it);
        else
            ++it;
    }
}

void OrderCache::cancelOrdersForSecIdWithMinimumQty(const std::string &securityId, unsigned int minQty)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_orders.begin();
    while (it != m_orders.end())
    {
        if (it->securityId() == securityId && it->qty() >= minQty)
            EraseOrdersContainers(it->orderId(), it);
        else
            ++it;
    }
}

unsigned int OrderCache::getMatchingSizeForSecurity(const std::string &securityId)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    unsigned int totalMatchedQty = 0;

    // Separate Buy and Sell orders for this security ID
    std::list<Order *> buyOrders, sellOrders;
    collectBuyAndSellOrders(securityId, buyOrders, sellOrders);

    // Match Buy and Sell orders
    totalMatchedQty = matchOrders(buyOrders, sellOrders);

    return totalMatchedQty;
}

std::vector<Order> OrderCache::getAllOrders() const
{
    return std::vector<Order>(m_orders.begin(), m_orders.end());
}

// Function to collect Buy and Sell orders
void OrderCache::collectBuyAndSellOrders(const std::string &securityId, std::list<Order *> &buyOrders, std::list<Order *> &sellOrders)
{
    for (auto &order : m_orders)
    {
        if (order.securityId() == securityId)
        {
            if (order.side() == "Buy")
            {
                buyOrders.push_back(&order);
            }
            else if (order.side() == "Sell")
            {
                sellOrders.push_back(&order);
            }
        }
    }
}

// Function to match Buy and Sell orders
unsigned int OrderCache::matchOrders(std::list<Order *> &buyOrders, std::list<Order *> &sellOrders)
{
    unsigned int totalMatchedQty = 0;

    for (auto buyIt = buyOrders.begin(); buyIt != buyOrders.end() && !sellOrders.empty();)
    {
        Order *buyOrder = *buyIt;
        totalMatchedQty += matchWithSellOrders(buyOrder, sellOrders);

        // Remove fully matched Buy order
        if (buyOrder->qty() == 0)
        {
            buyIt = buyOrders.erase(buyIt);
        }
        else
        {
            ++buyIt;
        }
    }
    return totalMatchedQty;
}

// Function to match a Buy order with Sell orders
unsigned int OrderCache::matchWithSellOrders(Order *buyOrder, std::list<Order *> &sellOrders)
{
    unsigned int matchedQty = 0;

    for (auto sellIt = sellOrders.begin(); sellIt != sellOrders.end() && buyOrder->qty() > 0;)
    {
        Order *sellOrder = *sellIt;

        // Skip if same company
        if (buyOrder->company() == sellOrder->company())
        {
            ++sellIt;
            continue;
        }

        // Calculate matched quantity
        unsigned int matchQty = std::min(buyOrder->qty(), sellOrder->qty());
        matchedQty += matchQty;

        // Reduce quantities from matched orders
        reduceOrderQty(buyOrder, sellOrder, matchQty);

        // Remove fully matched Sell order
        if (sellOrder->qty() == 0)
        {
            sellIt = sellOrders.erase(sellIt);
        }
        else
        {
            ++sellIt;
        }
    }
    return matchedQty;
}

// Function to reduce order quantities
void OrderCache::reduceOrderQty(Order *buyOrder, Order *sellOrder, unsigned int matchQty)
{
    buyOrder->reduceQty(matchQty);
    sellOrder->reduceQty(matchQty);
}

void OrderCache::EraseOrdersContainers(const std::string &orderId, std::list<Order>::iterator it)
{
    m_orders.erase(it);
    m_orderMap.erase(orderId);
}
