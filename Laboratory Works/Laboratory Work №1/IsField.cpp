#include "IsField.hpp"

bool Assoc_Commut_Distrib(Set& set)
{
	for (const auto& ar_i : set.GetArray())
	{
		for (const auto& ar_j : set.GetArray())
		{
			if (set.plus(ar_i.second, ar_j.second) != set.plus(ar_j.second, ar_i.second) || set.mult(ar_i.second, ar_j.second) != set.mult(ar_j.second, ar_i.second))
			{
				return false;
			}

			for (const auto& ar_k : set.GetArray())
			{
				if (set.plus(set.plus(ar_i.second, ar_j.second), ar_k.second) != set.plus(set.plus(ar_k.second, ar_j.second), ar_i.second)
					|| set.mult(set.mult(ar_i.second, ar_j.second), ar_k.second) != set.mult(set.mult(ar_k.second, ar_j.second), ar_i.second))
				{
					return false;
				}

				if (set.mult(set.plus(ar_i.second, ar_j.second), ar_k.second) != set.plus(set.mult(ar_i.second, ar_k.second), set.mult(ar_j.second, ar_k.second)))
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool NeutralElementPlus(Set& set, std::string& plus_element)
{
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
					plus_element = ar_j.second;
					break;
				}
			}
		}

		if (have_neutral)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool NeutralElementMult(Set& set, const std::string& plus_element, std::string& mult_element)
{
	for (const auto& ar_i : set.GetArray())
	{
		if (ar_i.second == plus_element)
		{
			continue;
		}

		bool have_neutral = false;

		for (const auto& ar_j : set.GetArray())
		{
			if (ar_j.second == plus_element)
			{
				continue;
			}

			if (set.mult(ar_i.second, ar_j.second) == ar_i.second)
			{
				for (const auto& ar_k : set.GetArray())
				{
					if (ar_k.second == plus_element)
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
					mult_element = ar_j.second;
					return true;
				}
			}
		}

		return false;
	}
}

bool OppositeElementPlus(Set& set, const std::string& plus_element)
{
	for (const auto& ar_i : set.GetArray())
	{
		bool have_opposite_plus = false;
		for (const auto& ar_j : set.GetArray())
		{
			if (set.plus(ar_i.second, ar_j.second) == plus_element)
			{
				have_opposite_plus = true;
				break;
			}
		}

		if (!have_opposite_plus)
		{
			return false;
		}
	}

	return true;
}

bool OppositeElementMult(Set& set, const std::string& plus_element, const std::string& mult_element)
{
	for (const auto& ar_i : set.GetArray())
	{
		if (ar_i.second == plus_element)
		{
			continue;
		}

		bool have_opposite_mult = false;
		
		for (const auto& ar_j : set.GetArray())
		{
			if (ar_j.second == plus_element)
			{
				continue;
			}

			if (set.mult(ar_i.second, ar_j.second) == mult_element)
			{
				have_opposite_mult = true;
				break;
			}
		}

		if (!have_opposite_mult)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

bool IsField(Set& set)
{
	std::string neutral_element_plus, neutral_element_mult;
	
	bool a_c_d = Assoc_Commut_Distrib(set);

	if (!a_c_d)
	{
		return false;
	}

	bool neutral = NeutralElementPlus(set, neutral_element_plus) && NeutralElementMult(set, neutral_element_plus, neutral_element_mult);

	if (!neutral)
	{
		return false;
	}

	bool opposite = OppositeElementPlus(set, neutral_element_plus) && OppositeElementMult(set, neutral_element_plus, neutral_element_mult);

	if (!opposite)
	{
		return false;
	}

	return true;
}