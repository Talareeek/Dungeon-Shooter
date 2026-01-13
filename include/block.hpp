#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "headers.hpp"
#include "object.hpp"

class block : public object
{
private:

public:

    using object::object;

    void update();

};

#endif // BLOCK_HPP