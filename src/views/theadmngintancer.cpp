#include "theadmngintancer.h"


TheadMngIntancer * TheadMngIntancer::instance_ = nullptr;

TheadMngIntancer::TheadMngIntancer(QObject *parent) : QObject(parent)
{

}

TheadMngIntancer::~TheadMngIntancer()
{

}
