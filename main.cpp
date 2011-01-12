/****************************************************************************
Iptc Keyword Editor. Add, delete and show Iptc keywords from image files.

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

#include <iterator>
#include <algorithm>
#include "src/kwimage.h"
#include "src/optionparser.h"


int main(int argc, char **argv) {


    OptionParser op(argc, argv);

    // Exit early if the command line options were invalid.
    if (!op.validate())
    {
        op.usage();
        return 1;
    }

    // Also exit early for help requests
    if (op.opt_help())
    {
        op.usage();
        return 0;
    }


    // The rest of the options need to read the image file.
    KwImage image(op.image());
    image.readMetadata();

    if (op.opt_add())
    {
        image.addKeywords(op.keywords_begin(), op.keywords_end());
    }
    else if (op.opt_delete())
    {
        image.eraseKeywords(op.keywords_begin(), op.keywords_end());
    }
    else if (op.opt_clear())
    {
        image.clearKeywords();
    }
    else if (op.opt_show())
    {
        std::copy(image.begin(),
                  image.end(),
                  std::ostream_iterator<std:: string>(std::cout, "\n"));
    }

    // Only some operations require writting back to the image file.
    if (op.writesImage())
    {
        image.writeMetadata();
    }

    return 0;
}
