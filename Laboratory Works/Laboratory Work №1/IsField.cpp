#include "IsField.hpp"

bool IsField(Set& set)
{
	std::string neutral_element_plus, neutral_element_mult;
	bool associativity = true, commutativity = true, neutral = false, opposite = true, distributivity = true;

	for (const auto& ar_i : set.GetArray())
	{
		for (const auto& ar_j : set.GetArray())
		{
			if (set.plus(ar_i.second, ar_j.second) != set.plus(ar_j.second, ar_i.second) || set.mult(ar_i.second, ar_j.second) != set.mult(ar_j.second, ar_i.second))
			{
				commutativity = false;
				goto exit;
			}
			
			for (const auto& ar_k : set.GetArray())
			{
				if (set.plus(set.plus(ar_i.second, ar_j.second), ar_k.second) != set.plus(set.plus(ar_k.second, ar_j.second), ar_i.second)
					|| set.mult(set.mult(ar_i.second, ar_j.second), ar_k.second) != set.mult(set.mult(ar_k.second, ar_j.second), ar_i.second))
				{
					associativity = false;
					goto exit;
				}

				if (set.mult(set.plus(ar_i.second, ar_j.second), ar_k.second) != set.plus(set.mult(ar_i.second, ar_k.second), set.mult(ar_j.second, ar_k.second)))
				{
					distributivity = false;
					goto exit;
				}
			}
		}
	}

	//Нейтральный элемент по сложению
	for (const auto& ar_i : set.GetArray())
	{
		bool have_neutral = false;
		for (const auto& ar_j : set.GetArray())
		{
			if (set.plus(ar_i.second, ar_j.second) == ar_i.second)
			{
				for (const auto& ar_k : set.GetArray())
				{
					if (set.plus(ar_k.second, ar_j.second) != ar_k.second)
					{
						have_neutral = false;
						break;
					}
					else
					{
						have_neutral = true;
					}
				}

				if (have_neutral)
				{
					neutral_element_plus = ar_j.second;
					break;
				}
			}
		}

		if (have_neutral)
		{
			neutral = true;
			break;
		}
		else
		{
			goto exit;
		}
	}

	//Нейтральный элемент по умножению
	for (const auto& ar_i : set.GetArray())
	{
		if (ar_i.second == neutral_element_plus)
		{
			continue;
		}

		bool have_neutral = false;

		for (const auto& ar_j : set.GetArray())
		{
			if (ar_j.second == neutral_element_plus)
			{
				continue;
			}
			
			if (set.mult(ar_i.second, ar_j.second) == ar_i.second)
			{
				for (const auto& ar_k : set.GetArray())
				{
					if (ar_k.second == neutral_element_plus)
					{
						continue;
					}
					
					if (set.mult(ar_k.second, ar_j.second) != ar_k.second)
					{
						have_neutral = false;
						break;
					}
					else
					{
						have_neutral = true;
					}
				}

				if (have_neutral)
				{
					neutral_element_mult = ar_j.second;
					break;
				}
			}
		}

		if (have_neutral)
		{
			neutral = true;
			break;
		}
		else
		{
			goto exit;
		}
	}

	//Обратный элемент по сложению
	for (const auto& ar_i : set.GetArray())
	{
		bool have_opposite_plus = false;
		for (const auto& ar_j : set.GetArray())
		{
			if (set.plus(ar_i.second, ar_j.second) == neutral_element_plus)
			{
				have_opposite_plus = true;
				break;
			}
		}
		
		if (!have_opposite_plus)
		{
			opposite = false;
			goto exit;
		}
	}

	//Обратный элемент по умножению
	for (const auto& ar_i : set.GetArray())
	{
		if (ar_i.second == neutral_element_plus)
		{
			continue;
		}
		
		bool have_opposite_mult = false;
		for (const auto& ar_j : set.GetArray())
		{
			if (ar_j.second == neutral_element_plus)
			{
				continue;
			}
			
			if (set.mult(ar_i.second, ar_j.second) == neutral_element_mult)
			{
				have_opposite_mult = true;
				break;
			}
		}

		if (!have_opposite_mult)
		{
			opposite = false;
			break;
		}
	}
	
	exit:

	return associativity && commutativity && distributivity && neutral && opposite;
}