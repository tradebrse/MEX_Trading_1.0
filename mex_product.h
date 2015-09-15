#ifndef MEX_PRODUCT_H
#define MEX_PRODUCT_H
#include <QString>

using namespace std;

class MEX_Product
{
public:
    MEX_Product(QString symbol, QString name);
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
