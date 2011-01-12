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

#include "optionparser.h"
#include <iostream>
#include <cstring>

/*!
 * Get the basename of a path by simply spliting the path using slashes and
 * back slashes as delimiters. Should work for windows too.
 */
std::string OptionParser::basename (const std::string& path)
{
    std::size_t found = path.find_last_of("/\\");
    return path.substr(found + 1);
}

void OptionParser::usage()
{
    std::cout << "USAGE:" << std::endl
              << getProgramName() << " OPTION IMAGE [KEYWORDS]" << std::endl
              << std::endl
              << "OPTIONS:" << std::endl
              << " -a IMAGE KEYWORDS   Add the KEYWORDS to the image"        << std::endl 
              << " -d IMAGE KEYWORDS   Delete the KEYWORDS from the image"   << std::endl 
              << " -c IMAGE            Clear all keywords from the image"    << std::endl 
              << " -s IMAGE            Show all keywords from the image"     << std::endl 
              << " -h                  Show this message and exit"
              << std::endl;

}


bool OptionParser::validate()
{

    // At least there must be a two character long flag that starts with a dash
    if ((m_argc < 2) || (std::strlen(m_argv[1]) != 2) || (m_argv[1][0] != '-'))
    {
        return false;
    }

    // Ditch the dash
    char flag_opt = m_argv[1][1];

    // Each option (flag value) can have its own parameter requirements, do
    // further checks here. Also se if the operation they request needs to
    // read or write metadata from/to the image.
    switch(flag_opt)
    {
        case 'a':
        case 'd':
            // Add and Delete both read and write and need an image file and
            // at least one keyword to work with.
            m_readsImage = m_writesImage = true;
            if (m_argc < 4) return false;
            break;
        case 'c':
            // Clear writes to the image file and only requires a file name.
            m_writesImage = true;
        case 's':
            // Show only reads from the image file and does not require any
            // keywords, only the image file name.
            m_readsImage = true;
            if (m_argc < 3) return false;
            break;
        case 'h':
            // Help does not require any other arguments.
            return true;
        default:
            // Unknown option.
            return false;
    }
    return true;
}
