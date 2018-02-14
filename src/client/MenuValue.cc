#include "MenuValue.h"

MenuValue& MenuValue::Instance()
{
    static MenuValue impl_;

    return (impl_);
}

GameConfiguration const &MenuValue::getGameConfiguration() const {
  return configuration_;
}