/*
 * BaseSlhaBlock.cpp
 *
 *  Created on: Mar 15, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#include "SLHA.hpp"

namespace LHPC
{
  namespace SLHA
  {
    BaseSlhaBlock::BaseSlhaBlock( std::string const& blockName ) :
        StringBlockObserver(),
        blockName( blockName )
    {
      BOL::StringParser::transformToUppercase( this->blockName );
    }

    BaseSlhaBlock::~BaseSlhaBlock()
    {
      // does nothing.
    }

  }

}
