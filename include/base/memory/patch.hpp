#pragma once

#include <algorithm>
#include <vector>

namespace base::memory
{
    template <typename T>
    class patch
    {
    public:
        explicit patch(void *address, std::vector<T> value);
        ~patch();

        void enable();
        void disable();

    private:
        T *m_address;
        std::vector<T> m_new_value;
        std::vector<T> m_original_value;
    };

    template <typename T>
    patch<T>::patch(void *address, std::vector<T> value)
    :
        m_address(static_cast<T *>(address)),
        m_new_value(std::move(value))
    {
        m_original_value.resize(m_new_value.size());
        
        std::copy_n(m_address, m_new_value.size(), m_original_value.data());
    }

    template <typename T>
    patch<T>::~patch()
    {
        disable();
    }

    template <typename T>
    void patch<T>::enable()
    {
        std::copy_n(m_new_value.data(), m_new_value.size(), m_address);
    }

    template <typename T>
    void patch<T>::disable()
    {
        std::copy_n(m_original_value.data(), m_original_value.size(), m_address);
    }
}