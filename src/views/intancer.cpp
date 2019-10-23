#include "intancer.h"

Intancer * Intancer::instance_ = nullptr;
Intancer::Intancer()
{
    tryToDelEmptyTextNote = false;
    recording = false;
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

void Intancer::setRecodingFlag(bool value)
{
    recording = value;
}

bool Intancer::getRecodingFlag()
{
    return recording;
}
