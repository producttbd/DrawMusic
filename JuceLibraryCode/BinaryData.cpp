/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== ToDo.txt ==================
static const unsigned char temp_binary_data_0[] =
"- Continuity of drawing\n"
"  - connecting mouse drag events\n"
"  - Moving applying brushes to background thread\n"
"- Lim/Griffin:\n"
"  - Clean up last window stuff\n"
"  - Check spectrum of output audio\n"
"  - Verify implementation\n"
"  - Clean out slider junk (move to settings menu?)\n"
"- WaveFrom display\n"
"- Log scale of vertical axis\n"
"- Background audio rendering\n"
"- Look and feel\n"
"- Clean up all the dimensions in MainComponent\n"
"- Clean up all header comments in source files\n"
"- Clean up includes\n"
"- Waveform view\n"
"- Save/load\n"
"\n"
"\n";

const char* ToDo_txt = (const char*) temp_binary_data_0;


const char* getNamedResource (const char*, int&) throw();
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes) throw()
{
    unsigned int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x80091737:  numBytes = 501; return ToDo_txt;
        default: break;
    }

    numBytes = 0;
    return 0;
}

const char* namedResourceList[] =
{
    "ToDo_txt"
};

}
