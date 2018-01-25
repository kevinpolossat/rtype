#include "MenuValue.h"

ge::MenuValue& ge::MenuValue::Instance()
{
    static MenuValue impl_;

    return (impl_);
}

GameConfiguration const &ge::MenuValue::getGameConfiguration() const {
  return configuration_;
}