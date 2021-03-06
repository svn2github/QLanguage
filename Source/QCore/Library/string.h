﻿/********************************************************************
	created:	2012/11/29
	created:	29:11:2012   23:36
	filename: 	\QCore\Library\string.h
	file path:	\QCore\Library
	file base:	string
	file ext:	h
	author:		lwch
	
	purpose:	
*********************************************************************/

#ifndef _QLANGUAGE_LIBRARY_STRING_H_
#define _QLANGUAGE_LIBRARY_STRING_H_

#include "definition.h"

#include "allocator.h"
#include "iterator.h"
#include "construct.h"

#include "char_traits.h"

#include <stdlib.h>
#include <stdarg.h>

NAMESPACE_QLANGUAGE_LIBRARY_START
#ifdef MSVC
#pragma warning(disable:4996)
#endif

template <typename T, typename Size, typename Distance>
class __basic_string_iterator : public __iterator<T, Size, Distance>, public random_access_iterator
{
protected:
    template <typename C, typename S, typename D>
    friend class __basic_string_const_iterator;

    typedef __iterator<T, Size, Distance>              parent;
    typedef __basic_string_iterator<T, Size, Distance> self;
    typedef T*                                         link_type;

    link_type node;
public:
    __basic_string_iterator() : node(NULL)
    {
    }

    __basic_string_iterator(link_type x) : node(x)
    {
    }

    static const self null()
    {
        static self tmp;
        return tmp;
    }

    inline typename parent::reference operator*()
    {
        return *node;
    }

    inline self& operator++()
    {
        ++node;
        return *this;
    }

    inline self operator++(int)
    {
        self tmp = *this;
        ++*this;
        return tmp;
    }

    inline self& operator--()
    {
        --node;
        return *this;
    }

    inline self operator--(int)
    {
        self tmp = *this;
        --*this;
        return tmp;
    }

    inline self operator+(Distance n)const
    {
        return self(node + n);
    }

    inline self& operator+=(Distance n)
    {
        node += n;
        return *this;
    }

    inline self operator-(Distance n)const
    {
        return self(node - n);
    }

    inline self& operator-=(Distance n)
    {
        node -= n;
        return *this;
    }

    inline const bool operator==(const self& x)const
    {
        return node == x.node;
    }

    inline const bool operator!=(const self& x)const
    {
        return node != x.node;
    }

    inline typename parent::value_type& operator[](Distance n)
    {
        return node[n];
    }

    inline operator link_type()const
    {
        return node;
    }
};

template <typename T, typename Size, typename Distance>
class __basic_string_const_iterator : public __const_iterator<T, Size, Distance>, public random_access_iterator
{
protected:
    typedef __const_iterator<T, Size, Distance>              parent;
    typedef __basic_string_const_iterator<T, Size, Distance> self;
    typedef const T*                                         link_type;

    link_type node;
public:
    __basic_string_const_iterator() : node(NULL)
    {
    }

    __basic_string_const_iterator(link_type x) : node(x)
    {
    }

    __basic_string_const_iterator(const __basic_string_iterator<T, Size, Distance>& x) : node(x.node)
    {
    }

    static const self null()
    {
        static self tmp;
        return tmp;
    }

    inline typename parent::reference operator*()
    {
        return *node;
    }

    inline self& operator++()
    {
        ++node;
        return *this;
    }

    inline self operator++(int)
    {
        self tmp = *this;
        ++*this;
        return tmp;
    }

    inline self& operator--()
    {
        --node;
        return *this;
    }

    inline self operator--(int)
    {
        self tmp = *this;
        --*this;
        return tmp;
    }

    inline self operator+(Distance n)const
    {
        return self(node + n);
    }

    inline self& operator+=(Distance n)
    {
        node += n;
        return *this;
    }

    inline self operator-(Distance n)const
    {
        return self(node - n);
    }

    inline self& operator-=(Distance n)
    {
        node -= n;
        return *this;
    }

    inline const bool operator==(const self& x)const
    {
        return node == x.node;
    }

    inline const bool operator!=(const self& x)const
    {
        return node != x.node;
    }

    inline typename parent::value_type& operator[](Distance n)
    {
        return node[n];
    }

    inline operator link_type()const
    {
        return node;
    }
};

#define BASIC_STRING_CONSTRUCT_HEADER start = finish = end_of_element = 0

