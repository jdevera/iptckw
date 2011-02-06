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
#include <boost/make_shared.hpp>
#include <iostream>
#include <cstring>

namespace po = boost::program_options;

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
    // std::cout << "USAGE:" << std::endl
    //           << getProgramName() << " OPTION IMAGE [KEYWORDS]" << std::endl
    //           << std::endl
    //           << "OPTIONS:" << std::endl
    //           << " -a IMAGE KEYWORDS   Add the KEYWORDS to the image"        << std::endl 
    //           << " -d IMAGE KEYWORDS   Delete the KEYWORDS from the image"   << std::endl 
    //           << " -c IMAGE            Clear all keywords from the image"    << std::endl 
    //           << " -s IMAGE            Show all keywords from the image"     << std::endl 
    //           << " -h                  Show this message and exit"
    //           << std::endl;


    std::cerr << *m_pOptDesc << std::endl;

}


OptionParser::OptionParser(int argc, char **argv)
    :m_argc(argc),
     m_argv(argv),
     m_readsImage(false),
     m_writesImage(false),
     m_pOptDesc(boost::make_shared<po::options_description>("Options")),
     m_imageFileName("")
{

    m_pOptDesc->add_options()
        ("add,a",    po::value<std::string>(), "Add the KEYWORDS to the image")
        ("delete,d", po::value<std::string>(), "Delete the KEYWORDS from the image")
        ("clear,c",  po::value<std::string>(), "Clear all keywords from the image")
        ("show,s",   po::value<std::string>(), "Show all keywords from the image")
        ("help,h",   "Show this message and exit")
    ;

    po::store(po::parse_command_line(argc, argv, *m_pOptDesc), m_varMap);
    po::notify(m_varMap);
}

bool OptionParser::validate()
{


    // TODO: Make sure only one option is specified, they are mutually exclusive.
    int optionCount = 0;


    // Each option (flag value) can have its own parameter requirements, do
    // further checks here. Also se if the operation they request needs to
    // read or write metadata from/to the image.
    if (opt_add())
    {
        // Add reads and writes. It needs an image file and at least one
        // keyword to work with.
        m_readsImage = m_writesImage = true;
        m_imageFileName = m_varMap["add"].as<std::string>();
        if (m_argc < 4) return false;
    }
    else if (opt_delete())
    {
        // Delete reads and writes. It needs an image file and at least one
        // keyword to work with.
        m_readsImage = m_writesImage = true;
        m_imageFileName = m_varMap["delete"].as<std::string>();
        if (m_argc < 4) return false;
    }
    else if (opt_clear())
    {
        // Clear writes to the image file and only requires a file name.
        m_readsImage = m_writesImage = true;
        m_imageFileName = m_varMap["clear"].as<std::string>();
        // if (m_argc < 3) return false;
    }
    else if (opt_show())
    {
        // Show only reads from the image file and does not require any
        // keywords, only the image file name.
        m_readsImage = true;
        m_imageFileName = m_varMap["show"].as<std::string>();
        // if (m_argc < 3) return false;
    }
    else if (opt_help())
    {
        // Help does not require any other arguments.
        return true;
    }
    else
    {
        // Unknown option.
        return false;
    }
    return true;
}
