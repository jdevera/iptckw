/****************************************************************************

Copyright (C) 2011 Jacobo de Vera

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*****************************************************************************
*/

#ifndef KEYWORDBAG_H
#define KEYWORDBAG_H

#include <set>
#include <string>
#include <functional>
#include <exiv2/image.hpp>

//! A smart container for IPTC keywords.
/*!
 * Contains a set of keywords and can write to or read from Exiv2::Image
 * objects.
 */
class KeywordBag
{
    protected:
        //! Keyword container type
        typedef std::set<std::string> keyword_container_type;

        //! Keyword container
        keyword_container_type m_keywords;

    public:

        //! KeywordBag iterator type
        typedef keyword_container_type::iterator iterator;

        //! KeywordBag size type
        typedef std::size_t size_type;

        //! Key name for IPTC keywords
        static const Exiv2::IptcKey KeywordsKey;

        //! Constructor from a collection of keywords
        template <typename InputIterator>
        KeywordBag(InputIterator first, InputIterator last): m_keywords(first,last) {}

        //! Constructor from the keywords in an image
        KeywordBag(const Exiv2::Image::AutoPtr &image);

        //! Default (empty KeywordBag) constructor
        KeywordBag(): m_keywords() {}

        //! Destructor
        virtual ~KeywordBag() {}

        //! Begin of the keywords
        iterator begin() const ;

        //! End of the keywords
        iterator end() const ;

        //! Add all keywords contained in an image's metadata
        void add(const Exiv2::Image::AutoPtr& image);

        //! Add a single keyword
        void add(const std::string &keyword);

        //! Add a collection of keywords
        template<typename InputIterator>
        void add(InputIterator first, InputIterator last);

        //! Save the keywords to an image's metadata
        void set(Exiv2::Image::AutoPtr& image);

        //! Erase a given keyword, if exists
        bool erase(const std::string &value);

        //! Clear the bag: delete all keywords
        void clear();

        //! Erase a collection of keywords
        //! \return The number of erased keywords
        template <typename InputIterator>
        unsigned erase(InputIterator first, InputIterator last);

        //! Check wether a given keyword is in the bag
        bool hasKeyword(const std::string &value);

        //! Get the number of keywords in the bag
        size_type size();

};

// ---------------------------------------------------------------
// Implementation of template methods (must be in the header file)
// ---------------------------------------------------------------

template<typename InputIterator>
void KeywordBag::add(InputIterator first, InputIterator last)
{
    m_keywords.insert(first, last);
}

template <typename InputIterator>
unsigned KeywordBag::erase(InputIterator first, InputIterator last)
{
    unsigned count = 0;
    for (InputIterator kwIt = first; kwIt != last; ++kwIt)
    {
        if (erase(*kwIt))
            count++;
    }
    return count;
}

#endif // KEYWORDBAG_H