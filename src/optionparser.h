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

#ifndef OPTIONPARSER_H
#define OPTIONPARSER_H
#include <string>


//! A parser for the IptcKw command line
class OptionParser
{

    protected:
        //! A helper function to get the base name of a path
        static std::string basename (const std::string& path);

        //! The program's argc, stored for convenience
        int m_argc;

        //! A pointer to the original argv, stored for convenience
        char** m_argv;

        //! If the requested action needs to read metada from the image
        bool m_readsImage;

        //! If the requested action needs to write metadata to the image
        bool m_writesImage;


    public:

        //! Constructor from the program's argc and argv
        OptionParser(int argc, char **argv):m_argc(argc),m_argv(argv) {}

        //! Show the usage help message
        void usage();

        //! Check if the parameters passed int eh command line are valid
        bool validate();

        //! If the ADD option has been requested in the command line
        bool opt_add()    { return (m_argv[1][1] == OPT_ADD);    }

        //! If the DELETE option has been requested in the command line
        bool opt_delete() { return (m_argv[1][1] == OPT_DELETE); }

        //! If the CLEAR option has been requested in the command line
        bool opt_clear()  { return (m_argv[1][1] == OPT_CLEAR);  }

        //! If the SHOW option has been requested in the command line
        bool opt_show()   { return (m_argv[1][1] == OPT_SHOW);   }

        //! If the HELP option has been requested in the command line
        bool opt_help()   { return (m_argv[1][1] == OPT_HELP);   }

        //! Get the image file name specified in the command line
        char*  image()          { return  m_argv[2];             }

        //! Beginning of the keywords from the command line
        char** keywords_begin() { return m_argv + 3;             }

        //! End of the keywords from the command line
        char** keywords_end()   { return m_argv + m_argc ;       }

        //! Get the program name
        std::string getProgramName() {return basename(m_argv[0]);}

        //! Checks if the requested option needs to read metadata from the image
        bool readsImage()  { return m_readsImage; }

        //! Checks if the requested option needs to write metadata to the image
        bool writesImage() { return m_writesImage; }



        static const char OPT_ADD    = 'a'; //!< The add option flag
        static const char OPT_DELETE = 'd'; //!< The delete option flag
        static const char OPT_CLEAR  = 'c'; //!< The clear option flag
        static const char OPT_SHOW   = 's'; //!< The show option flag
        static const char OPT_HELP   = 'h'; //!< The help option flag
};

#endif // OPTIONPARSER_H
