#include "OrderCache.h"
#include <utility>

void Order::reduceQty(unsigned int amount)
{
    // If amount of qty to reduce from particular order is bigger than existing order qty value,
    // existing qty is fully mathed and becomes 0, otherwise subtract existing qty value with received amount
    m_qty = (amount > m_qty) ? 0 : (m_qty - amount);
}

void OrderCache::addOrder(Order order)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    // Save order only if order with particular ID doesn't exist
    if (m_orderMap.find(order.orderId()) == m_orderMap.end())
    {
        // Save order to a list
        m_orders.push_back(order);

        // Save orderId and pointer to the order previously saved inside the list
        m_orderMap[order.orderId()] = --m_orders.end();
    }
}

void OrderCache::cancelOrder(const std::string& orderId)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    // If order with received orderId exists, delete it both from list and map container
    auto it = m_orderMap.find(orderId);
    if (it != m_orderMap.end())
        eraseOrderFromContainers(it->first, it->second);
}

void OrderCache::cancelOrdersForUser(const std::string &user)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    // Iterate through list of orders and delete ones with same user
    auto it = m_orders.begin();
    while (it != m_orders.end())
    {
        if (it->user() == user)
            it = eraseOrderFromContainers(it->orderId(), it);
        else
            ++it;
    }
}

void OrderCache::cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    // Iterate through list of orders and delete ones with same securityId and with qty value bigger than
    // required minimum one
    auto it = m_orders.begin();
    while (it != m_orders.end())
    {
        if (it->securityId() == securityId && it->qty() >= minQty)
            it = eraseOrderFromContainers(it->orderId(), it);
        else
            ++it;
    }
}

unsigned int OrderCache::getMatchingSizeForSecurity(const std::string& securityId)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    unsigned int totalMatchedQty = 0;

    // Separate Buy and Sell orders for this security ID
    std::list<Order*> buyOrders;
    std::list<Order*> sellOrders;

    // Collect Buy and Sell orders for particular securityId
    collectBuyAndSellOrders(securityId, buyOrders, sellOrders);

    // Match Buy and Sell orders
    totalMatchedQty = matchOrders(buyOrders, sellOrders);

    return totalMatchedQty;
}

void OrderCache::collectBuyAndSellOrders(const std::string& securityId, std::list<Order*>& buyOrders, std::list<Order*>& sellOrders)
{
    for (auto &order : m_orders)
    {
        if (order.securityId() == securityId)
        {
            if (order.side() == "Buy")
                buyOrders.push_back(&order);
            else if (order.side() == "Sell")
                sellOrders.push_back(&order);
        }
    }
}

unsigned int OrderCache::matchOrders(std::list<Order*>& buyOrders, std::list<Order*>& sellOrders)
{
    unsigned int totalMatchedQty = 0;

    // Iterate through buyOrders until every buyOrder has been tried to match to sellOrder or
    // until every sellOrder is already matched with buyOrder, so there is no data anymore to match
    for (auto buyIt = buyOrders.begin(); buyIt != buyOrders.end() && !sellOrders.empty();)
    {
        // Fetch buyOrder and try to match it to any of the sellOrders
        Order* buyOrder = *buyIt;
        totalMatchedQty += matchWithSellOrders(buyOrder, sellOrders);

        // If quantity of buyOrder is 0, remove buyOrder to avoid matching sellOrders to that one
        // in following iterations
        if (buyOrder->qty() == 0)
            buyIt = buyOrders.erase(buyIt);
        else
            ++buyIt;
    }
    return totalMatchedQty;
}

unsigned int OrderCache::matchWithSellOrders(Order* buyOrder, std::list<Order*>& sellOrders)
{
    unsigned int matchedQty = 0;

    // Iterate through sellOrders until every sellOrder has been tried to match to received buyOrder or
    // until quantity of received buyOrder is 0
    for (auto sellIt = sellOrders.begin(); sellIt != sellOrders.end() && buyOrder->qty() > 0;)
    {
        // Fetch sellOrder and try to match it to received buyOrder
        Order* sellOrder = *sellIt;

        // Skip if same company
        if (buyOrder->company() == sellOrder->company())
        {
            ++sellIt;
            continue;
        }

        // Determine the quantity that can be matched between the current buy and sell orders
        unsigned int matchQty = std::min(buyOrder->qty(), sellOrder->qty());
    
        // Accumulate the matched quantity into the total for the given buy order
        matchedQty += matchQty;

        // Reduce quantities from matched Buy and Sell orders
        reduceOrderQty(buyOrder, sellOrder, matchQty);

        // Remove fully matched Sell order
        if (sellOrder->qty() == 0)
            sellIt = sellOrders.erase(sellIt);
        else
            ++sellIt;
    }
    return matchedQty;
}

void OrderCache::reduceOrderQty(Order* buyOrder, Order* sellOrder, unsigned int matchQty)
{
    buyOrder->reduceQty(matchQty);
    sellOrder->reduceQty(matchQty);
}

std::list<Order>::iterator OrderCache::eraseOrderFromContainers(const std::string& orderId, std::list<Order>::iterator it)
{
    m_orderMap.erase(orderId);
    return m_orders.erase(it);
}

std::vector<Order> OrderCache::getAllOrders() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return std::vector<Order>(m_orders.begin(), m_orders.end());
}
