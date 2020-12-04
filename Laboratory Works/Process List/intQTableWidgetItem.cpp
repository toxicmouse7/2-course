#include "intQTableWidgetItem.h"

bool intQTableWidgetItem::operator<(const QTableWidgetItem& other)
{
	if (this->text().toInt() < other.text().toInt())
	{
		return true;
	}

	return false;
}