template <typename T>
class basic_string
{
public:
    typedef T         value_type;
    typedef T*        pointer;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef size_t    size_type;
    typedef ptrdiff_t distance_type;
    typedef __basic_string_const_iterator<value_type, size_type, distance_type> const_iterator;
    typedef __reverse_iterator<const_iterator, value_type, size_type, distance_type> const_reverse_iterator;
    typedef __basic_string_iterator<value_type, size_type, distance_type> iterator;
    typedef __reverse_iterator<iterator, value_type, size_type, distance_type> reverse_iterator;

    static const size_type npos = -1;
protected:
#define MAX_STRING_RESERVE_SIZE 512
    typedef char_traits<T> Traits;

    typedef basic_string<T> self;
    typedef allocator<T>    Alloc;

    iterator start;
    iterator finish;
    iterator end_of_element;
public:
    basic_string()
    {
        BASIC_STRING_CONSTRUCT_HEADER;
        start = finish = Alloc::allocate(8);
        *finish = Traits::eof();
        end_of_element = start + 8;
    }

    basic_string(size_type n)
    {
        BASIC_STRING_CONSTRUCT_HEADER;
        const size_type _1 = n + 1;
        const size_type _2 = _1 * 2;
        reserve(_2 <= MAX_STRING_RESERVE_SIZE ? _2 : _1);
        *finish = Traits::eof();
    }

    basic_string(const T* s)
    {
        BASIC_STRING_CONSTRUCT_HEADER;
        const size_type n = Traits::length(s);
        const size_type _1 = n + 1;
        const size_type _2 = _1 * 2;
        reserve(_2 <= MAX_STRING_RESERVE_SIZE ? _2 : _1);
        copy(s, s + n, begin());
        finish = start + n;
        *finish = Traits::eof();
    }

    basic_string(const T* s, size_type n)
    {
        BASIC_STRING_CONSTRUCT_HEADER;
        const size_type sSize = Traits::length(s);
        if(n > sSize) THROW_OUT_OF_RANGE;
        const size_type _1 = n + 1;
        const size_type _2 = _1 * 2;
        reserve(_2 <= MAX_STRING_RESERVE_SIZE ? _2 : _1);
        copy(s, s + n, begin());
        finish = start + n;
        *finish = Traits::eof();
    }

    basic_string(const basic_string<T>& s)
    {
        BASIC_STRING_CONSTRUCT_HEADER;
        const size_type n = s.size();
        const size_type _1 = n + 1;
        const size_type _2 = _1 * 2;
        reserve(_2 <= MAX_STRING_RESERVE_SIZE ? _2 : _1);
        copy(s.begin(), s.end(), begin());
        finish = start + n;
        *finish = Traits::eof();
    }

    basic_string(const basic_string<T>& s, size_type pos, size_type n = npos)
    {
        BASIC_STRING_CONSTRUCT_HEADER;
        const size_type sSize = s.size();
        if(pos > sSize || pos < 0) THROW_OUT_OF_RANGE;
        const size_type nLength = n == npos ? sSize - pos : min(n, sSize - pos);
        const size_type _1 = nLength + 1;
        const size_type _2 = _1 * 2;
        reserve(_2 <= MAX_STRING_RESERVE_SIZE ? _2 : _1);
        copy(s.begin() + pos, s.begin() + pos + nLength, begin());
        finish = start + nLength;
        *finish = Traits::eof();
    }

    basic_string(size_type n, const T& c)
    {
        BASIC_STRING_CONSTRUCT_HEADER;
        const size_type _1 = n + 1;
        const size_type _2 = _1 * 2;
        reserve(_2 <= MAX_STRING_RESERVE_SIZE ? _2 : _1);
        uninitialized_fill_n(begin(), n, c);
        finish = start + n;
        *finish = Traits::eof();
    }

    template <typename Iterator>
    basic_string(Iterator first, Iterator last)
    {
        BASIC_STRING_CONSTRUCT_HEADER;
        const size_type n = last - first;
        const size_type _1 = n + 1;
        const size_type _2 = _1 * 2;
        reserve(_2 <= MAX_STRING_RESERVE_SIZE ? _2 : _1);
        copy(first, last, begin());
        finish = start + n;
        *finish = Traits::eof();
    }

    basic_string(const T* first, const T* last)
    {
        BASIC_STRING_CONSTRUCT_HEADER;
        const size_type n = last - first;
        const size_type _1 = n + 1;
        const size_type _2 = _1 * 2;
        reserve(_2 <= MAX_STRING_RESERVE_SIZE ? _2 : _1);
        copy(first, last, begin());
        finish = start + n;
        *finish = Traits::eof();
    }

    ~basic_string()
    {
        clear();
        if (start != iterator::null()) Alloc::deallocate(start, end_of_element - start);
    }

    void clear()
    {
        destruct_range(start, finish);
        finish = start;
    }

