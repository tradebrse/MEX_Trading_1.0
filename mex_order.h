#ifndef MEX_ORDER_H
#define MEX_ORDER_H
#include <QDateTime>
#include <mex_product.h>
#include <iostream>


class MEX_Order
{
public:
    MEX_Order();
    MEX_Order(QString traderID, int orderID, int value, int quantity, QString comment, MEX_Product product, QString ordertype);
    ~MEX_Order();

    // Getter/Setter methods
    QString getTraderID();
    QString getOrdertype();
    void setTraderID(QString);
    int getOrderID();
    void setOrderID(int);
    int getValue();
    void setValue(int);
    int getQuantity();
    void setQuantity(int);
    QString getComment();
    void setComment(QString);
    QDateTime getTime();
    MEX_Product getProduct();
    void setProduct(MEX_Product );


    void modify(int value, int quantity);
    //void deleteOrder();

private:

    QString traderID;
    int orderID;
    int value;
    int quantity;
    QString comment;
    QDateTime time;
    QString ordertype;
    MEX_Product product;

};

#endif // MEX_ORDER_H
