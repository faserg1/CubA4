#include <app.hpp>
#include <mainFrame.hpp>

wxIMPLEMENT_APP(CubA4LauncherApp);
 
bool CubA4LauncherApp::OnInit()
{
    MainFrame *frame = new MainFrame();
    frame->Show(true);
    return true;
}