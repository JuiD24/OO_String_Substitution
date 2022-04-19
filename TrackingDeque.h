#include <iostream>
#include <deque>
using namespace std;

template <typename TheType>
class TrackingDeque : public deque<TheType>
{
public:
    TrackingDeque(); //Default constructor

    ~TrackingDeque(); //Destructor
    void push_back(const TheType &val);
    void push_front(const TheType &val);

private:
    int maximum_size;
};

template <typename TheType>
TrackingDeque<TheType>::TrackingDeque()
    : maximum_size(0)
{
}

template <typename TheType>
TrackingDeque<TheType>::~TrackingDeque()
{
    cout << "---> " << maximum_size << " <---\n";
}

template <typename TheType>
void TrackingDeque<TheType>::push_back(const TheType &val)
{
    deque<TheType>::push_back(val);
    if (deque<TheType>::size() > maximum_size)
        maximum_size = deque<TheType>::size();
}

template <typename TheType>
void TrackingDeque<TheType>::push_front(const TheType &val)
{
    deque<TheType>::push_front(val);
    if (deque<TheType>::size() > maximum_size)
        maximum_size = deque<TheType>::size();
}