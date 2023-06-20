#ifndef SOUVENIR_H
#define SOUVENIR_H
#include <string>

/*********************************************************************
 * Souvenir struct
 *   Represents a generic souvenir to be purchased. Manages 4 relevant
 *   attributes: name (string), price (double), quantity (int),
 *   total (double).
 *********************************************************************/
struct Souvenir
{
    std::string name;  // souvenir name
    double price;      // souvenir price
    int quantity;      // souvenir quantity bought
    double total;      // total price of souvenir purchase (price * quantity)

    Souvenir() = default;
    Souvenir(std::string souvName, double souvPrice, int souvQty = 0)
        : name(souvName), price(souvPrice), quantity(souvQty), total(0) {}

    void setQuantity(int qty)
    {
        quantity = qty;
        total = price * quantity;
    }

    void addQuantity(int qty)
    {
        quantity += qty;
        total += price * quantity;
    }
};

#endif // SOUVENIR_H
