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

#include "keywordbag.h"
#include "foreach.h"

const Exiv2::IptcKey KeywordBag::KeywordsKey("Iptc.Application2.Keywords");

KeywordBag::KeywordBag(const Exiv2::Image::AutoPtr& image)
{
    add(image);
}

void KeywordBag::add(const std::string& keyword)
{
    m_keywords.insert(keyword);
}

void KeywordBag::add(const Exiv2::Image::AutoPtr& image)
{
    image->readMetadata();
    foreach(Exiv2::Iptcdatum d, image->iptcData())
    {
        if (d.key() == KeywordBag::KeywordsKey.key())
        {
            m_keywords.insert(d.value().toString());
        }
    }
}

/*!
 * Replace all the keywords in an image's metadata with the ones in this
 * bag. Note that the image is not written to disk by this method.
 */
void KeywordBag::set(Exiv2::Image::AutoPtr& image)
{
    // We need to get the image's metadata before writing the keywords in the
    // bag so that the rest of the Iptc metadata is left intact.
    image->readMetadata();
    Exiv2::IptcData iptcData = image->iptcData();

    // All existing keywords in the image must be deleted first.
    Exiv2::IptcData::iterator kwIt = iptcData.findKey(KeywordsKey);
    while (kwIt != iptcData.end())
    {
        iptcData.erase(kwIt);
        kwIt = iptcData.findKey(KeywordBag::KeywordsKey);
    }

    // Now add each keyword from the bag to the image.
    Exiv2::StringValue sval;
    foreach(std::string keyword, m_keywords)
    {
        sval.read(keyword);
        iptcData.add(KeywordsKey, &sval);
    }
    image->setIptcData(iptcData);
}

bool KeywordBag::erase(const std::string& value)
{
    return bool(m_keywords.erase(value));
}

bool KeywordBag::hasKeyword(const std::string& value)
{
    return (m_keywords.find(value) != m_keywords.end());
}

KeywordBag::iterator KeywordBag::begin() const
{
    return m_keywords.begin();
}

KeywordBag::iterator KeywordBag::end() const 
{
    return m_keywords.end();
}

void KeywordBag::clear()
{
    m_keywords.clear();
}

KeywordBag::size_type KeywordBag::size()
{
    return m_keywords.size();
}

