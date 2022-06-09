namespace my
{
	template <typename Iter, typename pred>
	bool all_of(Iter begin, Iter end, pred p)
	{
		for (Iter i = begin; i != end; ++i)
			if (!p(*i))
				return false;
		return true;
	}

	template <typename Iter, typename pred>
	bool any_of(Iter begin, Iter end, pred p)
	{
		for (Iter i = begin; i != end; ++i)
			if (p(*i))
				return true;
		return false;
	}

	template <typename Iter, typename pred>
	bool none_of(Iter begin, Iter end, pred p)
	{
		for (Iter i = begin; i != end; ++i)
			if (p(*i))
				return false;
		return true;
	}

	template <typename Iter, typename pred>
	bool one_of(Iter begin, Iter end, pred p)
	{
		bool one = false;
		for (Iter i = begin; i != end; ++i)
			if (p(*i))
				if (one = false)
					one = true;
				else
					return false;
	
		if (one)
			return true;
		else
			return false;
	}

	template <typename Iter>
	bool is_sorted (Iter begin, Iter end)
	{
		Iter prev = begin;

		for (Iter i = begin + 1; i != end; ++i)
		{
			if (*prev > *i)
				return false;
			prev = i;
		}

		return true;
	}

	template <typename Iter, typename pred>
	bool is_partitioned(Iter begin, Iter end, pred p)
	{
		char atape = 1;
		bool znach;

		if (p(*begin))
			znach = true;
		else
			znach = false;

		for (Iter i = begin + 1; i != end; ++i)
		{
			if (p(*i) != znach)
			{
				znach = p(*i);
				atape++;
				if (atape > 2)
					return false;
			}
		}
		return true;
	}

	template <typename Iter, typename znach>
	Iter find_not(Iter begin, Iter end, znach z)
	{
		for (Iter i = begin; i != end; ++i)
		{
			if (*i != z)
				return i;
		}

		return end+1;
	}

	template <typename Iter, typename znach>
	Iter find_backward(Iter begin, Iter end, znach z)
	{
		for (Iter i = end; i != begin; --i)
		{
			if (*i == z)
				return i;
		}

		return end + 1;
	}

	template <typename Iter, typename pred>
	bool is_palindrome (Iter begin, Iter end, pred p)
	{
		Iter prev=begin;
		end--;

		while (begin!=end && end != prev)
		{
			if (p(* begin) != p(*end))
				return false;
			prev = begin;
			begin++;
			end--;
		}

		return true;
	}
}
