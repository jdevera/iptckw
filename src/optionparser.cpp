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


OptionParser::OptionParser(int argc, char* argv[])
    :m_programName(basename(argv[0])),
     m_writesImage(false),
     m_spOptDesc(boost::make_shared<po::options_description>("Options")),
     m_imageFileName(""),
     m_keywords(),
     m_valid(true)
{

    // Main options, the ones that will be shown in help message
    m_spOptDesc->add_options()
        ("add,a",    po::value<std::string>(&m_imageFileName), "Add the KEYWORDS to the image")
        ("delete,d", po::value<std::string>(&m_imageFileName), "Delete the KEYWORDS from the image")
        ("clear,c",  po::value<std::string>(&m_imageFileName), "Clear all keywords from the image")
        ("show,s",   po::value<std::string>(&m_imageFileName), "Show all keywords from the image")
        ("help,h",   "Show this message and exit")
    ;
    
    // Additional hidden options (not shown in help message, onoly used for
    // parsing)
    po::options_description hidden("Keywords");
    hidden.add_options()("keywords", po::value<std::vector<std::string> >(), "Keywords");

    // Make the keywords option positional
    po::positional_options_description positional;
    positional.add("keywords", -1);
    
    // Put together all options and use this aggreagate for parsing
    po::options_description command_line_options;
    command_line_options.add(*m_spOptDesc);
    command_line_options.add(hidden);
    
    try
    {
        po::store(po::command_line_parser(argc, argv).options(command_line_options)
                                                     .positional(positional)
                                                     .run(),
                  m_varMap);
        po::notify(m_varMap);
    }
    catch (boost::program_options::invalid_command_line_syntax)
    {
        m_valid = false;
    }
}

bool OptionParser::validate()
{

    // Command line might have already been invalidated
    if (!m_valid) return false;

    // Make sure only one option is specified, they are mutually exclusive.
    int optionCount = 0;


    // Each option (flag value) can have its own parameter requirements, do
    // further checks here. Also se if the operation they request needs to
    // write metadata to the image.
    if (opt_add())
    {
        m_writesImage = true;
        if (!has_keywords()) return false;
        optionCount++;
    }
    if (opt_delete())
    {
        m_writesImage = true;
        if (!has_keywords()) return false;
        optionCount++;
    }
    if (opt_clear())
    {
        // Clear writes to the image file and only requires a file name.
        m_writesImage = true;
        if (has_keywords()) return false;
        optionCount++;
    }
    if (opt_show())
    {
        // Show only reads from the image file and does not require any
        // keywords, only the image file name.
        if (has_keywords()) return false;
        optionCount++;
    }
    if (opt_help())
    {
        // Help does not require any other arguments.
        optionCount++;
    }
    
    if (optionCount != 1) return false;
    
    return true;
}
