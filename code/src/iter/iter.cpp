#include <forward_list>
#include <iostream>
#include <iterator>
#include <utility>
using namespace std;

#define t_iterator typename T::iterator


// In-place reverse iterator for arbitrary forward iterators.
// Not sure if qualifies as valid answer for exercise 11.5, though.
//   * Has constant space complexity, as required.
//   * Works for any forward iterator (the constructor might be
//     refactored in order to receive two iterators for a given
//     bounded range instead of the container itself).
//   * ...but the operator++ has linear time complexity :(
template<typename T>
class ReverseIterator : public iterator<forward_iterator_tag,
                                        typename T::value_type>
{
private:
    t_iterator _begin, _current;
    bool _has_next;

    pair<t_iterator, t_iterator> find_next(t_iterator limit) const
    {
        t_iterator current(_begin), prev(_begin);
        for(; current != limit; current++)
            prev = current;
        return {current, prev};
    };

public:
    ReverseIterator(T &container) : _begin(container.begin()),
                                    _current(find_next(container.end()).second)
    {
        _has_next = _begin != container.end();
    };

    ReverseIterator &operator++(int _)
    {
        pair<t_iterator, t_iterator> p(find_next(_current));
        if(p.first == _begin)
            _has_next = false;
        else
            _current = p.second;
        return *this;
    };

    typename T::value_type &operator*()
    {
        return *_current;
    };

    bool has_next() const
    {
        return _has_next;
    };
};


int main(int argc, char *argv[])
{
    forward_list<int> list;
    for(int i = 5; i > 0; --i)
        list.push_front(i);

    cout << "Reversing list [1,2,3,4,5] using an in-place reverse iterator..."
         << endl;

    ReverseIterator<forward_list<int> > iter(list);
    for(; iter.has_next(); iter++)
        cout << *iter << " ";
    cout << endl;

    return 0;
}
