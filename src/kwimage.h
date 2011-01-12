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

#ifndef KWIMAGE_H
#define KWIMAGE_H

#include <exiv2/image.hpp>
#include "keywordbag.h"

//! A wrapper for Exiv2::Image which handles IPTC keywords with a KeywordBag
class KwImage
{
    protected:
        //! The wrapped image object
        Exiv2::Image::AutoPtr m_image;

        //! The Image's keywords in a bag
        KeywordBag m_keywordbag;

    public:

        //! Image keyword iterator type
        typedef KeywordBag::iterator iterator;

        //! Constructor from an Exiv2::Image
        KwImage(Exiv2::Image::AutoPtr& image):m_image(image),m_keywordbag(m_image) {}

        //! Constructor from the path to an image file
        KwImage(const std::string &imagePath);

        //! Begin of the keywords
        iterator begin();

        //! End of the keywords
        iterator end();

        //! Read metadata from the image and load its keywords into the bag
        void readMetadata();

        //! Write the keywords in the bag to the image's metadata
        void writeMetadata();

        //! Add a keyword to the image
        void addKeyword(const std::string &keyword) ;

        //! Add a collection of keywords to the image
        template<typename InputIterator>
        void addKeywords(InputIterator first, InputIterator last);

        //! Delete a given keyword from the image
        bool eraseKeyword(const std::string &keyword) ;

        //! Delete a collection of keywords from the image.
        template <typename InputIterator>
        unsigned eraseKeywords(InputIterator first, InputIterator last);

        //! Clear all keywords from the image
        void clearKeywords() ;
};

#endif // KWIMAGE_H

// ---------------------------------------------------------------
// Implementation of template methods (must be in the header file)
// ---------------------------------------------------------------

template<typename InputIterator>
void KwImage::addKeywords(InputIterator first, InputIterator last)
{
    m_keywordbag.add(first, last);
}

template <typename InputIterator>
unsigned KwImage::eraseKeywords(InputIterator first, InputIterator last)
{
    return m_keywordbag.erase(first, last);
}