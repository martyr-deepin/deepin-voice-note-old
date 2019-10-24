#include "intancer.h"

Intancer * Intancer::instance_ = nullptr;
Intancer::Intancer()
{
    tryToDelEmptyTextNote = false;
    recording = false;
    isRenameRepeat = false;
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

void Intancer::setRenameRepeatFlag(bool value)
{
    isRenameRepeat = value;
}

bool Intancer::getRenameRepeatFlag()
{
    return isRenameRepeat;
}
