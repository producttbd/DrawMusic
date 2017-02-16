#ifndef GRIDDATAFILE_H_INCLUDED
#define GRIDDATAFILE_H_INCLUDED

#include "JuceHeader.h"

#include "GridData.h"

class GridDataFile : public FileBasedDocument
{
 public:
  explicit GridDataFile(GridData &gridData);

  String getDocumentTitle() override;
  Result loadDocument(const File &file) override;
  Result saveDocument(const File &file) override;
  File getLastDocumentOpened() override;
  void setLastDocumentOpened(const File &file) override;
  File getSuggestedSaveAsFile(const File &defaultFile) override;

 private:
  GridData &gridData_;
};

#endif  // GRIDDATAFILE_H_INCLUDED
