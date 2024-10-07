#include "OrderCache2.h"

void Order::reduceQty(unsigned int amount)
{
    m_qty = (amount > m_qty) ? 0 : (m_qty - amount); // Reduce qty safely
}

// Add an order to the cache
void OrderCache::addOrder(Order order) {
    std::lock_guard<std::mutex> lock(m_mutex);

    // Add the order to the main list and get iterator
    m_orders.push_back(order);
    auto orderIt = --m_orders.end();

    // Store iterators for quick access by orderId, user, and securityId
    m_orderMap[order.orderId()] = orderIt;
    m_ordersByUser[order.user()].push_back(orderIt);
    m_ordersBySecurity[order.securityId()].push_back(orderIt);
}

// Cancel an order by orderId
void OrderCache::cancelOrder(const std::string& orderId) {
    std::lock_guard<std::mutex> lock(m_mutex);

    auto it = m_orderMap.find(orderId);
    if (it != m_orderMap.end()) {
        eraseOrderFromContainers(it->first, it->second);
    }
}

// Cancel all orders for a specific user efficiently
void OrderCache::cancelOrdersForUser(const std::string& user) {
    std::lock_guard<std::mutex> lock(m_mutex);

    auto userOrdersIt = m_ordersByUser.find(user);
    if (userOrdersIt != m_ordersByUser.end()) {
        for (auto it : userOrdersIt->second) {
            eraseOrderFromContainers(it->orderId(), it);
        }
        m_ordersByUser.erase(userOrdersIt);
    }
}

// Cancel all orders for a security with a minimum quantity
void OrderCache::cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty) {
    std::lock_guard<std::mutex> lock(m_mutex);

    auto secOrdersIt = m_ordersBySecurity.find(securityId);
    if (secOrdersIt != m_ordersBySecurity.end()) {
        for (auto it : secOrdersIt->second) {
            if (it->qty() >= minQty) {
                eraseOrderFromContainers(it->orderId(), it);
            }
        }
        m_ordersBySecurity.erase(secOrdersIt);
    }
}

unsigned int OrderCache::getMatchingSizeForSecurity(const std::string& securityId)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    unsigned int totalMatchedQty = 0;

    // Separate Buy and Sell orders for this security ID
    std::list<Order*> buyOrders;
    std::list<Order*> sellOrders;

    collectBuyAndSellOrders(securityId, buyOrders, sellOrders);

    // Match Buy and Sell orders
    totalMatchedQty = matchOrders(buyOrders, sellOrders);

    return totalMatchedQty;
}

// Function to collect Buy and Sell orders using unordered_map
void OrderCache::collectBuyAndSellOrders(const std::string& securityId, std::list<Order*>& buyOrders, std::list<Order*>& sellOrders)
{
    auto secOrdersIt = m_ordersBySecurity.find(securityId);
    if (secOrdersIt != m_ordersBySecurity.end())
    {
        for (auto it : secOrdersIt->second)
        {
            Order* order = &(*it);
            if (order->side() == "Buy")
                buyOrders.push_back(order);
            else if (order->side() == "Sell")
                sellOrders.push_back(order);
        }
    }
}

// Function to match Buy and Sell orders
unsigned int OrderCache::matchOrders(std::list<Order*>& buyOrders, std::list<Order*>& sellOrders)
{
    unsigned int totalMatchedQty = 0;

    for (auto buyIt = buyOrders.begin(); buyIt != buyOrders.end() && !sellOrders.empty();)
    {
        Order* buyOrder = *buyIt;
        totalMatchedQty += matchWithSellOrders(buyOrder, sellOrders);

        // Remove fully matched Buy order
        if (buyOrder->qty() == 0)
            buyIt = buyOrders.erase(buyIt);
        else
            ++buyIt;
    }
    return totalMatchedQty;
}

// Function to match a Buy order with Sell orders
unsigned int OrderCache::matchWithSellOrders(Order* buyOrder, std::list<Order*>& sellOrders)
{
    unsigned int matchedQty = 0;

    for (auto sellIt = sellOrders.begin(); sellIt != sellOrders.end() && buyOrder->qty() > 0;)
    {
        Order* sellOrder = *sellIt;

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
            sellIt = sellOrders.erase(sellIt);
        else
            ++sellIt;
    }
    return matchedQty;
}

// Function to reduce order quantities
void OrderCache::reduceOrderQty(Order* buyOrder, Order* sellOrder, unsigned int matchQty)
{
    buyOrder->reduceQty(matchQty);
    sellOrder->reduceQty(matchQty);
}

// Erase order from all containers
void OrderCache::eraseOrderFromContainers(const std::string& orderId, std::list<Order>::iterator it) {
    m_orders.erase(it);
    m_orderMap.erase(orderId);

    removeOrderFromUserAndSecurityMaps(it);
}

// Remove order from the user and security maps
void OrderCache::removeOrderFromUserAndSecurityMaps(std::list<Order>::iterator it) {
    auto& userOrders = m_ordersByUser[it->user()];
    userOrders.remove(it);
    if (userOrders.empty()) {
        m_ordersByUser.erase(it->user());
    }

    auto& secOrders = m_ordersBySecurity[it->securityId()];
    secOrders.remove(it);
    if (secOrders.empty()) {
        m_ordersBySecurity.erase(it->securityId());
    }
}

// Get all orders as a vector
std::vector<Order> OrderCache::getAllOrders() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return std::vector<Order>(m_orders.begin(), m_orders.end());
}
