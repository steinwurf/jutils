// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <memory>

namespace jutils
{
template <class Object>
class ptr_container
{
public:
    ptr_container(std::shared_ptr<Object> object) : m_object(object)
    {
    }

    std::shared_ptr<Object> operator->()
    {
        return m_object;
    }

private:
    std::shared_ptr<Object> m_object;
};
}
