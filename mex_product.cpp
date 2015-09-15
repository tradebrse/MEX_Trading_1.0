#include "mex_product.h"

MEX_Product::MEX_Product(QString name)
{
    this->name=name;
}

MEX_Product::~MEX_Product()
{

}
//Get Method
QString MEX_Product::getName()
{
    return this->name;
}
//Set Methods
void MEX_Product::setName(QString name)
{
    this->name = name;
    return;
}