    inline const T* c_str()const
    {
        return start;
    }

    inline const T* data()const
    {
        return start;
    }

    void reserve(size_type count)
    {
        const size_type old_size = size();
        if(count <= capacity())
        {
            // Do nothing
        }
        else
        {
            iterator tmp = Alloc::allocate(count);
            copy(begin(), end(), tmp);
            Alloc::deallocate(start, capacity());
            start = tmp;
            finish = tmp + old_size;
            end_of_element = start + count;
        }
    }

    inline iterator begin()
    {
        return start;
    }

    inline const_iterator begin()const
    {
        return start;
    }

    inline reverse_iterator rbegin()
    {
        return reverse_iterator(end());
    }

    inline const_reverse_iterator rbegin()const
    {
        return const_reverse_iterator(end());
    }

    inline iterator end()
    {
        return finish;
    }

    inline const_iterator end()const
    {
        return finish;
    }

    inline reverse_iterator rend()
    {
        return reverse_iterator(begin());
    }

    inline const_reverse_iterator rend()const
    {
        return const_reverse_iterator(begin());
    }

    inline reference front()
    {
        return *begin();
    }

    inline const_reference front()const
    {
        return *begin();
    }

    inline reference back()
    {
        return *(end() - 1);
    }

    inline const_reference back()const
    {
        return *(end() - 1);
    }

    inline bool empty()const
    {
        return begin() == end();
    }

    inline const size_type size()const
    {
        return size_type(end() - begin());
    }

    void setsize(size_t size)
    {
        if (size <= capacity()) finish = start + size;
        else throw error<const char*>("size is too big", __FILE__, __LINE__);
    }

    inline const size_type capacity()const
    {
        return size_type(end_of_element - begin());
    }

    inline self& append(const self& s)
    {
        return append(s.begin(), s.end());
    }

    self& append(const self& s, size_type pos, size_type n)
    {
        const size_type sSize = s.size();
        if(pos > sSize || pos < 0) THROW_OUT_OF_RANGE;
        const size_type nLength = n == npos ? sSize - pos : min(n, sSize - pos);
        return append(s.begin(), s.begin() + nLength);
    }

    inline self& append(const T* s)
    {
        return append(s, s + Traits::length(s));
    }

    self& append(const T* s, size_type pos, size_type n)
    {
        const size_type sSize = char_traits<T>::length(s);
        if(pos > sSize || pos < 0) THROW_OUT_OF_RANGE;
        const size_type nLength = n == npos ? sSize - pos : min(n, sSize - pos);
        return append(s, s + nLength);
    }

    template <typename Iterator>
    self& append(Iterator first, Iterator last)
    {
        const size_type newSize = size() + last - first;
        const size_type _1 = newSize + 1;
        const size_type _2 = _1 * 2;
        reserve(_2 <= MAX_STRING_RESERVE_SIZE ? _2 : _1);
        copy(first, last, end());
        finish = start + newSize;
        *finish = Traits::eof();
        return *this;
    }

    self& append(const T* first, const T* last)
    {
        const size_type newSize = size() + last - first;
        const size_type _1 = newSize + 1;
        const size_type _2 = _1 * 2;
        reserve(_2 <= MAX_STRING_RESERVE_SIZE ? _2 : _1);
        copy(first, last, end());
        finish = start + newSize;
        *finish = Traits::eof();
        return *this;
    }

    inline self& assign(const self& s)
    {
        return assign(s.begin(), s.end());
    }

    self& assign(const self& s, size_type pos, size_type n)
    {
        const size_type sSize = s.size();
        if(pos > sSize || pos < 0) THROW_OUT_OF_RANGE;
        const size_type nLength = n == npos ? sSize - pos : min(n, sSize - pos);
        return assign(s.begin(), s.begin() + nLength);
    }

    inline self& assign(const T* s)
    {
        return assign(s, s + Traits::length(s));
    }

    self& assign(const T* s, size_type pos, size_type n)
    {
        const size_type sSize = s.size();
        if(pos > sSize || pos < 0) THROW_OUT_OF_RANGE;
        const size_type nLength = n == npos ? sSize - pos : min(n, sSize - pos);
        return assign(s, s + nLength);
    }

    template <typename Iterator>
    self& assign(Iterator first, Iterator last)
    {
        const size_type newSize = last - first;
        const size_type _1 = newSize + 1;
        const size_type _2 = _1 * 2;
        reserve(_2 <= MAX_STRING_RESERVE_SIZE ? _2 : _1);
        copy(first, last, begin());
        finish = start + newSize;
        *finish = Traits::eof();
        return *this;
    }

