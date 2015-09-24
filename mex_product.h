#ifndef MEX_PRODUCT_H
#define MEX_PRODUCT_H
#include <QString>
#include <iostream>

class MEX_Product
{
public:
    MEX_Product();
    ~MEX_Product();

    QString getName();
    QString getSymbol();

    void setName(QString);
    void setSymbol(QString);

private:
    QString name;
    QString symbol;
};

#endif // MEX_PRODUCT_H
