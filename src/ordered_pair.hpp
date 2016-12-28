#ifndef ORDERED_PAIR_HPP
#define ORDERED_PAIR_HPP

template<class T, class U>
class Ordered_pair {
public:
	Ordered_pair(T first, U second);

	T get_first();

	U get_second();

private:
	T first;
	U second;
};

template<class T, class U>
Ordered_pair<T, U>::Ordered_pair(T fst, U snd) : first(fst), second(snd) {}

template<class T, class U>
T Ordered_pair<T, U>::get_first()
{
	return first;
}

template<class T, class U>
U Ordered_pair<T, U>::get_second()
{
	return second;
}

#endif /* not ORDERED_PAIR_HPP */
