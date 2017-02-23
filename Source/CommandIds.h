#ifndef COMMANDIDS_H_INCLUDED
#define COMMANDIDS_H_INCLUDED

namespace DrawMusicCommandID
{
enum
{
  // general commands
  newDrawing = 0x200010,
  open = 0x200020,
  saveDrawing = 0x200030,
  saveDrawingAs = 0x200031,
  exportAudio = 0x200050,
  openSettings = 0x500010,

  // general?
  play_pause = 0x400010,

  // editing
  // StandardApplicationsCommands::del to clear
  // StandardApplicationsCommands::undo
  // StandardApplicationsCommands::redo

  // canvas commands
  gridSmaller = 0x300010,
  gridLarger = 0x300020,

};
}

namespace CommandCategories
{
static const char* const general = "General";
static const char* const editing = "Editing";
static const char* const canvas = "Canvas";
}

#endif  // COMMANDIDS_H_INCLUDED