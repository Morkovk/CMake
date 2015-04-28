/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "cmGlobalNMakeMakefileGenerator.h"
#include "cmLocalUnixMakefileGenerator3.h"
#include "cmMakefile.h"

cmGlobalNMakeMakefileGenerator::cmGlobalNMakeMakefileGenerator()
{
  this->FindMakeProgramFile = "CMakeNMakeFindMake.cmake";
  this->ForceUnixPaths = false;
  this->ToolSupportsColor = true;
  this->UseLinkScript = false;
}

void cmGlobalNMakeMakefileGenerator
::EnableLanguage(std::vector<std::string>const& l,
                 cmMakefile *mf,
                 bool optional)
{
  // pick a default
  mf->AddDefinition("CMAKE_GENERATOR_CC", "cl");
  mf->AddDefinition("CMAKE_GENERATOR_CXX", "cl");
  if(!(cmSystemTools::GetEnv("INCLUDE") &&
       cmSystemTools::GetEnv("LIB"))
    )
    {
    std::string message = "To use the NMake generator, cmake must be run "
      "from a shell that can use the compiler cl from the command line. "
      "This environment does not contain INCLUDE, LIB, or LIBPATH, and "
      "these must be set for the cl compiler to work. ";
    mf->IssueMessage(cmake::WARNING,
                     message);
    }

  this->cmGlobalUnixMakefileGenerator3::EnableLanguage(l, mf, optional);
}

///! Create a local generator appropriate to this Global Generator
cmLocalGenerator *
cmGlobalNMakeMakefileGenerator::CreateLocalGenerator(cmLocalGenerator* parent)
{
  cmLocalUnixMakefileGenerator3* lg =
      new cmLocalUnixMakefileGenerator3(parent);
  lg->SetDefineWindowsNULL(true);
  lg->SetWindowsShell(true);
  lg->SetMakeSilentFlag("/nologo");
  lg->SetGlobalGenerator(this);
  lg->SetIgnoreLibPrefix(true);
  lg->SetPassMakeflags(true);
  lg->SetNMake(true);
  lg->SetUnixCD(false);
  return lg;
}

//----------------------------------------------------------------------------
void cmGlobalNMakeMakefileGenerator
::GetDocumentation(cmDocumentationEntry& entry)
{
  entry.Name = cmGlobalNMakeMakefileGenerator::GetActualName();
  entry.Brief = "Generates NMake makefiles.";
}
