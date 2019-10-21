#include "intancer.h"

Intancer * Intancer::instance_ = nullptr;
Intancer::Intancer()
{
    tryToDelEmptyTextNote = false;
}

Intancer::~Intancer()
{

}

void Intancer::setTryToDelEmptyTextNote(bool value)
{
    tryToDelEmptyTextNote = value;
}

bool Intancer::getTryToDelEmptyTextNote()
{
    return tryToDelEmptyTextNote;
}
