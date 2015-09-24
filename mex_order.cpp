#include "mex_order.h"

MEX_Order::MEX_Order()
{
}

MEX_Order::MEX_Order(QString traderID, int orderID, int value, int quantity, QString comment, MEX_Product product)
{
    this->traderID = traderID;
    this->orderID = orderID;
    this->value = value;
    this->quantity = quantity;
    this->comment = comment;
    this->product = product;
    time = QDateTime::currentDateTime();
}

MEX_Order::~MEX_Order()
{

}

//Getter methods
QString MEX_Order::getTraderID()
{
    return this->traderID;
}
int MEX_Order::getOrderID()
{
    return this->orderID;
}
int MEX_Order::getValue()
{
    return this->value;
}
int MEX_Order::getQuantity()
{
    return this->quantity;
}
QString MEX_Order::getComment()
{
    return this->comment;
}
QDateTime MEX_Order::getTime()
{
    return this->time;
}

MEX_Product MEX_Order::getProduct()
{ 
    return this->product;
}

//Setter methods
void MEX_Order::setTraderID(QString traderID)
{
   this->traderID = traderID;
}
void MEX_Order::setOrderID(int orderID)
{
    this->orderID = orderID;
}
void MEX_Order::setValue(int value)
{
    this->value = value;
}
void MEX_Order::setQuantity(int quantity)
{
    this->quantity = quantity;
}
void MEX_Order::setComment(QString comment)
{
    this->comment = comment;
}

void MEX_Order::setProduct(MEX_Product product)
{
    this->product = product;
}

