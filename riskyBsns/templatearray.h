#pragma once

/** ideal when the size is known at creation time */
template<typename DATA_TYPE>
class TemplateArray
{
protected:
	/** pointer to the allocated data for the vector */
	DATA_TYPE * m_data;

	/** actual number of allocated elements that we can use */
	int m_allocated;
public:
	/** @return value from the list at given index */
	inline DATA_TYPE & get(const int & a_index) const
	{
		return m_data[a_index];
	}

	/** simple mutator sets a value in the list */
	inline void set(const int & a_index, const DATA_TYPE & a_value)
	{
		// complex types must overload DATA_TYPE & operator=(const DATA_TYPE &)
		m_data[a_index] = a_value;
	}

protected:
	/** @note will only work if a_offset is a negative value...*/
	inline void moveDown(const int & a_from, const int & a_offset, int a_size)
	{
		for(int i = a_from; i < a_size; ++i)
		{
			set(i+a_offset, get(i));
		}
	}
	/** @note will only work if a_offset is a negative value...*/
	inline void moveUp(const int & a_from, const int & a_offset, int a_size)
	{
		for(int i = a_size-1; i >= a_from; --i)
		{
			set(i+a_offset, get(i));
		}
	}

public:
	/** @param a_size reallocate the vector to this size */
	const bool allocateToSize(const int & a_size)
	{
		// reallocate a new list with the given size
		DATA_TYPE * newList = new DATA_TYPE[a_size];
		// if the list could not allocate, fail...
		if(!newList)	return false;
		// the temp list is the one we will keep, while the old list will be dropped.
		DATA_TYPE * oldList = m_data;
		// swap done here so set(index, value) can be called instead of the equals operator
		m_data = newList;
		// if a list currently exists
		if(oldList)
		{
			// when copying old data, make sure no over-writes happen.
			int smallestSize = m_allocated<a_size?m_allocated:a_size;
			// fill the new list with the old data
			for(int i = 0; i < smallestSize; ++i)
			{
				set(i, oldList[i]);
			}
			// get rid of the old list (so we can maybe use the memory later)
			delete [] oldList;
		}
		// mark the new allocated size (held size of oldList)
		m_allocated = a_size;
		return true;
	}

	/** note: this method is memory intesive, and should not be in any inner loops... */
	void add(const DATA_TYPE & a_value)
	{
		allocateToSize(size()+1);
		set(size()-1, a_value);
	}

	/** note: this method is memory intesive, and should not be in any inner loops... */
	void add()
	{
		allocateToSize(size()+1);
	}

	/** sets all fields to an initial data state. WARNING: can cause memory leaks if used without care */
	inline void init()
	{
		m_data = 0;
		m_allocated = 0;
	}

	/** cleans up memory */
	inline void release()
	{
		if(m_data)
		{
			delete [] m_data;
			m_data = 0;
			m_allocated = 0;
		}
	}

	~TemplateArray(){release();}

	/** @return true if vector allocated this size */
	inline bool ensureCapacity(const int & a_size)
	{
		if(a_size && m_allocated < a_size)
		{
			return allocateToSize(a_size);
		}
		return true;
	}

	/** @return true of the copy finished correctly */
	inline bool copy(const TemplateArray<DATA_TYPE> & a_array)
	{
		if(ensureCapacity(a_array.m_allocated))
		{
			for(int i = 0; i < a_array.m_allocated; ++i)
			{
				set(i, a_array.get(i));
			}
			return true;
		}
		return false;
	}

	/** copy constructor */
	inline TemplateArray(
		const TemplateArray<DATA_TYPE> & a_array)
	{
		init();
		copy(a_array);
	}

	/** default constructor allocates no list (zero size) */
	inline TemplateArray(){init();}


	/** size constructor */
	inline TemplateArray(const int & a_size)
	{
		init();
		ensureCapacity(a_size);
	}

	/** format constructor */
	inline TemplateArray(const int & a_size,
		const DATA_TYPE & a_defaultValue)
	{
		init();
		ensureCapacity(a_size);
		for(int i = 0; i < a_size; ++i)
			set(i, a_defaultValue);
	}

	/** @return the size of the list */
	inline const int & size() const
	{
		return m_allocated;
	}

	/** @return the last value in the list */
	inline DATA_TYPE & getLast()
	{
		return get(size()-1);
	}

	/**
	 * @return the raw pointer to the data... 
	 * @note dangerous accessor. use it only if you know what you're doing.
	 */
	inline DATA_TYPE * getRawList()
	{
		return m_data;
	}

	/** 
	 * @param a_index is overwritten by the next element, which is 
	 * overwritten by the next element, and so on, till the last element
	 * @note this operation is memory intensive!
	 */
	void remove(const int & a_index)
	{
		moveDown(a_index+1, -1, size());
		allocateToSize(m_allocated-1);
	}

	/** 
	 * @param a_index where to insert a_value. shifts elements in the vector.
	 * @note this operation is memory intensive!
	 */
	void insert(const int & a_index, const DATA_TYPE & a_value)
	{
		setSize(m_size+1);
		moveUp(m_data, a_index, 1, size());
		set(a_index, a_value);
	}

	/** swaps to elements in the vector */
	inline void swap(const int & a_index0, const int & a_index1)
	{
		DATA_TYPE temp = get(a_index0);
		set(a_index0, get(a_index1));
		set(a_index1, temp);
	}

	/** @return index of 1st a_value at or after a_startingIndex. uses == */
	inline int indexOf(const DATA_TYPE & a_value, const int & a_startingIndex, const int & a_endingIndex) const
	{
		for(int i = a_startingIndex; i < a_endingIndex; ++i)
		{
			if(get(i) == a_value)
				return i;
		}
		return -1;
	}

	/** @return index of 1st a_value at or after a_startingIndex. uses == */
	inline int indexOf(const DATA_TYPE & a_value) const
	{
		return indexOf(a_value, 0, size());
	}

	/** 
	 * will only work correctly if the TemplateVector is sorted.
	 * @return the index of the given value, -1 if the value is not in the list
	 */
	int indexOfWithBinarySearch(const DATA_TYPE & a_value, const int & a_first, const int & a_limit)
	{
		if(m_size)
		{
			int first = a_first, last = a_limit;
			while (first <= last)
			{
				int mid = (first + last) / 2;  // compute mid point.
				if (a_value > m_data[mid]) 
					first = mid + 1;  // repeat search in top half.
				else if (a_value < m_data[mid]) 
					last = mid - 1; // repeat search in bottom half.
				else
					return mid;     // found it. return position
			}
		}
		return -1;    // failed to find key
	}

	void setAll(const DATA_TYPE & a_value)
	{
		for(int i = 0; i < size(); ++i)
		{
			set(i, a_value);
		}
	}
};
