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

#include "kwimage.h"


KwImage::KwImage(const std::string& imagePath)
    :m_image(Exiv2::ImageFactory::open(imagePath)),
     m_keywordbag()
{
}

void KwImage::readMetadata()
{
    m_image->readMetadata();
    m_keywordbag.add(m_image);
}

void KwImage::writeMetadata()
{
    m_keywordbag.set(m_image);
    m_image->writeMetadata();
}

void KwImage::addKeyword(const std::string& keyword)
{
    m_keywordbag.add(keyword);
}

bool KwImage::eraseKeyword(const std::string& keyword)
{
    return m_keywordbag.erase(keyword);
}

void KwImage::clearKeywords()
{
    m_keywordbag.clear();
}

KwImage::iterator KwImage::begin()
{
    return m_keywordbag.begin();
}

KwImage::iterator KwImage::end()
{
    return m_keywordbag.end();
}
