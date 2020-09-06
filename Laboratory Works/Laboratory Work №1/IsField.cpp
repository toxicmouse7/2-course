#include "IsField.hpp"

bool IsField(Set& set)
{
	bool associativity = true, commutativity = true, neutral = false, opposite, distributivity = true;

	for (int i = 0; i < set.GetPower(); ++i)
	{
		for (int j = 0; j < set.GetPower(); ++j)
		{
			if (set.plus(i, j) != set.plus(j,i) || set.mult(i,j) != set.mult(j,i))
			{
				commutativity = false;
				goto exit;
			}
			
			for (int k = 0; k < set.GetPower(); ++k)
			{
				if (set.plus(set.plus(i,j), k) != set.plus(set.plus(k, j), i) || set.mult(set.mult(i, j), k) != set.mult(set.mult(k, j), i))
				{
					associativity = false;
					goto exit;
				}

				if (set.mult(set.plus(i, j), k) != set.plus(set.mult(i, k), set.mult(j, k)))
				{
					distributivity = false;
					goto exit;
				}
			}
		}
	}

	exit:

	return associativity && commutativity && distributivity;
}