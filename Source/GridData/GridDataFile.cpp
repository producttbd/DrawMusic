#include "GridDataFile.h"

#include "../Configuration.h"

GridDataFile::GridDataFile(GridData& gridData)
    : FileBasedDocument(".drawmusic", "*.drawmusic", TRANS("Load canvas"), TRANS("Save canvas")),
      gridData_(gridData)

{
}

String GridDataFile::getDocumentTitle()
{
  return "DrawMusicDocument";
}

Result GridDataFile::loadDocument(const File& file)
{
  // TODO deal with differing grid sizes
  ScopedPointer<FileInputStream> stream(file.createInputStream());
  if (stream != nullptr)
  {
    return gridData_.readFromStream(stream);
  }
  return Result::fail(TRANS("Failed to open file."));
}

Result GridDataFile::saveDocument(const File& file)
{
  if (!file.deleteFile())
  {
    return Result::fail(TRANS("Could not overwrite file"));
  }
  ScopedPointer<FileOutputStream> stream(file.createOutputStream());
  if (stream != nullptr)
  {
    return gridData_.writeToStream(stream);
  }
  return Result::fail(TRANS("Failed to open file."));
}

File GridDataFile::getLastDocumentOpened()
{
  return File();
}

void GridDataFile::setLastDocumentOpened(const File& /* file */)
{
  // TODO?
}

File GridDataFile::getSuggestedSaveAsFile(const File& defaultFile)
{
  return defaultFile;
}