    self& assign(const T* first, const T* last)
    {
        const size_type newSize = last - first;
        const size_type _1 = newSize + 1;
        const size_type _2 = _1 * 2;
        reserve(_2 <= MAX_STRING_RESERVE_SIZE ? _2 : _1);
        copy(first, last, begin());
        finish = start + newSize;
        *finish = Traits::eof();
        return *this;
    }

    inline const size_type find(const self& s, size_type pos = 0)const
    {
        return find(s.begin(), pos, s.size());
    }

    inline const size_type find(const T* s, size_type pos = 0)const
    {
        return find(s, pos, Traits::length(s));
    }

    template <typename Iterator>
    const size_type find(Iterator first, size_type pos, size_type n)const
    {
        if(pos + n > size()) return npos;
        const_iterator result = search(begin() + pos, end(), first, first + n);
        return result != end() ? result - begin() : npos;
    }

    const size_type find(const T* first, size_type pos, size_type n)const
    {
        if(pos + n > size()) return npos;
        const_iterator result = search(begin() + pos, end(), first, first + n);
        return result != end() ? result - begin() : npos;
    }

    self substr(size_type i = 0, size_type iCount = npos)const
    {
        return self(*this, i, iCount);
    }

    template <typename T2>
    static const basic_string<T2> format(const T* fmt, ...)
    {
        throw error<const char*>("Doesn't support!", __FILE__, __LINE__);
        return basic_string<T2>();
    }

    static const basic_string<char> format(const char* fmt, ...)
    {
        va_list l;
        va_start(l, fmt);
        basic_string<T> result;
        int len = 0;
#ifdef WIN32
        len = _vscprintf(fmt, l);
        result.reserve(len + 1);
        vsprintf(result.begin(), fmt, l);
        result.finish = result.begin() + len;
#elif defined(unix)
        char* res = NULL;
        len = vasprintf(&res, fmt, l);
        result.reserve(len + 1);
        copy(res, res + len, result.begin());
        result.finish = result.begin() + len;
        free(res);
#endif
        *result.finish = char_traits<char>::eof();
        va_end(l);
        return result;
    }

    static const basic_string<wchar_t> format(const wchar_t* fmt, ...)
    {
        va_list l;
        va_start(l, fmt);
        basic_string<T> result;
        int len = 0;
#if defined(unix)
        throw error<const wchar_t*>(L"doesn't support", __FILE__, __LINE__);
#elif defined(WIN32) && !defined(__MINGW32__) && !defined(__CYGWIN__)
        len = _vscwprintf(fmt, l);
        result.reserve(len + 1);
        vswprintf(result.begin(), fmt, l);
        result.finish = result.begin() + len;
#endif
        *result.finish = char_traits<wchar_t>::eof();
        va_end(l);
        return result;
    }

    inline self operator+(const self& s)const
    {
        self tmp(*this);
        tmp += s;
        return tmp;
    }

    inline self operator+(const T* s)const
    {
        self tmp(*this);
        tmp += s;
        return tmp;
    }

    inline self operator+(const T& c)const
    {
        self tmp(*this);
        tmp += c;
        return tmp;
    }

    inline self& operator+=(const self& s)
    {
        return append(s);
    }

    inline self& operator+=(const T* s)
    {
        return append(s);
    }

    inline self& operator+=(const T& c)
    {
        push_back(c);
        return *this;
    }

    inline self& operator=(const self& s)
    {
        if(this != &s) assign(s.begin(), s.end());
        return *this;
    }

    inline self& operator=(const T* s)
    {
        return assign(s, s + Traits::length(s));
    }

    inline self& operator=(T c)
    {
        return assign(&c, &c + 1);
    }

    inline const_reference operator[](size_type n)const
    {
        return *(begin() + n);
    }

    inline reference operator[](size_type n)
    {
        return *(begin() + n);
    }

    inline const value_type at(size_type n)const
    {
        return operator[](n);
    }

    const bool operator==(const self& s)const
    {
        if(size() != s.size()) return false;
        for(size_type i = 0; i < size(); ++i)
        {
            if(at(i) != s[i]) return false;
        }
        return true;
    }

    const bool operator!=(const self& s)const
    {
        if(size() != s.size()) return true;
        for(size_type i = 0; i < size(); ++i)
        {
            if(at(i) != s[i]) return true;
        }
        return false;
    }

    const bool operator<(const self& s)const
    {
        return size() < s.size();
    }
};

typedef basic_string<char> string;
NAMESPACE_QLANGUAGE_LIBRARY_END

#endif
