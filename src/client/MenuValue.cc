#include "MenuValue.h"

ge::MenuValue ge::MenuValue::m_instance=ge::MenuValue();

ge::MenuValue::MenuValue()
{}

ge::MenuValue::~MenuValue()
{}

ge::MenuValue& ge::MenuValue::Instance()
{
  return(m_instance);
}
